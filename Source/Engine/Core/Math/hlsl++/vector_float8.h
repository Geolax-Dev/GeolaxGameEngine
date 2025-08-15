#pragma once

#include <Core/Math/hlsl++/common.h>

//---------------//
// Float8 Vector //
//---------------//

#if defined(GGE_FLOAT8)

GGE_module_export namespace GGE
{
	// See http://http.developer.nvidia.com/Cg/fmod.html for reference
	// This implementation does not follow the reference
	// float2 c = frac(abs(a/b))*abs(b);
	// return (a < 0) ? -c : c;    // if ( a < 0 ) c = 0-c
	GGE_inline n256 _GGE256_fmod_ps(n256 x, n256 y)
	{
		n256 div = _GGE256_div_ps(x, y);
		n256 trnc = _GGE256_sub_ps(div, _GGE256_trunc_ps(div));
		return _GGE256_mul_ps(trnc, y);
	}

	GGE_inline void _GGE256_modf_ps(n256 x, n256& intPart, n256& fracPart)
	{
		intPart = _GGE256_trunc_ps(x);
		fracPart = _GGE256_sub_ps(x, intPart);
	}

	// Returns true if x is not +infinity or -infinity
	GGE_inline n256 _GGE256_isfinite_ps(n256 x)
	{
		return _GGE256_and_ps(_GGE256_and_ps(_GGE256_cmpneq_ps(x, f8_inf), _GGE256_cmpneq_ps(x, f8_minusinf)), _GGE256_cmpeq_ps(x, x));
	}

	// Returns true if x is +infinity or -infinity
	GGE_inline n256 _GGE256_isinf_ps(n256 x)
	{
		return _GGE256_or_ps(_GGE256_cmpeq_ps(x, f8_inf), _GGE256_cmpeq_ps(x, f8_minusinf));
	}

	// Returns true if x is nan
	GGE_inline n256 _GGE256_isnan_ps(n256 x)
	{
		return _GGE256_cmpneq_ps(x, x);
	}

	// Follows fxc in order of operations (a * (y - x) + x)
	GGE_inline n256 _GGE256_lerp_ps(n256 x, n256 y, n256 a)
	{
		n256 y_minus_x = _GGE256_sub_ps(y, x);
		n256 result = _GGE256_madd_ps(a, y_minus_x, x);
		return result;
	}

	// See http://jrfonseca.blogspot.co.uk/2008/09/fast-sse2-pow-tables-or-polynomials.html for derivation
	// Fonseca derives from here: http://forum.devmaster.net/t/approximate-math-library/11679
	inline n256 _GGE256_log2_ps(n256 x)
	{
		static const n256 log2_c0 = _GGE256_set1_ps( 3.1157899f);
		static const n256 log2_c1 = _GGE256_set1_ps(-3.3241990f);
		static const n256 log2_c2 = _GGE256_set1_ps( 2.5988452f);
		static const n256 log2_c3 = _GGE256_set1_ps(-1.2315303f);
		static const n256 log2_c4 = _GGE256_set1_ps( 3.1821337e-1f);
		static const n256 log2_c5 = _GGE256_set1_ps(-3.4436006e-2f);

		static const n256i exp    = _GGE256_set1_epi32(0x7F800000);
		static const n256i mant   = _GGE256_set1_epi32(0x007FFFFF);

		static const n256 minus127 = _GGE256_set1_ps(-127.0f);

		n256i i = _GGE256_castps_si256(x);

		n256 e = _GGE256_cvtepi32_ps(_GGE256_sub_epi32(_GGE256_srli_epi32(_GGE256_and_si128(i, exp), 23), _GGE256_set1_epi32(127)));

		n256 m = _GGE256_or_ps(_GGE256_castsi256_ps(_GGE256_and_si128(i, mant)), f8_1);

		n256 p;
		// Minimax polynomial fit of log2(x)/(x - 1), for x in range [1, 2[
		p = _GGE256_madd_ps(m, log2_c5, log2_c4);
		p = _GGE256_madd_ps(m, p, log2_c3);
		p = _GGE256_madd_ps(m, p, log2_c2);
		p = _GGE256_madd_ps(m, p, log2_c1);
		p = _GGE256_madd_ps(m, p, log2_c0);

		// This effectively increases the polynomial degree by one, but ensures that log2(1) == 0
		p = _GGE256_mul_ps(p, _GGE256_sub_ps(m, f8_1));

		n256 result = _GGE256_add_ps(p, e);

		// We can't compute a logarithm beyond this value, so we'll mark it as -infinity to indicate close to 0
		n256 ltminus127 = _GGE256_cmple_ps(result, minus127);
		result = _GGE256_sel_ps(result, f8_minusinf, ltminus127);

		// Check for negative values and return NaN
		n256 lt0 = _GGE256_cmplt_ps(x, f8_0);
		result = _GGE256_sel_ps(result, f8_NaN, lt0);

		return result;
	}

	GGE_inline n256 _GGE256_log10_ps(n256 x)
	{
		static const n256 invlog_2_10 = _GGE256_div_ps(f8_1, _GGE256_log2_ps(f8_10));
		return _GGE256_mul_ps(_GGE256_log2_ps(x), invlog_2_10);
	}

	GGE_inline n256 _GGE256_log_ps(n256 x)
	{
		static const n256 invlog_2_e = _GGE256_div_ps(f8_1, _GGE256_log2_ps(f8_e));
		return _GGE256_mul_ps(_GGE256_log2_ps(x), invlog_2_e);
	}

	// See http://jrfonseca.blogspot.co.uk/2008/09/fast-sse2-pow-tables-or-polynomials.html for derivation
	inline n256 _GGE256_exp2_ps(n256 x)
	{
		static const n256 exp2_c0 = _GGE256_set1_ps(1.0f);
		static const n256 exp2_c1 = _GGE256_set1_ps(6.9315308e-1f);
		static const n256 exp2_c2 = _GGE256_set1_ps(2.4015361e-1f);
		static const n256 exp2_c3 = _GGE256_set1_ps(5.5826318e-2f);
		static const n256 exp2_c4 = _GGE256_set1_ps(8.9893397e-3f);
		static const n256 exp2_c5 = _GGE256_set1_ps(1.8775767e-3f);

		static const n256 exp2_129 = _GGE256_set1_ps(129.00000f);
		static const n256 exp2_minus127 = _GGE256_set1_ps(-126.99999f);
		static const n256i exp2_127i = _GGE256_set1_epi32(127);

		n256i ipart;
		n256 fpart, expipart, expfpart;

		// Clamp values
		x = _GGE256_min_ps(x, exp2_129);
		x = _GGE256_max_ps(x, exp2_minus127);

		// ipart = int(x - 0.5)
		ipart = _GGE256_cvtps_epi32(_GGE256_sub_ps(x, f8_05));

		// fpart = x - ipart
		fpart = _GGE256_sub_ps(x, _GGE256_cvtepi32_ps(ipart));

		// expipart = (float) (1 << ipart)
		expipart = _GGE256_castsi256_ps(_GGE256_slli_epi32(_GGE256_add_epi32(ipart, exp2_127i), 23));

		// Minimax polynomial fit of 2^x, in range [-0.5, 0.5[
		expfpart = _GGE256_madd_ps(fpart, exp2_c5, exp2_c4);
		expfpart = _GGE256_madd_ps(fpart, expfpart, exp2_c3);
		expfpart = _GGE256_madd_ps(fpart, expfpart, exp2_c2);
		expfpart = _GGE256_madd_ps(fpart, expfpart, exp2_c1);
		expfpart = _GGE256_madd_ps(fpart, expfpart, exp2_c0);

		return _GGE256_mul_ps(expipart, expfpart);
	}

	GGE_inline n256 _GGE256_exp_ps(n256 x)
	{
		static const n256 log_2_e = _GGE256_log2_ps(f8_e);
		return _GGE256_exp2_ps(_GGE256_mul_ps(x, log_2_e));
	}

	// https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/smoothstep.xhtml
	// x = (x - edge0) / (edge1 - edge0);
	// 0,           x <= 0
	// 3x^2 - 2x^3, 0 < x < 1
	// 1,           x >= 1
	GGE_inline n256 _GGE256_smoothstep_ps(n256 edge0, n256 edge1, n256 x)
	{
		x = _GGE256_sat_ps(_GGE256_div_ps(_GGE256_sub_ps(x, edge0), _GGE256_sub_ps(edge1, edge0))); // x = saturate((x - edge0) / (edge1 - edge0))
		n256 result = _GGE256_mul_ps(_GGE256_mul_ps(x, x), _GGE256_sub_ps(f8_3, _GGE256_add_ps(x, x))); // result = x^2(3 - 2x)
		return result;
	}

	// Hlsl, glsl and Cg behavior is to swap the operands.
	// http://http.developer.nvidia.com/Cg/step.html
	// https://www.opengl.org/sdk/docs/man/html/step.xhtml
	GGE_inline n256 _GGE256_step_ps(n256 x, n256 y)
	{
		return _GGE256_cmpge1_ps(x, y);
	}

#if !defined(GGE_SIN_IMPLEMENTATION)

		// Uses a minimax polynomial fitted to the [-pi/2, pi/2] range
	inline n256 _GGE256_sin_ps(n256 x)
	{
		static const n256 sin_c1 = f8_1;
		static const n256 sin_c3 = _GGE256_set1_ps(-1.6665578e-1f);
		static const n256 sin_c5 = _GGE256_set1_ps( 8.3109378e-3f);
		static const n256 sin_c7 = _GGE256_set1_ps(-1.84477486e-4f);

		// Range reduction (into [-pi, pi] range)
		// Formula is x = x - round(x / 2pi) * 2pi

		x = _GGE256_subm_ps(x, _GGE256_round_ps(_GGE256_mul_ps(x, f8_inv2pi)), f8_2pi);

		n256 gtpi2      = _GGE256_cmpgt_ps(x, f8_pi2);
		n256 ltminusPi2 = _GGE256_cmplt_ps(x, f8_minusPi2);

		n256 ox = x;

		// Use identities/mirroring to remap into the range of the minimax polynomial
		x = _GGE256_sel_ps(x, _GGE256_sub_ps(f8_pi, ox), gtpi2);
		x = _GGE256_sel_ps(x, _GGE256_sub_ps(f8_minusPi, ox), ltminusPi2);

		n256 x2 = _GGE256_mul_ps(x, x);
		n256 result;
		result = _GGE256_madd_ps(x2, sin_c7, sin_c5);
		result = _GGE256_madd_ps(x2, result, sin_c3);
		result = _GGE256_madd_ps(x2, result, sin_c1);
		result = _GGE256_mul_ps(result, x);
		return result;
	}

#endif

#if !defined(GGE_COS_IMPLEMENTATION)

	GGE_inline n256 _GGE256_cos_ps(n256 x)
	{
		return _GGE256_sin_ps(_GGE256_sub_ps(f8_pi2, x));
	}

#endif

#if !defined(GGE_TAN_IMPLEMENTATION)

	// Uses a minimax polynomial fitted to the [-pi/4, pi/4] range
	inline n256 _GGE256_tan_ps(n256 x)
	{
		static const n256 tan_c1 = f8_1;
		static const n256 tan_c3 = _GGE256_set1_ps(3.329923284e-1f);
		static const n256 tan_c5 = _GGE256_set1_ps(1.374784343e-1f);
		static const n256 tan_c7 = _GGE256_set1_ps(3.769634481e-2f);
		static const n256 tan_c9 = _GGE256_set1_ps(4.609737727e-2f);

		// Range reduction (into [-pi/2, pi/2] range)
		// Formula is x = x - round(x / pi) * pi

		x = _GGE256_subm_ps(x, _GGE256_round_ps(_GGE256_mul_ps(x, f8_invPi)), f8_pi);

		n256 gtPi4      = _GGE256_cmpgt_ps(x, f8_pi4);
		n256 ltMinusPi4 = _GGE256_cmplt_ps(x, f8_minusPi4);
		n256 gtltPi4    = _GGE256_or_ps(gtPi4, ltMinusPi4);

		x = _GGE256_sel_ps(x, _GGE256_sub_ps(f8_pi2, x), gtPi4);
		x = _GGE256_sel_ps(x, _GGE256_sub_ps(f8_minusPi2, x), ltMinusPi4);

		n256 x2 = _GGE256_mul_ps(x, x);
		n256 centerResult;
		centerResult = _GGE256_madd_ps(x2, tan_c9, tan_c7);
		centerResult = _GGE256_madd_ps(x2, centerResult, tan_c5);
		centerResult = _GGE256_madd_ps(x2, centerResult, tan_c3);
		centerResult = _GGE256_madd_ps(x2, centerResult, tan_c1);
		centerResult = _GGE256_mul_ps(centerResult, x);				// Valid within [-pi/4, pi/4]

		n256 lateralResult = _GGE256_div_ps(f8_1, centerResult); // Valid in [-pi/2, -pi/4) U (pi/4, pi/2]

		n256 result = _GGE256_sel_ps(centerResult, lateralResult, gtltPi4);

		return result;
	}

#endif

#if !defined(GGE_ACOS_IMPLEMENTATION)

	// Max error vs. std::acos
	// SSE : 1.54972076e-6
	inline n256 _GGE256_acos_ps(n256 x)
	{
		static const n256 asinacos_c0 = f8_pi2;
		static const n256 asinacos_c1 = _GGE256_set1_ps(-2.145329213e-1f);
		static const n256 asinacos_c2 = _GGE256_set1_ps(8.797308928e-2f);
		static const n256 asinacos_c3 = _GGE256_set1_ps(-4.513026638e-2f);
		static const n256 asinacos_c4 = _GGE256_set1_ps(1.946746668e-2f);
		static const n256 asinacos_c5 = _GGE256_set1_ps(-4.360132611e-3f);

		// We use the trigonometric identity acos(x) = pi - acos(-x) to mirror [0, 1]
		// into the [-1, 0] range
		n256 ltZero = _GGE256_cmplt_ps(x, f8_0);
		x = _GGE256_sel_ps(x, _GGE256_neg_ps(x), ltZero);

		n256 sqrt1minusx = _GGE256_sqrt_ps(_GGE256_sub_ps(f8_1, x));

		n256 result;
		result = _GGE256_madd_ps(x, asinacos_c5, asinacos_c4);
		result = _GGE256_madd_ps(x, result, asinacos_c3);
		result = _GGE256_madd_ps(x, result, asinacos_c2);
		result = _GGE256_madd_ps(x, result, asinacos_c1);
		result = _GGE256_madd_ps(x, result, asinacos_c0);
		result = _GGE256_mul_ps(result, sqrt1minusx);

		result = _GGE256_sel_ps(result, _GGE256_sub_ps(f8_pi, result), ltZero); // Select the [0, 1] or [-1, 0] result

		n256 gtltOne = _GGE256_cmpgt_ps(_GGE256_abs_ps(x), f8_1);	// > 1 || < -1
		result = _GGE256_sel_ps(result, f8_NaN, gtltOne);			// Select NaN if input out of range

		return result;
	}

#endif

#if !defined(GGE_ASIN_IMPLEMENTATION)

	// Max error vs. std::asin
	// SSE : 1.5348196e-6
	inline n256 _GGE256_asin_ps(n256 x)
	{
		static const n256 asinacos_c0 = f8_pi2;
		static const n256 asinacos_c1 = _GGE256_set1_ps(-2.145329213e-1f);
		static const n256 asinacos_c2 = _GGE256_set1_ps(8.797308928e-2f);
		static const n256 asinacos_c3 = _GGE256_set1_ps(-4.513026638e-2f);
		static const n256 asinacos_c4 = _GGE256_set1_ps(1.946746668e-2f);
		static const n256 asinacos_c5 = _GGE256_set1_ps(-4.360132611e-3f);

		// We use the trigonometric identity asin(x) = -asin(-x) to mirror [0, 1] into the [-1, 0] range
		n256 ltZero = _GGE256_cmplt_ps(x, f8_0);
		x = _GGE256_sel_ps(x, _GGE256_neg_ps(x), ltZero);

		n256 sqrt1minusx = _GGE256_sqrt_ps(_GGE256_sub_ps(f8_1, x));

		n256 result;
		result = _GGE256_madd_ps(x, asinacos_c5, asinacos_c4);
		result = _GGE256_madd_ps(x, result, asinacos_c3);
		result = _GGE256_madd_ps(x, result, asinacos_c2);
		result = _GGE256_madd_ps(x, result, asinacos_c1);
		result = _GGE256_madd_ps(x, result, asinacos_c0);
		result = _GGE256_subm_ps(f8_pi2, result, sqrt1minusx); // pi/2 - result * sqrt(1 - x)

		result = _GGE256_sel_ps(result, _GGE256_neg_ps(result), ltZero);	// Select the [0, 1] or [-1, 0] result

		n256 gtltOne = _GGE256_cmpgt_ps(_GGE256_abs_ps(x), f8_1);		// > 1 || < -1
		result = _GGE256_sel_ps(result, f8_NaN, gtltOne);				// Select NaN if input out of range

		return result;
	}

#endif

#if !defined(GGE_ATAN_IMPLEMENTATION)

	// Max error vs. std::atan
	// SSE : 2.74181366e-6
	inline n256 _GGE256_atan_ps(n256 x)
	{
		static const n256 atan_c1 = f8_1;
		static const n256 atan_c3 = _GGE256_set1_ps(-3.329452768e-1f);
		static const n256 atan_c5 = _GGE256_set1_ps(1.949865716e-1f);
		static const n256 atan_c7 = _GGE256_set1_ps(-1.192157627e-1f);
		static const n256 atan_c9 = _GGE256_set1_ps(5.506335136e-2f);
		static const n256 atan_c11 = _GGE256_set1_ps(-1.249072006e-2f);

		n256 ltgtOne = _GGE256_cmpgt_ps(_GGE256_abs_ps(x), f8_1); // Check if outside the [-1, 1] range
		n256 gtOne = _GGE256_cmpgt_ps(x, f8_1);				 // Check if input > 1 (as we need to select the constant later)

		x = _GGE256_sel_ps(x, _GGE256_div_ps(f8_1, x), ltgtOne);

		n256 x2 = _GGE256_mul_ps(x, x);
		n256 result;
		result = _GGE256_madd_ps(x2, atan_c11, atan_c9);
		result = _GGE256_madd_ps(x2, result, atan_c7);
		result = _GGE256_madd_ps(x2, result, atan_c5);
		result = _GGE256_madd_ps(x2, result, atan_c3);
		result = _GGE256_madd_ps(x2, result, atan_c1);
		result = _GGE256_mul_ps(x, result);

		// if(abs(x) < 1)	return result
		// if(x >  1)		return pi/2 - result
		// if(x < -1)		return -pi/2 - result

		n256 outRangeK = _GGE256_sel_ps(f8_minusPi2, f8_pi2, gtOne);
		n256 outRangeResult = _GGE256_sub_ps(outRangeK, result);

		result = _GGE256_sel_ps(result, outRangeResult, ltgtOne);
		return result;
	}

#endif

#if !defined(GGE_ATAN2_IMPLEMENTATION)

	// Use definition from Wikipedia: https://en.wikipedia.org/wiki/Atan2
	inline n256 _GGE256_atan2_ps(n256 y, n256 x)
	{
		n256 isxgt0 = _GGE256_cmpgt_ps(x, _GGE256_setzero_ps()); // x > 0
		n256 isxeq0 = _GGE256_cmpeq_ps(x, _GGE256_setzero_ps()); // x == 0
		n256 isxlt0 = _GGE256_cmplt_ps(x, _GGE256_setzero_ps()); // x < 0

		n256 isyge0 = _GGE256_cmpge_ps(y, _GGE256_setzero_ps()); // y >= 0
		n256 isygt0 = _GGE256_cmpgt_ps(y, _GGE256_setzero_ps()); // y > 0
		n256 isylt0 = _GGE256_cmplt_ps(y, _GGE256_setzero_ps()); // y < 0

		n256 atanydivx = _GGE256_atan_ps(_GGE256_div_ps(y, x)); // atan(y / x)
		n256 atanydivxpluspi = _GGE256_add_ps(atanydivx, f8_pi);   // atan(y / x) + pi
		n256 atanydivxminuspi = _GGE256_sub_ps(atanydivx, f8_pi);  // atan(y / x) - pi

		n256 isxlt0yge0 = _GGE256_and_ps(isxlt0, isyge0);
		n256 isxlt0ylt0 = _GGE256_and_ps(isxlt0, isylt0);
		n256 isxeq0ygt0 = _GGE256_and_ps(isxeq0, isygt0);
		n256 isxeq0ylt0 = _GGE256_and_ps(isxeq0, isylt0);

		// If x == 0 and y == 0, return NaN
		n256 result = f8_NaN;
		result = _GGE256_sel_ps(result, atanydivx, isxgt0);
		result = _GGE256_sel_ps(result, atanydivxpluspi, isxlt0yge0);
		result = _GGE256_sel_ps(result, atanydivxminuspi, isxlt0ylt0);
		result = _GGE256_sel_ps(result, f8_pi2, isxeq0ygt0);
		result = _GGE256_sel_ps(result, f8_minusPi2, isxeq0ylt0);
		return result;
	}

#endif

#if !defined(GGE_SINH_IMPLEMENTATION)

	// sinh(x) = (exp(x) - exp(-x)) / 2.0
	GGE_inline n256 _GGE256_sinh_ps(n256 x)
	{
		n256 expx = _GGE256_exp_ps(x);
		n256 exp_minusx = _GGE256_rcp_ps(expx);
		return _GGE256_mul_ps(_GGE256_sub_ps(expx, exp_minusx), f8_05);
	}

#endif

#if !defined(GGE_COSH_IMPLEMENTATION)

	// cosh(x) = (exp(x) + exp(-x)) / 2.0
	GGE_inline n256 _GGE256_cosh_ps(n256 x)
	{
		n256 expx = _GGE256_exp_ps(x);
		n256 exp_minusx = _GGE256_rcp_ps(expx);
		return _GGE256_mul_ps(_GGE256_add_ps(expx, exp_minusx), f8_05);
	}

#endif

#if !defined(GGE_TANH_IMPLEMENTATION)

	// tanh(x) = (exp(x) - exp(-x)) / (exp(x) + exp(-x))
	GGE_inline n256 _GGE256_tanh_ps(n256 x)
	{
		n256 expx = _GGE256_exp_ps(x);
		n256 exp_minusx = _GGE256_rcp_ps(expx);
		return _GGE256_div_ps(_GGE256_sub_ps(expx, exp_minusx), _GGE256_add_ps(expx, exp_minusx));
	}

#endif

	GGE_inline n256 _GGE256_reflect8_ps(n256 i, n256 n)
	{
		return _GGE256_sub_ps(i, _GGE256_mul_ps(f8_2, _GGE256_mul_ps(n, _GGE256_perm_xxxx_xxxx_ps(_GGE256_dot8_ps(i, n)))));
	}

	GGE_inline n256 _GGE256_refract8_ps(n256 i, n256 n, n128 ior)
	{
		n256 NdotI = _GGE256_dot8_ps(i, n);

		n256 NdotI4 = _GGE256_perm_xxxx_xxxx_ps(NdotI); // Propagate to all components (dot lives in x)

		n256 ior8 = _GGE256_set128_ps(ior, ior);

		n256 ior2      = _GGE256_mul_ps(ior8, ior8);             // ior^2
		n256 invNdotI2 = _GGE256_subm_ps(f8_1, NdotI4, NdotI4);  // 1.0 - dot(n, i)^2
		n256 k         = _GGE256_subm_ps(f8_1, ior2, invNdotI2); // k = 1.0 - ior^2 * (1.0 - dot(n, i)^2)

		n256 sqrtK          = _GGE256_sqrt_ps(k);                       // sqrt(k)
		n256 iorNdotISqrtk  = _GGE256_madd_ps(ior8, NdotI4, sqrtK);     // ior * dot(n, i) + sqrt(k)
		n256 iorNdotISqrtkn = _GGE256_mul_ps(iorNdotISqrtk, n);         // (ior * dot(n, i) + sqrt(k)) * n
		n256 result         = _GGE256_msub_ps(ior8, i, iorNdotISqrtkn); // ior * i - (ior * dot(n, i) + sqrt(k)) * n

		n256 klt0 = _GGE256_cmplt_ps(k, _GGE256_setzero_ps()); // Whether k was less than 0

		return _GGE256_sel_ps(result, _GGE256_setzero_ps(), klt0); // Select between 0 and the result 
	}

	struct GGE_nodiscard float8
	{
		GGE_inline float8() GGE_noexcept {}
		GGE_inline float8(const float8& f) GGE_noexcept : vec(f.vec) {}
		explicit GGE_inline float8(n256 vec) GGE_noexcept : vec(vec) {}
		explicit GGE_inline float8(const float1& f) GGE_noexcept : vec(_GGE256_set128_ps(_GGE_perm_xxxx_ps(f.vec), _GGE_perm_xxxx_ps(f.vec))) {}

		template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
		GGE_inline float8(T1 f1, T2 f2, T3 f3, T4 f4, T5 f5, T6 f6, T7 f7, T8 f8, GGE_enable_if_number_8(T1, T2, T3, T4, T5, T6, T7, T8)) 
			GGE_noexcept : vec(_GGE256_set_ps(float(f1), float(f2), float(f3), float(f4), float(f5), float(f6), float(f7), float(f8))) {}

		template<typename T>
		float8(T f, GGE_enable_if_number(T)) GGE_noexcept : vec(_GGE256_set1_ps(float(f))) {}

		/*GGE_inline float8(const float1& f1, const float1& f2, const float1& f3, const float1& f4) { vec = _GGE_blend_ps(_GGE_shuf_xxxx_ps(f1.vec, f3.vec), _GGE_shuf_xxxx_ps(f2.vec, f4.vec), GGE_BLEND_MASK(1, 0, 1, 0)); }

		GGE_inline float8(const float2& f1, const float1& f2, const float1& f3) { vec = _GGE_blend_ps(_GGE_shuf_xyxx_ps(f1.vec, f2.vec), _GGE_perm_xxxx_ps(f3.vec), GGE_BLEND_MASK(1, 1, 1, 0)); }
		GGE_inline float8(const float1& f1, const float2& f2, const float1& f3) { vec = _GGE_blend_ps(_GGE_shuf_xxxx_ps(f1.vec, f3.vec), _GGE_perm_xxyx_ps(f2.vec), GGE_BLEND_MASK(1, 0, 0, 1)); }
		GGE_inline float8(const float1& f1, const float1& f2, const float2& f3) { vec = _GGE_blend_ps(_GGE_shuf_xxxy_ps(f1.vec, f3.vec), _GGE_perm_xxxx_ps(f2.vec), GGE_BLEND_MASK(1, 0, 1, 1)); }

		GGE_inline float8(const float2& f1, const float2& f2) { vec = _GGE_shuf_xyxy_ps(f1.vec, f2.vec); }

		GGE_inline float8(const float1& f1, const float3& f2) { vec = _GGE_blend_ps(f1.vec, _GGE_perm_xxyz_ps(f2.vec), GGE_BLEND_MASK(1, 0, 0, 0)); }
		GGE_inline float8(const float3& f1, const float1& f2) { vec = _GGE_blend_ps(f1.vec, _GGE_perm_xxxx_ps(f2.vec), GGE_BLEND_MASK(1, 1, 1, 0)); }

		GGE_inline float8(const int4& i);*/

		GGE_inline float8(float8&& f) GGE_noexcept : vec(f.vec) {}
		GGE_inline float8& operator = (float8&& f) GGE_noexcept { vec = f.vec; return *this; }

		float& operator[](int N)
		{
			GGE_assert(N >= 0 && N <= 7);
			return f32[N];
		}

		const float& operator[](int N) const
		{
			GGE_assert(N >= 0 && N <= 7);
			return f32[N];
		}

		union
		{
			n256 vec;
			float f32[8];
		};
	};

	// We cannot have swizzle members like with smaller vectors, the combinatorial explosion of template instantiations is
	// impossible to compile. Therefore, a free function seems like the most convenient interface, especially if we plan to
	// introduce float16 later.
	template<int X, int Y, int Z, int W, int A, int B, int C, int D>
	float8 swizzle(const float8& v)
	{
		return float8(_GGE256_perm_ps(v.vec, X, Y, Z, W, A, B, C, D));
	}

	// Operators

	GGE_inline float8 operator + (const float8& f1, const float8& f2) { return float8(_GGE256_add_ps(f1.vec, f2.vec)); }

	GGE_inline float8 operator + (const float8& f1, const float1& f2)
	{
		n128 perm_xxxx = _GGE_perm_xxxx_ps(f2.vec);
		return float8(_GGE256_add_ps(f1.vec, _GGE256_set128_ps(perm_xxxx, perm_xxxx)));
	}

	GGE_inline float8 operator - (const float8& f1, const float8& f2) { return float8(_GGE256_sub_ps(f1.vec, f2.vec)); }

	GGE_inline float8 operator - (const float8& f1, const float1& f2)
	{
		n128 perm_xxxx = _GGE_perm_xxxx_ps(f2.vec);
		return float8(_GGE256_sub_ps(f1.vec, _GGE256_set128_ps(perm_xxxx, perm_xxxx)));
	}

	GGE_inline float8 operator * (const float8& f1, const float8& f2) { return float8(_GGE256_mul_ps(f1.vec, f2.vec)); }

	GGE_inline float8 operator * (const float8& f1, const float1& f2)
	{
		n128 perm_xxxx = _GGE_perm_xxxx_ps(f2.vec);
		return float8(_GGE256_mul_ps(f1.vec, _GGE256_set128_ps(perm_xxxx, perm_xxxx)));
	}

	GGE_inline float8 operator / (const float8& f1, const float8& f2) { return float8(_GGE256_div_ps(f1.vec, f2.vec)); }

	GGE_inline float8 operator / (const float8& f1, const float1& f2)
	{
		n128 perm_xxxx = _GGE_perm_xxxx_ps(f2.vec);
		return float8(_GGE256_div_ps(f1.vec, _GGE256_set128_ps(perm_xxxx, perm_xxxx)));
	}

	GGE_inline float8 operator % (const float8& f1, const float8& f2) { return float8(_GGE256_fmod_ps(f1.vec, f2.vec)); }

	GGE_inline float8 operator % (const float8& f1, const float1& f2)
	{
		n128 perm_xxxx = _GGE_perm_xxxx_ps(f2.vec);
		return float8(_GGE256_fmod_ps(f1.vec, _GGE256_set128_ps(perm_xxxx, perm_xxxx)));
	}

	GGE_inline float8 operator - (const float8& f) { return float8(_GGE256_neg_ps(f.vec)); }

	GGE_inline float8& operator += (float8& f1, const float8& f2) { f1 = f1 + f2; return f1; }

	GGE_inline float8& operator -= (float8& f1, const float8& f2) { f1 = f1 - f2; return f1; }

	GGE_inline float8& operator *= (float8& f1, const float8& f2) { f1 = f1 * f2; return f1; }

	GGE_inline float8& operator /= (float8& f1, const float8& f2) { f1 = f1 / f2; return f1; }

	GGE_inline float8& operator %= (float8& f1, const float8& f2) { f1 = f1 % f2; return f1; }


	// Pre-increment

	GGE_inline float8& operator ++ (float8& f) { f = f + float8(f8_1); return f; }
	GGE_inline float8& operator -- (float8& f) { f = f - float8(f8_1); return f; }

	// Post-increment

	GGE_inline float8 operator ++ (float8& f, int) { float8 tmp = f; f = f + float8(f8_1); return tmp; }
	GGE_inline float8 operator -- (float8& f, int) { float8 tmp = f; f = f - float8(f8_1); return tmp; }

	//------------------------------------------------------------------------------------------------------------------------
	// float1 and swizzle1 need special overloads to disambiguate between our operators/functions and built-in float operators
	// and functions that are part of common headers such as cmath, math.h, algorithm, etc
	//------------------------------------------------------------------------------------------------------------------------

	template<typename T> GGE_inline GGE_enable_if_return(T, float8) operator + (const float8& f1, T f2) { return f1 + float8(f2); }

	template<typename T> GGE_inline GGE_enable_if_return(T, float8) operator + (T f1, const float8& f2) { return float8(f1) + f2; }

	template<typename T> GGE_inline GGE_enable_if_return(T, float8) operator - (const float8& f1, T f2) { return f1 - float8(f2); }

	template<typename T> GGE_inline GGE_enable_if_return(T, float8) operator - (T f1, const float8& f2) { return float8(f1) - f2; }

	template<typename T> GGE_inline GGE_enable_if_return(T, float8) operator * (const float8& f1, T f2) { return f1 * float8(f2); }

	template<typename T> GGE_inline GGE_enable_if_return(T, float8) operator * (T f1, const float8& f2) { return float8(f1) * f2; }

	template<typename T> GGE_inline GGE_enable_if_return(T, float8) operator / (const float8& f1, T f2) { return f1 / float8(f2); }

	template<typename T> GGE_inline GGE_enable_if_return(T, float8) operator / (T f1, const float8& f2) { return float8(f1) / f2; }

	template<typename T> GGE_inline GGE_enable_if_return(T, float8) operator % (const float8& f1, T f2) { return f1 % float8(f2); }

	template<typename T> GGE_inline GGE_enable_if_return(T, float8) operator % (T f1, const float8& f2) { return float8(f1) % f2; }

	GGE_inline float8 operator == (const float8& f1, const float8& f2) { return float8(_GGE256_cmpeq1_ps(f1.vec, f2.vec)); }
	
	GGE_inline float8 operator != (const float8& f1, const float8& f2) { return float8(_GGE256_cmpneq1_ps(f1.vec, f2.vec)); }
	
	GGE_inline float8 operator > (const float8& f1, const float8& f2) { return float8(_GGE256_cmpgt1_ps(f1.vec, f2.vec)); }
	
	GGE_inline float8 operator >= (const float8& f1, const float8& f2) { return float8(_GGE256_cmpge1_ps(f1.vec, f2.vec)); }
	
	GGE_inline float8 operator < (const float8& f1, const float8& f2) { return float8(_GGE256_cmplt1_ps(f1.vec, f2.vec)); }
	
	GGE_inline float8 operator <= (const float8& f1, const float8& f2) { return float8(_GGE256_cmple1_ps(f1.vec, f2.vec)); }

	GGE_inline float8 abs(const float8& f) { return float8(_GGE256_abs_ps(f.vec)); }

	GGE_inline float8 acos(const float8& f) { return float8(_GGE256_acos_ps(f.vec)); }

	GGE_inline bool all(const float8& f) { return _GGE256_all8_ps(f.vec); }

	GGE_inline bool any(const float8& f) { return _GGE256_any8_ps(f.vec); }

	GGE_inline float8 asin(const float8& f) { return float8(_GGE256_asin_ps(f.vec)); }

	GGE_inline float8 atan(const float8& f) { return float8(_GGE256_atan_ps(f.vec)); }

	GGE_inline float8 atan2(const float8& y, const float8& x) { return float8(_GGE256_atan2_ps(y.vec, x.vec)); }

	GGE_inline float8 ceil(const float8& f) { return float8(_GGE256_ceil_ps(f.vec)); }

	GGE_inline float8 clamp(const float8& f, const float8& minf, const float8& maxf) { return float8(_GGE256_clamp_ps(f.vec, minf.vec, maxf.vec)); }

	GGE_inline float8 copysign(const float8& from, const float8& to) { return float8(_GGE256_copysign_ps(from.vec, to.vec)); }

	GGE_inline float8 cos(const float8& f) { return float8(_GGE256_cos_ps(f.vec)); }

	GGE_inline float8 cosh(const float8& f) { return float8(_GGE256_cosh_ps(f.vec)); }

	GGE_inline float8 degrees(const float8& f) { return float8(_GGE256_mul_ps(f.vec, f8_rad2deg)); }

	GGE_inline float1 dot(const float8& f1, const float8& f2) { return float1(_GGE256_low_ps(_GGE256_dot8_ps(f1.vec, f2.vec))); }

	GGE_inline float8 exp(const float8& f) { return float8(_GGE256_exp_ps(f.vec)); }

	GGE_inline float8 exp2(const float8& f) { return float8(_GGE256_exp2_ps(f.vec)); }

	GGE_inline float8 floor(const float8& f) { return float8(_GGE256_floor_ps(f.vec)); }

	GGE_inline float8 fmod(const float8& f1, const float8& f2) { return float8(_GGE256_fmod_ps(f1.vec, f2.vec)); }

	GGE_inline float8 frac(const float8& f) { return float8(_GGE256_frac_ps(f.vec)); }

	GGE_inline float8 isfinite(const float8& f) { return float8(_GGE256_andnot_ps(_GGE256_isfinite_ps(f.vec), f8_1)); }

	GGE_inline float8 isinf(const float8& f) { return float8(_GGE256_and_ps(_GGE256_isinf_ps(f.vec), f8_1)); }

	GGE_inline float8 isnan(const float8& f) { return float8(_GGE256_and_ps(_GGE256_isnan_ps(f.vec), f8_1)); }

	GGE_inline float1 length(const float8& f) { return float1(_GGE256_low_ps(_GGE256_sqrt_ps(_GGE256_dot8_ps(f.vec, f.vec)))); }

	GGE_inline float8 lerp(const float8& f1, const float8& f2, const float8& a) { return float8(_GGE256_lerp_ps(f1.vec, f2.vec, a.vec)); }

	GGE_inline float8 log(const float8& f) { return float8(_GGE256_log_ps(f.vec)); }

	GGE_inline float8 log2(const float8& f) { return float8(_GGE256_log2_ps(f.vec)); }

	GGE_inline float8 log10(const float8& f) { return float8(_GGE256_log10_ps(f.vec)); }

	GGE_inline float8 min(const float8& f1, const float8& f2) { return float8(_GGE256_min_ps(f1.vec, f2.vec)); }

	GGE_inline float8 mad(const float8& f1, const float8& f2, const float8& f3) { return float8(_GGE256_madd_ps(f1.vec, f2.vec, f3.vec)); }

	GGE_inline float8 max(const float8& f1, const float8& f2) { return float8(_GGE256_max_ps(f1.vec, f2.vec)); }

	GGE_inline float8 modf(const float8& f1, float8& integerPart)
	{
		n256 signedFrac, signedInteger;
		_GGE256_modf_ps(f1.vec, signedInteger, signedFrac);
		integerPart = float8(signedInteger);
		return float8(signedFrac);
	}

	GGE_inline float8 normalize(const float8& f) { return float8(_GGE256_div_ps(f.vec, _GGE256_perm_xxxx_xxxx_ps(_GGE256_sqrt_ps(_GGE256_dot8_ps(f.vec, f.vec))))); }

	GGE_inline float8 pow(const float8& f1, const float8& f2) { return float8(_GGE256_exp2_ps(_GGE256_mul_ps(f2.vec, _GGE256_log2_ps(f1.vec)))); }

	GGE_inline float8 radians(const float8& f) { return float8(_GGE256_mul_ps(f.vec, f8_deg2rad)); }

	GGE_inline float8 rcp(const float8& f) { return float8(_GGE256_rcp_ps(f.vec)); }

	GGE_inline float8 reflect(const float8& i, const float8& n) { return float8(_GGE256_reflect8_ps(i.vec, n.vec)); }

	GGE_inline float8 refract(const float8& i, const float8& n, const float1& ior) { return float8(_GGE256_refract8_ps(i.vec, n.vec, ior.vec)); }

	GGE_inline float8 rsqrt(const float8& f) { return float8(_GGE256_rsqrt_ps(f.vec)); }

	GGE_inline float8 round(const float8& f) { return float8(_GGE256_round_ps(f.vec)); }

	GGE_inline float8 saturate(const float8& f) { return float8(_GGE256_sat_ps(f.vec)); }

	GGE_inline float8 sign(const float8& f) { return float8(_GGE256_sign_ps(f.vec)); }

	GGE_inline float8 sin(const float8& f) { return float8(_GGE256_sin_ps(f.vec)); }

	GGE_inline void sincos(const float8& f, float8& s, float8& c) { s = float8(_GGE256_sin_ps(f.vec)); c = float8(_GGE256_cos_ps(f.vec)); }

	GGE_inline float8 sinh(const float8& f) { return float8(_GGE256_sinh_ps(f.vec)); }

	GGE_inline float8 smoothstep(const float8& f1, const float8& f2, const float8& a) { return float8(_GGE256_smoothstep_ps(f1.vec, f2.vec, a.vec)); }

	GGE_inline float8 sqrt(const float8& f) { return float8(_GGE256_sqrt_ps(f.vec)); }

	GGE_inline float8 step(const float8& f1, const float8& f2) { return float8(_GGE256_step_ps(f1.vec, f2.vec)); }

	GGE_inline float8 tan(const float8& f) { return float8(_GGE256_tan_ps(f.vec)); }

	GGE_inline float8 tanh(const float8& f) { return float8(_GGE256_tanh_ps(f.vec)); }

	GGE_inline float8 trunc(const float8& f) { return float8(_GGE256_trunc_ps(f.vec)); }

	GGE_inline void store(float* dst, const float8& src)
	{
		_GGE256_store8_ps(dst, src.vec);
	}

	GGE_inline void load(float8& dst, const float* src)
	{
		_GGE256_load8_ps(dst.vec, src);
	}
}

#endif