#pragma once

#include <Core/Math/hlsl++/common.h>
#include <Core/Math/hlsl++/vector_float.h>

#if defined(GGE_MODULE_DECLARATION)
import <math.h>;
#else
#include <math.h>
#endif

//-----------
// Quaternion
//-----------

#include <Core/Math/hlsl++/quaternion_type.h>

GGE_module_export namespace GGE
{
	// https://proofwiki.org/wiki/Quaternion_Multiplication
	GGE_inline n128 _GGE_quat_mul_ps(const n128 q0, const n128 q1)
	{
		// q0.x * q1.w, q0.y * q1.w, q0.x * q1.y, q0.x * q1.x
		n128 tmp_mul_0 = _GGE_mul_ps(_GGE_perm_xyxx_ps(q0), _GGE_perm_wwyx_ps(q1));

		// q0.y * q1.x + q0.x * q1.w, q0.z * q1.x + q0.y * q1.w, q0.z * q1.w + q0.x * q1.y, q0.y * q1.y + q0.x * q1.x
		n128 tmp_mad_1 = _GGE_madd_ps(_GGE_perm_yzzy_ps(q0), _GGE_perm_zxwy_ps(q1), tmp_mul_0);

		const n128i signMask = _GGE_set_epi32(0, 0, 0, (int)0x80000000);
		n128 tmp_sign = _GGE_xor_ps(tmp_mad_1, _GGE_castsi128_ps(signMask)); // Flip the sign from the last row (w)

		// q0.w * q1.x + q0.y * q1.x + q0.x * q1.w, 
		// q0.w * q1.y + q0.z * q1.x + q0.y * q1.w, 
		// q0.w * q1.z + q0.z * q1.w + q0.x * q1.y,
		// q0.w * q1.w - q0.y * q1.y - q0.x * q1.x
		n128 tmp_mad_2 = _GGE_madd_ps(_GGE_perm_wwww_ps(q0), q1, tmp_sign);

		// q0.w * q1.x + q0.y * q1.x + q0.x * q1.w - q0.z * q1.y
		// q0.w * q1.y + q0.z * q1.x + q0.y * q1.w - q0.x * q1.z
		// q0.w * q1.z + q0.z * q1.w + q0.x * q1.y - q0.y * q1.x
		// q0.w * q1.w - q0.y * q1.y - q0.x * q1.x - q0.z * q1.z
		n128 result = _GGE_subm_ps(tmp_mad_2, _GGE_perm_zxyz_ps(q0), _GGE_perm_yzxz_ps(q1));
		return result;
	}

	GGE_inline n128 _GGE_quat_conjugate_ps(const n128 q)
	{
		static const n128i signMask = _GGE_set_epi32((int)0x80000000, (int)0x80000000, (int)0x80000000, 0);
		return _GGE_xor_ps(q, _GGE_castsi128_ps(signMask)); // Flip the sign bits of the vector part of the quaternion
	}

	// Quaternion - vector multiplication. Faster version of q * v * q*
	// Rotates a vector using a quaternion
	// https://blog.molecular-matters.com/2013/05/24/a-faster-quaternion-vector-multiplication/
	// We are using the same default convention as matrices where this version premultiplies
	// the vector. This effectively matches vec * matrix(q)
	GGE_inline n128 _GGE_quat_mul_vec_ps(const n128 v, const n128 q)
	{
		n128 t = _GGE_cross_ps(q, v);
		n128 t2 = _GGE_add_ps(t, t);
		n128 qxt = _GGE_cross_ps(q, t2);
		n128 v_qxt = _GGE_add_ps(v, qxt);
		n128 result = _GGE_madd_ps(_GGE_perm_wwww_ps(q), t2, v_qxt);
		return result;
	}

	GGE_inline n128 _GGE_quat_mul_vec_inv_ps(const n128 q, const n128 v)
	{
		n128 t = _GGE_cross_ps(v, q);
		n128 t2 = _GGE_add_ps(t, t);
		n128 qxt = _GGE_cross_ps(t2, q);
		n128 v_qxt = _GGE_add_ps(v, qxt);
		n128 result = _GGE_madd_ps(_GGE_perm_wwww_ps(q), t2, v_qxt);
		return result;
	}

	GGE_inline n128 _GGE_quat_inverse_ps(const n128 q)
	{
		n128 conjugate = _GGE_quat_conjugate_ps(q);
		n128 sqNorm = _GGE_dot4_ps(q, q);
		n128 result = _GGE_div_ps(conjugate, sqNorm);
		return result;
	}

	// Assume axis is a 3-component vector and angle is contained in all components of angle
	// Also assume that the axis is normalized
	GGE_inline n128 _GGE_quat_axis_angle_ps(const n128 axis, const n128 angle)
	{
		n128 angle05 = _GGE_mul_ps(angle, f4_05);
		n128 sin     = _GGE_mul_ps(_GGE_sin_ps(angle05), axis);
		n128 cos     = _GGE_cos_ps(angle05);
		n128 result  = _GGE_blend_ps(sin, cos, GGE_BLEND_MASK(1, 1, 1, 0));
		return result;
	}

	// Make the same assumptions as the previous function. This function exists because often
	// it's very cheap to obtain the cosine via a dot product and work with that directly as
	// obtaining the angle would require a costly acos. The variable sign contains the direction
	// of the angle in all components, 1.0f for clockwise and -1.0f for anti-clockwise
	GGE_inline n128 _GGE_quat_axis_cosangle_ps(const n128 axis, const n128 cosangle, const n128 sign)
	{
		// We'll use the identities
		//
		//                 |  1 + cos(2 * theta)  |
		// cosTheta = sqrt | -------------------- |
		//                 |           2          |
		//
		// cos^2(x) + sin^2(x) = 1

		n128 cosangle05 = _GGE_sqrt_ps(_GGE_madd_ps(f4_05, cosangle, f4_05));
		n128 sinangle05 = _GGE_mul_ps(_GGE_sqrt_ps(_GGE_subm_ps(f4_1, cosangle05, cosangle05)), sign);
		n128 sinAxis = _GGE_mul_ps(sinangle05, axis);
		n128 result = _GGE_blend_ps(sinAxis, cosangle05, GGE_BLEND_MASK(1, 1, 1, 0));
		return result;
	}

	// http://d.hatena.ne.jp/ohtorii/20150424/p1
	inline n128 _GGE_quat_euler_zxy_ps(const n128 angles)
	{
		n128 angles05 = _GGE_mul_ps(angles, f4_05);
		n128 sin = _GGE_sin_ps(angles05);
		n128 cos = _GGE_cos_ps(angles05);

		n128 CxCxCxCx	= _GGE_perm_xxxx_ps(cos);
		n128 SySyCyCy	= _GGE_shuf_yyyy_ps(sin, cos);
		n128 SzCzSzCz	= _GGE_blend_ps(_GGE_perm_zzzz_ps(sin), _GGE_perm_zzzz_ps(cos), GGE_BLEND_MASK(1, 0, 1, 0));

		n128 term1		= _GGE_mul_ps(CxCxCxCx, _GGE_mul_ps(SySyCyCy, SzCzSzCz));

		n128 SxSxSxSx	= _GGE_perm_xxxx_ps(sin);
		n128 CyCySySy	= _GGE_shuf_yyyy_ps(cos, sin);
		n128 CzSzCzSz	= _GGE_blend_ps(_GGE_perm_zzzz_ps(sin), _GGE_perm_zzzz_ps(cos), GGE_BLEND_MASK(0, 1, 0, 1));

		n128 term2		= _GGE_mul_ps(SxSxSxSx, _GGE_mul_ps(CyCySySy, CzSzCzSz));
		const n128i signMask = _GGE_set_epi32(0, (int)0x80000000, (int)0x80000000, 0);
		term2			= _GGE_xor_ps(term2, _GGE_castsi128_ps(signMask)); // Flip the sign bits

		n128 result		= _GGE_add_ps(term1, term2);
		return result;
	}

	// Quaternion interpolation functions
	// Assume input quaternions are normalized
	// Assume t is in the x component
	
	// Spherical interpolation
	// - Non-commutative
	// - Constant velocity
	inline n128 _GGE_quat_slerp_ps(const n128 q0, const n128 q1, const n128 t)
	{
		n128 cosHalfTheta       = _GGE_dot4_ps(q0, q1);

		// Small imprecisions in the incoming quaternions can cause the dot product to be very slightly larger than 1 which will cause a nan in acos
		cosHalfTheta            = _GGE_clamp_ps(cosHalfTheta, f4_minus1, f4_1);

		n128 t4                 = _GGE_shuf_xxxx_ps(t, f4_1); // Contains t, t, 1, unused
		n128 oneMinusT          = _GGE_sub_ps(f4_1, t4);      // Contains 1 - t, 1 - t, 0, unused
		n128 lerpFactors        = _GGE_blend_ps(oneMinusT, t4, GGE_BLEND_MASK(1, 0, 0, 1)); // Contains (1 - t), t, 1, unused

		n128 halfTheta          = _GGE_acos_ps(cosHalfTheta);
		
		n128 tTheta             = _GGE_mul_ps(lerpFactors, _GGE_perm_xxxx_ps(halfTheta));   // Contains (1 - t) * theta, t * theta, theta, unused
		n128 sinVec             = _GGE_sin_ps(tTheta);                                         // Contains sin((1 - t) * theta), sin(t * theta), sin(theta), unused
		
		n128 sinTheta4          = _GGE_perm_zzzz_ps(sinVec);
		n128 sinVecDiv          = _GGE_div_ps(sinVec, sinTheta4);

		// If theta -> 0, the result converges to lerp(q0, q1, t). As there is a division by 0 in this case, 
		// we can select between those two in the case where sinTheta4 is 0 or some threshold
		sinVecDiv        = _GGE_sel_ps(sinVecDiv, lerpFactors, _GGE_cmpeq_ps(sinTheta4, _GGE_setzero_ps()));

		n128 q0_sinTheta = _GGE_mul_ps(q0, _GGE_perm_xxxx_ps(sinVecDiv));
		n128 result      = _GGE_madd_ps(_GGE_perm_yyyy_ps(sinVecDiv), q1, q0_sinTheta);

		return result;
	}

	// Linear interpolation followed by normalization
	// - Commutative
	// - Non-constant velocity
	inline n128 _GGE_quat_nlerp_ps(const n128 q0, const n128 q1, const n128 t)
	{
		n128 t4         = _GGE_perm_xxxx_ps(t); // Contains t, t, t, t

		n128 q1_minus_q0 = _GGE_sub_ps(q1, q0); // q1 - q0
		n128 lerp        = _GGE_madd_ps(t4, q1_minus_q0, q0); // q0 * (1 - t) + q1 * t

		n128 result = _GGE_mul_ps(lerp, _GGE_rsqrt_ps(_GGE_dot4_ps(lerp, lerp)));

		return result;
	}

	// Simple interpolation
	// - Likely returns a non-normalized quaternion
	GGE_inline n128 _GGE_quat_lerp_ps(const n128 q0, const n128 q1, const n128 t)
	{
		n128 t4 = _GGE_perm_xxxx_ps(t);           // Contains t, t, t, t
		n128 q1_minus_q0 = _GGE_sub_ps(q1, q0);   // q1 - q0
		return _GGE_madd_ps(t4, q1_minus_q0, q0); // q0 * (1 - t) + q1 * t
	}

	// https://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToMatrix/index.htm
	// 
	// | 1 - 2 * (q.y * q.y * q.z * q.z) |   2 * (q.x * q.y + q.k * q.w)   |   2 * (q.x * q.z - q.y * q.w)   |
	// |                                 |                                 |                                 |
	// |   2 * (q.x * q.y - q.k * q.w)   | 1 - 2 * (q.x * q.x + q.z * q.z) |   2 * (q.y * q.z + q.x * q.w)   |
	// |                                 |                                 |                                 |
	// |   2 * (q.x * q.z + q.y * q.w)   |   2 * (q.y * q.z - q.x * q.w)   | 1 - 2 * (q.x * q.x + q.z * q.z) |
	//
	// We use the transposed version to be consistent with the left-hand default of hlsl. In right-handed mode
	// the quaternion will have a flipped sign
	inline void _GGE_quat_to_3x3_ps(const n128 q, n128& row0, n128& row1, n128& row2)
	{
		n128 q_xxy		= _GGE_perm_xxyx_ps(q);        // q.x, q.x, q.y
		n128 q_zyz		= _GGE_perm_zyzx_ps(q);        // q.z, q.y, q.x
		n128 q_mul0		= _GGE_mul_ps(q_xxy, q_zyz);   // q.x * q.z, q.x * q.y, q.y * q.z

		n128 q_yzx		= _GGE_perm_yzxx_ps(q);        // q.y, q.z, q.x
		n128 q_www		= _GGE_perm_wwwx_ps(q);        // q.w, q.w, q.w
		n128 q_mul1		= _GGE_mul_ps(q_yzx, q_www);   // q.y * q.w, q.z * q.w, q.x * q.w

		n128 q_add		= _GGE_add_ps(q_mul0, q_mul1); // q.x * q.z + q.y * q.w, q.x * q.y + q.z * q.w, q.y * q.z + q.x * q.w
		q_add			= _GGE_add_ps(q_add, q_add);   // 2 * (q.x * q.z + q.y * q.w), 2 * (q.x * q.y + q.z * q.w), 2 * (q.y * q.z + q.x * q.w)

		n128 q_sub		= _GGE_sub_ps(q_mul0, q_mul1); // q.x * q.z - q.y * q.w, q.x * q.y - q.z * q.w, q.y * q.z - q.x * q.w
		q_sub			= _GGE_add_ps(q_sub, q_sub);   // 2 *(q.x * q.z - q.y * q.w), 2*(q.x * q.y - q.z * q.w), 2 * (q.y * q.z - q.x * q.w)
		q_sub			= _GGE_perm_yzxx_ps(q_sub);    // 2 *(q.x * q.y - q.z * q.w), 2*(q.y * q.z - q.x * q.w), 2 * (q.x * q.z - q.y * q.w)

		n128 q_xyz_2	= _GGE_mul_ps(q, q);           // q.x * q.x, q.y * q.y, q.z * q.z, q.w * q.w

		n128 q_yxx_2	= _GGE_perm_yxxx_ps(q_xyz_2);  // q.y * q.y, q.x * q.x, q.x * q.x
		n128 q_zzy_2	= _GGE_perm_zzyx_ps(q_xyz_2);  // q.z * q.z, q.z * q.z, q.y * q.y

		n128 oneMinus_2 = _GGE_sub_ps(f4_05, _GGE_add_ps(q_yxx_2, q_zzy_2)); // 0.5 - (q.y * q.y + q.z * q.z), 0.5 - (q.x * q.x + q.z * q.z), 0.5 - (q.x * q.x + q.y * q.y)
		oneMinus_2		= _GGE_add_ps(oneMinus_2, oneMinus_2); // 1.0 - 2 * (q.y * q.y + q.z * q.z), 1.0 - 2 * (q.x * q.x + q.z * q.z), 1.0 - 2 * (q.x * q.x + q.y * q.y)

		row0 = _GGE_blend_ps(oneMinus_2, q_add,	GGE_BLEND_MASK(1, 0, 0, 0));
		row0 = _GGE_blend_ps(row0, q_sub,		GGE_BLEND_MASK(1, 1, 0, 0));

		row1 = _GGE_blend_ps(oneMinus_2, q_add,	GGE_BLEND_MASK(0, 1, 0, 0));
		row1 = _GGE_blend_ps(row1, q_sub,		GGE_BLEND_MASK(0, 1, 1, 0));

		row2 = _GGE_blend_ps(oneMinus_2, q_add,	GGE_BLEND_MASK(0, 0, 1, 0));
		row2 = _GGE_blend_ps(row2, q_sub,		GGE_BLEND_MASK(1, 0, 1, 0));
	}

	GGE_inline void _GGE_quat_to_4x4_ps(const n128 q, n128& row0, n128& row1, n128& row2, n128& row3)
	{
		_GGE_quat_to_3x3_ps(q, row0, row1, row2);
		const n128 zeroLast = _GGE_castsi128_ps(_GGE_set_epi32((int)0xffffffff, (int)0xffffffff, (int)0xffffffff, 0));
		row0 = _GGE_and_ps(row0, zeroLast);
		row1 = _GGE_and_ps(row1, zeroLast);
		row2 = _GGE_and_ps(row2, zeroLast);
		row3 = _GGE_set_ps(0.0f, 0.0f, 0.0f, 1.0f);
	}

	// References
	// https://google.github.io/mathfu/quaternion_8h_source.html
	// https://www.euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/christian.htm
	// http://www.thetenthplanet.de/archives/1994
	// 
	// Actual implementation is the overkill version in
	// https://marc-b-reynolds.github.io/quaternions/2017/08/08/QuatRotMatrix.html
	// which has the least error of all
	inline void _GGE_3x3_to_quat_ps(const n128 row0, const n128 row1, const n128 row2, n128& q)
	{
		n128 m00 = _GGE_perm_xxxx_ps(row0);
		n128 m11 = _GGE_perm_yyyy_ps(row1);
		n128 m22 = _GGE_perm_zzzz_ps(row2);

		n128 m00_pnnp = _GGE_xor_ps(m00, _GGE_set_ps( 0.0f, -0.0f, -0.0f, 0.0f));
		n128 m11_npnp = _GGE_xor_ps(m11, _GGE_set_ps(-0.0f,  0.0f, -0.0f, 0.0f));
		n128 m22_nnpp = _GGE_xor_ps(m22, _GGE_set_ps(-0.0f, -0.0f,  0.0f, 0.0f));

		n128 t_4_1 = _GGE_add_ps(m00_pnnp, m11_npnp);
		n128 t_4_2 = _GGE_add_ps(m22_nnpp, f4_1);
		n128 d_4   = _GGE_add_ps(t_4_1, t_4_2);

		// float s1 = m12 - m21; float a1 = m12 + m21;
		// float s2 = m20 - m02; float a2 = m20 + m02;
		// float s3 = m01 - m10; float a3 = m01 + m10;

		n128 m01_m02_m10_m12 = _GGE_shuffle_ps(row0, row1, MaskY, MaskZ, MaskX, MaskZ);
		n128 m01_m02_m20_m21 = _GGE_shuffle_ps(row0, row2, MaskY, MaskZ, MaskX, MaskY);
		n128 m10_m12_m20_m21 = _GGE_shuffle_ps(row1, row2, MaskX, MaskZ, MaskX, MaskY);

		n128 m12_m20_m01_m12 = _GGE_shuffle_ps(m10_m12_m20_m21, m01_m02_m10_m12, MaskY, MaskZ, MaskX, MaskW);
		n128 m21_m02_m10_m21 = _GGE_shuffle_ps(m01_m02_m20_m21, m10_m12_m20_m21, MaskW, MaskY, MaskX, MaskW);
		n128 s1_s2_s3_s1     = _GGE_sub_ps(m12_m20_m01_m12, m21_m02_m10_m21);
		
		n128 m20_m12_m12_m20 = _GGE_perm_ps(m10_m12_m20_m21, MaskZ, MaskY, MaskY, MaskZ);
		n128 m02_m21_m21_m02 = _GGE_perm_ps(m01_m02_m20_m21, MaskY, MaskW, MaskW, MaskY);
		n128 a2_a1_a1_s2     = _GGE_add_ps(m20_m12_m12_m20, _GGE_xor_ps(m02_m21_m21_m02, _GGE_set_ps(0.0f, 0.0f, 0.0f, -0.0f)));
		
		n128 m01_m01_m20_m01 = _GGE_perm_ps(m01_m02_m20_m21, MaskX, MaskX, MaskZ, MaskX);
		n128 m10_m10_m02_m10 = _GGE_perm_ps(m01_m02_m10_m12, MaskZ, MaskZ, MaskY, MaskZ);
		n128 a3_a3_a2_s3     = _GGE_add_ps(m01_m01_m20_m01, _GGE_xor_ps(m10_m10_m02_m10, _GGE_set_ps(0.0f, 0.0f, 0.0f, -0.0f)));

		n128 q_positive = _GGE_mul_ps(d_4, d_4);
		q_positive      = _GGE_madd_ps(s1_s2_s3_s1, s1_s2_s3_s1, q_positive);
		q_positive      = _GGE_madd_ps(a2_a1_a1_s2, a2_a1_a1_s2, q_positive);
		q_positive      = _GGE_madd_ps(a3_a3_a2_s3, a3_a3_a2_s3, q_positive);
		q_positive      = _GGE_mul_ps(_GGE_sqrt_ps(q_positive), _GGE_set1_ps(0.25f));

		n128 condition = _GGE_cmpgt_ps(q_positive, _GGE_set_ps(0.25f, 0.25f, 0.0f, 0.0678711f));

		n128 sign_s1_s2_s3_0 = _GGE_and_ps(s1_s2_s3_s1, _GGE_set_ps(-0.0f, -0.0f, -0.0f, 0.0f));
		n128 sign_0_a3_a2_s1 = _GGE_and_ps(_GGE_blend_ps(a3_a3_a2_s3, s1_s2_s3_s1, GGE_BLEND_MASK(1, 1, 1, 0)), _GGE_set_ps(0.0f, -0.0f, -0.0f, -0.0f));
		n128 sign_a3_0_a1_s2 = _GGE_and_ps(_GGE_blend_ps(a3_a3_a2_s3, a2_a1_a1_s2, GGE_BLEND_MASK(1, 1, 0, 0)), _GGE_set_ps(-0.0f, 0.0f, -0.0f, -0.0f));
		n128 sign_a2_a1_0_s3 = _GGE_and_ps(_GGE_blend_ps(a2_a1_a1_s2, a3_a3_a2_s3, GGE_BLEND_MASK(1, 1, 0, 0)), _GGE_set_ps(-0.0f, -0.0f, 0.0f, -0.0f));

		n128 signs = sign_a2_a1_0_s3;
		signs = _GGE_sel_ps(signs, sign_a3_0_a1_s2, _GGE_perm_yyyy_ps(condition));
		signs = _GGE_sel_ps(signs, sign_0_a3_a2_s1, _GGE_perm_xxxx_ps(condition));
		signs = _GGE_sel_ps(signs, sign_s1_s2_s3_0, _GGE_perm_wwww_ps(condition));

		q = _GGE_or_ps(q_positive, signs);
	}

	GGE_inline quaternion	operator + (const quaternion& q1, const quaternion& q2) { return quaternion(_GGE_add_ps(q1.vec, q2.vec)); }
	GGE_inline quaternion&	operator += (quaternion& q1, const quaternion& q2) { q1 = q1 + q2; return q1; }

	GGE_inline quaternion	operator - (const quaternion& q1, const quaternion& q2) { return quaternion(_GGE_sub_ps(q1.vec, q2.vec)); }
	GGE_inline quaternion&	operator -= (quaternion& q1, const quaternion& q2) { q1 = q1 - q2; return q1; }

	GGE_inline quaternion	operator * (const quaternion& q, const float1& v) { return quaternion(_GGE_mul_ps(q.vec, _GGE_perm_xxxx_ps(v.vec))); }
	GGE_inline quaternion	operator * (const float1& v, const quaternion& q) { return q * v; }

	GGE_inline quaternion&	operator *= (quaternion& q, const float1& v) { q = q * v; return q; }

	//inline quaternion operator / (const quaternion& q1, const quaternion& q2) { return quaternion(_GGE_div_ps(q1._vec, q2._vec)); }
	//inline quaternion& operator /= (quaternion& q1, const quaternion& q2) { q1 = q1 / q2; return q1; }

	GGE_inline quaternion	operator / (const quaternion& q, const float1& v) { return quaternion(_GGE_div_ps(q.vec, _GGE_perm_xxxx_ps(v.vec))); }
	GGE_inline quaternion&	operator /= (quaternion& q, const float1& v) { q = q / v; return q; }

	GGE_inline quaternion	operator - (const quaternion& q) { return quaternion(_GGE_neg_ps(q.vec)); }
	GGE_inline float4		operator == (const quaternion& q1, const quaternion& q2) { return float4(_GGE_cmpeq1_ps(q1.vec, q2.vec)); }
	GGE_inline float4		operator != (const quaternion& q1, const quaternion& q2) { return float4(_GGE_cmpneq1_ps(q1.vec, q2.vec)); }
	GGE_inline float4		operator >  (const quaternion& q1, const quaternion& q2) { return float4(_GGE_cmpgt1_ps(q1.vec, q2.vec)); }
	GGE_inline float4		operator >= (const quaternion& q1, const quaternion& q2) { return float4(_GGE_cmpge1_ps(q1.vec, q2.vec)); }
	GGE_inline float4		operator <  (const quaternion& q1, const quaternion& q2) { return float4(_GGE_cmplt1_ps(q1.vec, q2.vec)); }
	GGE_inline float4		operator <= (const quaternion& q1, const quaternion& q2) { return float4(_GGE_cmple1_ps(q1.vec, q2.vec)); }

	GGE_inline quaternion	abs(const quaternion& q) { return quaternion(_GGE_abs_ps(q.vec)); }
	//GGE_inline float4		all(const quaternion& q) { return float4(_GGE_all1_ps(q.vec)); }
	//GGE_inline float4		any(const quaternion& q) { return float4(_GGE_any1_ps(q.vec)); }
	GGE_inline quaternion	conjugate(const quaternion& q) { return quaternion(_GGE_quat_conjugate_ps(q.vec)); }
	//clamp TODO
	GGE_inline float1		dot(const quaternion& q0, const quaternion& q1) { return float1(_GGE_dot4_ps(q0.vec, q1.vec)); }
	//GGE_inline quaternion exp(quaternion& q) { return quaternion(_GGE_exp_ps(q._vec)); }
	GGE_inline quaternion	frac(const quaternion& q) { return quaternion(_GGE_frac_ps(q.vec)); }
	GGE_inline quaternion	inverse(const quaternion& q) { return quaternion(_GGE_quat_inverse_ps(q.vec)); }
	GGE_inline float4		isfinite(const quaternion& q) { return float4(_GGE_andnot_ps(_GGE_isfinite_ps(q.vec), f4_1)); }
	GGE_inline float4		isinf(const quaternion& q) { return float4(_GGE_and_ps(_GGE_isinf_ps(q.vec), f4_1)); }
	GGE_inline float4		isnan(const quaternion& q) { return float4(_GGE_and_ps(_GGE_isnan_ps(q.vec), f4_1)); }
	GGE_inline float1		length(const quaternion& q) { return float1(_GGE_sqrt_ps(_GGE_dot4_ps(q.vec, q.vec))); }

	GGE_inline quaternion	lerp(const quaternion& q1, const quaternion& q2, const float1& a) { return quaternion(_GGE_quat_lerp_ps(q1.vec, q2.vec, a.vec)); }
	GGE_inline quaternion	nlerp(const quaternion& q1, const quaternion& q2, const float1& a) { return quaternion(_GGE_quat_nlerp_ps(q1.vec, q2.vec, a.vec)); }
	GGE_inline quaternion	slerp(const quaternion& q1, const quaternion& q2, const float1& a) { return quaternion(_GGE_quat_slerp_ps(q1.vec, q2.vec, a.vec)); }

	//GGE_inline quaternion log(const quaternion& q) { return quaternion(_GGE_log_ps(q._vec)); }
	GGE_inline quaternion	min(const quaternion& q1, const quaternion& q2) { return quaternion(_GGE_min_ps(q1.vec, q2.vec)); }
	GGE_inline quaternion	max(const quaternion& q1, const quaternion& q2) { return quaternion(_GGE_max_ps(q1.vec, q2.vec)); }
	GGE_inline quaternion	mul(const quaternion& q1, const quaternion& q2) { return quaternion(_GGE_quat_mul_ps(q1.vec, q2.vec)); }
	GGE_inline float3		mul(const float3& v, const quaternion& q) { return float3(_GGE_quat_mul_vec_ps(v.vec, q.vec)); }
	GGE_inline float3		mul(const quaternion& q, const float3& v) { return float3(_GGE_quat_mul_vec_inv_ps(q.vec, v.vec)); }
	GGE_inline quaternion	normalize(const quaternion& q) { return quaternion(_GGE_div_ps(q.vec, _GGE_perm_xxxx_ps(_GGE_sqrt_ps(_GGE_dot4_ps(q.vec, q.vec))))); }
	GGE_inline quaternion	saturate(const quaternion& q) { return quaternion(_GGE_sat_ps(q.vec)); }
	GGE_inline quaternion	sign(const quaternion& q) { return quaternion(_GGE_sign_ps(q.vec)); }

	// Transformation functions
	// https://ohtorii.hatenadiary.jp/entry/20150424/p1

	GGE_inline quaternion quaternion::rotation_axis(const float3& axis, float angle_rad)
	{
#if defined(GGE_LAYOUT_COORDINATES_FLIP_SIGN)
		angle_rad = -angle_rad;
#endif
		return quaternion(_GGE_quat_axis_angle_ps(axis.vec, _GGE_set1_ps(angle_rad)));
	}

	GGE_inline quaternion quaternion::rotation_axis_cosangle(const float3& axis, float cos_angle, float sign)
	{
#if defined(GGE_LAYOUT_COORDINATES_FLIP_SIGN)
		sign = -sign;
#endif
		return quaternion(_GGE_quat_axis_cosangle_ps(axis.vec, _GGE_set1_ps(cos_angle), _GGE_set1_ps(sign)));
	}
	
	GGE_inline quaternion quaternion::rotation_euler_zxy(const float3& angles_rad)
	{
#if defined(GGE_LAYOUT_COORDINATES_FLIP_SIGN)
		return quaternion(_GGE_quat_euler_zxy_ps(_GGE_neg_ps(angles_rad.vec)));
#else
		return quaternion(_GGE_quat_euler_zxy_ps(angles_rad.vec));
#endif
	}

	GGE_inline quaternion quaternion::rotation_x(float angle_rad)
	{
#if defined(GGE_LAYOUT_COORDINATES_FLIP_SIGN)
		angle_rad = -angle_rad;
#endif
		return quaternion(sinf(angle_rad * 0.5f), 0.0f, 0.0f, cosf(angle_rad * 0.5f));
	}

	GGE_inline quaternion quaternion::rotation_y(float angle_rad)
	{
#if defined(GGE_LAYOUT_COORDINATES_FLIP_SIGN)
		angle_rad = -angle_rad;
#endif
		return quaternion(0.0f, sinf(angle_rad * 0.5f), 0.0f, cosf(angle_rad * 0.5f)); 
	}

	GGE_inline quaternion quaternion::rotation_z(float angle_rad)
	{
#if defined(GGE_LAYOUT_COORDINATES_FLIP_SIGN)
		angle_rad = -angle_rad;
#endif
		return quaternion(0.0f, 0.0f, sinf(angle_rad * 0.5f), cosf(angle_rad * 0.5f));
	}

	GGE_inline void store(float* dst, const quaternion& src)
	{
		_GGE_store4_ps(dst, src.vec);
	}

	GGE_inline void load(quaternion& dst, const float* src)
	{
		_GGE_load4_ps(dst.vec, src);
	}
}