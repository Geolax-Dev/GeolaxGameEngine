#pragma once

#include <Core/Math/hlsl++/common.h>

//---------------//
// Double Vector //
//---------------//

#if defined(GGE_DOUBLE)

GGE_module_export namespace GGE
{
	union BitMaskDouble
	{
		uint64_t i;
		double d;
		explicit BitMaskDouble(uint64_t i) : i(i) {}
		explicit BitMaskDouble(double d) : d(d) {}
	};

	const BitMaskDouble dfffMask((uint64_t)0xffffffffffffffffu); // Negative NaN
	const BitMaskDouble dNanMask((uint64_t)0x7fffffffffffffffu); // Positive NaN
	const BitMaskDouble dInfMask((uint64_t)0x7f80000000000000u);
	const BitMaskDouble dMinusinfMask((uint64_t)0xff80000000000000u);
	const BitMaskDouble dAbsMask((uint64_t)0x7fffffffffffffffu);
	const BitMaskDouble dNegMask((uint64_t)0x8000000000000000u);

	//----------
	// Constants
	//----------

	const n128d d2_1            = _GGE_set1_pd(1.0);
	const n128d d2minusOne      = _GGE_set1_pd(-1.0);

	const n128d d2_NaN          = _GGE_set1_pd(dNanMask.d);      // Quiet NaN
	const n128d d2_inf          = _GGE_set1_pd(dInfMask.d);      // Infinity
	const n128d d2_minusinf     = _GGE_set1_pd(dMinusinfMask.d); // -Infinity
	const n128d d2_fff          = _GGE_set1_pd(dfffMask.d);      // 0xffffffff

	const n128d d2negativeMask  = _GGE_set1_pd(dNegMask.d);
	const n128d d2absMask       = _GGE_set1_pd(dAbsMask.d);

	const n128d d2_rad2deg      = _GGE_set1_pd(180.0 / 3.141592653589793238462643383279502884);
	const n128d d2_deg2rad      = _GGE_set1_pd(3.141592653589793238462643383279502884 / 180.0);

#if defined(GGE_SIMD_REGISTER_256)

	const n256d d4_1            = _GGE256_set1_pd(1.0);
	const n256d d4minusOne      = _GGE256_set1_pd(-1.0);

	const n256d d4_NaN          = _GGE256_set1_pd(dNanMask.d);      // Quiet NaN
	const n256d d4_inf          = _GGE256_set1_pd(dInfMask.d);      // Infinity
	const n256d d4_minusinf     = _GGE256_set1_pd(dMinusinfMask.d); // -Infinity
	const n256d d4_fff          = _GGE256_set1_pd(dfffMask.d);      // 0xffffffff

	const n256d d4negativeMask  = _GGE256_set1_pd(dNegMask.d);
	const n256d d4absMask       = _GGE256_set1_pd(dAbsMask.d);

	const n256d d4_rad2deg      = _GGE256_set1_pd(180.0 / 3.141592653589793238462643383279502884);
	const n256d d4_deg2rad      = _GGE256_set1_pd(3.141592653589793238462643383279502884 / 180.0);

#endif

	#define _GGE_cmpneq1_pd(val1, val2)		_GGE_and_pd(_GGE_cmpneq_pd((val1), (val2)), d2_1)
	#define _GGE_cmpeq1_pd(val1, val2)		_GGE_and_pd(_GGE_cmpeq_pd((val1), (val2)), d2_1)
	
	#define _GGE_cmpgt1_pd(val1, val2)		_GGE_and_pd(_GGE_cmpgt_pd((val1), (val2)), d2_1)
	#define _GGE_cmpge1_pd(val1, val2)		_GGE_and_pd(_GGE_cmpge_pd((val1), (val2)), d2_1)
	
	#define _GGE_cmplt1_pd(val1, val2)		_GGE_and_pd(_GGE_cmplt_pd((val1), (val2)), d2_1)
	#define _GGE_cmple1_pd(val1, val2)		_GGE_and_pd(_GGE_cmple_pd((val1), (val2)), d2_1)

#if defined(GGE_SIMD_REGISTER_256)

	#define _GGE256_perm_xxxx_pd(x)			_GGE256_perm_pd((x), MaskX, MaskX, MaskX, MaskX)
	#define _GGE256_perm_yyyy_pd(x)			_GGE256_perm_pd((x), MaskY, MaskY, MaskY, MaskY)
	#define _GGE256_perm_zzzz_pd(x)			_GGE256_perm_pd((x), MaskZ, MaskZ, MaskZ, MaskZ)
	#define _GGE256_perm_wwww_pd(x)			_GGE256_perm_pd((x), MaskW, MaskW, MaskW, MaskW)

	#define _GGE256_perm_yzxx_pd(x)			_GGE256_perm_pd((x), MaskY, MaskZ, MaskX, MaskX)

	#define _GGE256_cmpneq1_pd(val1, val2)	_GGE256_and_pd(_GGE256_cmpneq_pd((val1), (val2)), d4_1)
	#define _GGE256_cmpeq1_pd(val1, val2)	_GGE256_and_pd(_GGE256_cmpeq_pd((val1), (val2)), d4_1)
	
	#define _GGE256_cmpgt1_pd(val1, val2)	_GGE256_and_pd(_GGE256_cmpgt_pd((val1), (val2)), d4_1)
	#define _GGE256_cmpge1_pd(val1, val2)	_GGE256_and_pd(_GGE256_cmpge_pd((val1), (val2)), d4_1)
	
	#define _GGE256_cmplt1_pd(val1, val2)	_GGE256_and_pd(_GGE256_cmplt_pd((val1), (val2)), d4_1)
	#define _GGE256_cmple1_pd(val1, val2)	_GGE256_and_pd(_GGE256_cmple_pd((val1), (val2)), d4_1)

#endif

	GGE_inline n128d _GGE_dot2_pd(n128d x, n128d y)
	{
		n128d multi = _GGE_mul_pd(x, y); // Multiply components
		n128d shuf = _GGE_perm_yy_pd(multi); // Shuffle y
		return _GGE_add_pd(multi, shuf);
	}

	// See http://http.developer.nvidia.com/Cg/fmod.html for reference
	// This implementation does not follow the reference
	// float2 c = frac(abs(a/b))*abs(b);
	// return (a < 0) ? -c : c;    // if ( a < 0 ) c = 0-c
	GGE_inline n128d _GGE_fmod_pd(n128d x, n128d y)
	{
		n128d div = _GGE_div_pd(x, y);
		n128d trnc = _GGE_sub_pd(div, _GGE_trunc_pd(div));
		return _GGE_mul_pd(trnc, y);
	}

	GGE_inline void _GGE_modf_pd(n128d x, n128d& intPart, n128d& fracPart)
	{
		intPart = _GGE_trunc_pd(x);
		fracPart = _GGE_sub_pd(x, intPart);
	}

	GGE_inline n128d _GGE_lerp_pd(n128d x, n128d y, n128d a)
	{
		n128d x_one_minus_a = _GGE_msub_pd(x, x, a); // x * (1 - a)
		n128d result = _GGE_madd_pd(y, a, x_one_minus_a);
		return result;
	}

	// Hlsl, glsl and Cg behavior is to swap the operands.
	// http://http.developer.nvidia.com/Cg/step.html
	// https://www.opengl.org/sdk/docs/man/html/step.xhtml
	GGE_inline n128d _GGE_step_pd(n128d x, n128d y)
	{
		return _GGE_cmpge1_pd(x, y);
	}

#if defined(GGE_SIMD_REGISTER_256)

	GGE_inline n256d _GGE256_cross_pd(const n256d& x, const n256d& y)
	{
		n256d x_yzx = _GGE256_perm_yzxx_pd(x);
		n256d y_yzx = _GGE256_perm_yzxx_pd(y);
		return _GGE256_perm_yzxx_pd(_GGE256_msub_pd(x, y_yzx, _GGE256_mul_pd(x_yzx, y)));
	}

	GGE_inline n128d _GGE256_dot3_pd(const n256d& x, const n256d& y)
	{
		n256d multi  = _GGE256_mul_pd(x, y);   // Multiply components
		n128d low    = _GGE256_low_pd(multi);
		n128d high   = _GGE256_high_pd(multi);
		n128d add    = _GGE_add_pd(low, high); // Contains x + z, y + w
		n128d result = _GGE_add_pd(add, _GGE_perm_yy_pd(low)); // Only add the y component (which was in the low)
		return result;
	}
	
	GGE_inline n128d _GGE256_dot4_pd(const n256d& x, const n256d& y)
	{
		n256d multi  = _GGE256_mul_pd(x, y);   // Multiply components
		n128d low    = _GGE256_low_pd(multi);
		n128d high   = _GGE256_high_pd(multi);
		n128d add    = _GGE_add_pd(low, high); // Contains x + y, z + w
		n128d result = _GGE_add_pd(add, _GGE_perm_yy_pd(add));
		return result;
	}

	// See http://http.developer.nvidia.com/Cg/fmod.html for reference
	// This implementation does not follow the reference
	// float2 c = frac(abs(a/b))*abs(b);
	// return (a < 0) ? -c : c;    // if ( a < 0 ) c = 0-c
	GGE_inline n256d _GGE256_fmod_pd(n256d x, n256d y)
	{
		n256d div = _GGE256_div_pd(x, y);
		n256d trnc = _GGE256_sub_pd(div, _GGE256_trunc_pd(div));
		return _GGE256_mul_pd(trnc, y);
	}

	GGE_inline void _GGE256_modf_pd(n256d x, n256d& intPart, n256d& fracPart)
	{
		intPart = _GGE256_trunc_pd(x);
		fracPart = _GGE256_sub_pd(x, intPart);
	}

	GGE_inline n256d _GGE256_lerp_pd(n256d x, n256d y, n256d a)
	{
		n256d x_one_minus_a = _GGE256_msub_pd(x, x, a); // x * (1 - a)
		n256d result = _GGE256_madd_pd(y, a, x_one_minus_a);
		return result;
	}
	
	// Hlsl, glsl and Cg behavior is to swap the operands.
	// http://http.developer.nvidia.com/Cg/step.html
	// https://www.opengl.org/sdk/docs/man/html/step.xhtml
	GGE_inline n256d _GGE256_step_pd(n256d x, n256d y)
	{
		return _GGE256_cmpge1_pd(x, y);
	}

#else

	GGE_inline void _GGE_cross_pd(const n128d& x0, const n128d& x1, const n128d& y0, const n128d& y1, n128d& r0, n128d& r1)
	{
		n128d x_yz = _GGE_shuf_yx_pd(x0, x1);
		n128d y_yz = _GGE_shuf_yx_pd(y0, y1);

		n128d multi0 = _GGE_mul_pd(x_yz, y0);
		n128d multi1 = _GGE_mul_pd(x0, y1);

		n128d msub0 = _GGE_msub_pd(x0, y_yz, multi0);
		n128d msub1 = _GGE_msub_pd(x1, y0, multi1);

		r0 = _GGE_shuf_yx_pd(msub0, msub1);
		r1 = msub0;
	}

	GGE_inline n128d _GGE_dot3_pd(const n128d& x0, const n128d& x1, const n128d& y0, const n128d& y1)
	{
		n128d multi0 = _GGE_mul_pd(x0, y0); // Multiply components
		n128d multi1 = _GGE_mul_pd(x1, y1);
		n128d shuf0 = _GGE_perm_yy_pd(multi0); // Shuffle y and w
		n128d add0 = _GGE_add_pd(shuf0, multi0);  // Contains x+y, _
		return _GGE_add_pd(add0, multi1);
	}

	GGE_inline n128d _GGE_dot4_pd(const n128d& x0, const n128d& x1, const n128d& y0, const n128d& y1)
	{
		n128d multi0 = _GGE_mul_pd(x0, y0); // Multiply components
		n128d multi1 = _GGE_mul_pd(x1, y1);

		n128d shuf0 = _GGE_perm_yy_pd(multi0); // Shuffle y and w
		n128d shuf1 = _GGE_perm_yy_pd(multi1);

		n128d add0 = _GGE_add_pd(shuf0, multi0);  // Contains x+y, _
		n128d add1 = _GGE_add_pd(shuf1, multi1);  // Contains z+w, _

		return _GGE_add_pd(add0, add1);
	}

#endif
}

#include <Core/Math/hlsl++/vector_double_type.h>

GGE_module_export namespace GGE
{
	// Addition

	GGE_inline double1 operator + (const double1& f1, const double1& f2) { return double1(_GGE_add_pd(f1.vec, f2.vec)); }
	GGE_inline double2 operator + (const double2& f1, const double2& f2) { return double2(_GGE_add_pd(f1.vec, f2.vec)); }
	GGE_inline double3 operator + (const double3& f1, const double3& f2)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double3(_GGE256_add_pd(f1.vec, f2.vec));
#else
		return double3(_GGE_add_pd(f1.vec0, f2.vec0), _GGE_add_pd(f1.vec1, f2.vec1));
#endif
	}

	GGE_inline double4 operator + (const double4& f1, const double4& f2)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double4(_GGE256_add_pd(f1.vec, f2.vec));
#else
		return double4(_GGE_add_pd(f1.vec0, f2.vec0), _GGE_add_pd(f1.vec1, f2.vec1));
#endif
	}

	GGE_inline double2 operator + (const double2& f1, const double1& f2) { return double2(_GGE_add_pd(f1.vec, _GGE_perm_xx_pd(f2.vec))); }
	GGE_inline double3 operator + (const double3& f1, const double1& f2)
	{
#if defined(GGE_SIMD_REGISTER_256)
		n128d shufx = _GGE_perm_xx_pd(f2.vec);
		return double3(_GGE256_add_pd(f1.vec, _GGE256_set128_pd(shufx, shufx)));
#else
		return double3(_GGE_add_pd(f1.vec0, _GGE_perm_xx_pd(f2.vec)), _GGE_add_pd(f1.vec1, _GGE_perm_xx_pd(f2.vec)));
#endif
	}

	GGE_inline double4 operator + (const double4& f1, const double1& f2)
	{
#if defined(GGE_SIMD_REGISTER_256)
		n128d shufx = _GGE_perm_xx_pd(f2.vec);
		return double4(_GGE256_add_pd(f1.vec, _GGE256_set128_pd(shufx, shufx)));
#else
		return double4(_GGE_add_pd(f1.vec0, _GGE_perm_xx_pd(f2.vec)), _GGE_add_pd(f1.vec1, _GGE_perm_xx_pd(f2.vec)));
#endif
	}

	// Subtraction

	GGE_inline double1 operator - (const double1& f1, const double1& f2) { return double1(_GGE_sub_pd(f1.vec, f2.vec)); }
	GGE_inline double2 operator - (const double2& f1, const double2& f2) { return double2(_GGE_sub_pd(f1.vec, f2.vec)); }
	GGE_inline double3 operator - (const double3& f1, const double3& f2)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double3(_GGE256_sub_pd(f1.vec, f2.vec));
#else
		return double3(_GGE_sub_pd(f1.vec0, f2.vec0), _GGE_sub_pd(f1.vec1, f2.vec1));
#endif
	}

	GGE_inline double4 operator - (const double4& f1, const double4& f2)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double4(_GGE256_sub_pd(f1.vec, f2.vec));
#else
		return double4(_GGE_sub_pd(f1.vec0, f2.vec0), _GGE_sub_pd(f1.vec1, f2.vec1));
#endif
	}

	GGE_inline double2 operator - (const double2& f1, const double1& f2) { return double2(_GGE_sub_pd(f1.vec, _GGE_perm_xx_pd(f2.vec))); }
	GGE_inline double3 operator - (const double3& f1, const double1& f2)
	{
#if defined(GGE_SIMD_REGISTER_256)
		n128d shufx = _GGE_perm_xx_pd(f2.vec);
		return double3(_GGE256_sub_pd(f1.vec, _GGE256_set128_pd(shufx, shufx)));
#else
		return double3(_GGE_sub_pd(f1.vec0, _GGE_perm_xx_pd(f2.vec)), _GGE_sub_pd(f1.vec1, _GGE_perm_xx_pd(f2.vec)));
#endif
	}

	GGE_inline double4 operator - (const double4& f1, const double1& f2)
	{
#if defined(GGE_SIMD_REGISTER_256)
		n128d shufx = _GGE_perm_xx_pd(f2.vec);
		return double4(_GGE256_sub_pd(f1.vec, _GGE256_set128_pd(shufx, shufx)));
#else
		return double4(_GGE_sub_pd(f1.vec0, _GGE_perm_xx_pd(f2.vec)), _GGE_sub_pd(f1.vec1, _GGE_perm_xx_pd(f2.vec)));
#endif
	}

	// Multiplication

	GGE_inline double1 operator * (const double1& f1, const double1& f2) { return double1(_GGE_mul_pd(f1.vec, f2.vec)); }
	GGE_inline double2 operator * (const double2& f1, const double2& f2) { return double2(_GGE_mul_pd(f1.vec, f2.vec)); }
	GGE_inline double3 operator * (const double3& f1, const double3& f2)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double3(_GGE256_mul_pd(f1.vec, f2.vec));
#else
		return double3(_GGE_mul_pd(f1.vec0, f2.vec0), _GGE_mul_pd(f1.vec1, f2.vec1));
#endif
	}

	GGE_inline double4 operator * (const double4& f1, const double4& f2)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double4(_GGE256_mul_pd(f1.vec, f2.vec));
#else
		return double4(_GGE_mul_pd(f1.vec0, f2.vec0), _GGE_mul_pd(f1.vec1, f2.vec1));
#endif
	}

	GGE_inline double2 operator * (const double2& f1, const double1& f2) { return double2(_GGE_mul_pd(f1.vec, _GGE_perm_xx_pd(f2.vec))); }
	
	GGE_inline double3 operator * (const double3& f1, const double1& f2)
	{
#if defined(GGE_SIMD_REGISTER_256)
		n128d shufx = _GGE_perm_xx_pd(f2.vec);
		return double3(_GGE256_mul_pd(f1.vec, _GGE256_set128_pd(shufx, shufx)));
#else
		return double3(_GGE_mul_pd(f1.vec0, _GGE_perm_xx_pd(f2.vec)), _GGE_mul_pd(f1.vec1, _GGE_perm_xx_pd(f2.vec)));
#endif
	}

	GGE_inline double4 operator * (const double4& f1, const double1& f2)
	{
#if defined(GGE_SIMD_REGISTER_256)
		n128d shufx = _GGE_perm_xx_pd(f2.vec);
		return double4(_GGE256_mul_pd(f1.vec, _GGE256_set128_pd(shufx, shufx)));
#else
		return double4(_GGE_mul_pd(f1.vec0, _GGE_perm_xx_pd(f2.vec)), _GGE_mul_pd(f1.vec1, _GGE_perm_xx_pd(f2.vec)));
#endif
	}

	// Division

	GGE_inline double1 operator / (const double1& f1, const double1& f2) { return double1(_GGE_div_pd(f1.vec, f2.vec)); }
	GGE_inline double2 operator / (const double2& f1, const double2& f2) { return double2(_GGE_div_pd(f1.vec, f2.vec)); }
	GGE_inline double3 operator / (const double3& f1, const double3& f2)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double3(_GGE256_div_pd(f1.vec, f2.vec));
#else
		return double3(_GGE_div_pd(f1.vec0, f2.vec0), _GGE_div_pd(f1.vec1, f2.vec1));
#endif
	}

	GGE_inline double4 operator / (const double4& f1, const double4& f2)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double4(_GGE256_div_pd(f1.vec, f2.vec));
#else
		return double4(_GGE_div_pd(f1.vec0, f2.vec0), _GGE_div_pd(f1.vec1, f2.vec1));
#endif
	}

	GGE_inline double2 operator / (const double2& f1, const double1& f2) { return double2(_GGE_div_pd(f1.vec, _GGE_perm_xx_pd(f2.vec))); }
	GGE_inline double3 operator / (const double3& f1, const double1& f2)
	{
#if defined(GGE_SIMD_REGISTER_256)
		n128d shufx = _GGE_perm_xx_pd(f2.vec);
		return double3(_GGE256_div_pd(f1.vec, _GGE256_set128_pd(shufx, shufx)));
#else
		return double3(_GGE_div_pd(f1.vec0, _GGE_perm_xx_pd(f2.vec)), _GGE_div_pd(f1.vec1, _GGE_perm_xx_pd(f2.vec)));
#endif
	}

	GGE_inline double4 operator / (const double4& f1, const double1& f2)
	{
#if defined(GGE_SIMD_REGISTER_256)
		n128d shufx = _GGE_perm_xx_pd(f2.vec);
		return double4(_GGE256_div_pd(f1.vec, _GGE256_set128_pd(shufx, shufx)));
#else
		return double4(_GGE_div_pd(f1.vec0, _GGE_perm_xx_pd(f2.vec)), _GGE_div_pd(f1.vec1, _GGE_perm_xx_pd(f2.vec)));
#endif
	}

	GGE_inline double1 operator - (const double1& f) { return double1(_GGE_neg_pd(f.vec)); }
	GGE_inline double2 operator - (const double2& f) { return double2(_GGE_neg_pd(f.vec)); }
	GGE_inline double3 operator - (const double3& f)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double3(_GGE256_neg_pd(f.vec));
#else
		return double3(_GGE_neg_pd(f.vec0), _GGE_neg_pd(f.vec1));
#endif
	}

	GGE_inline double4 operator - (const double4& f)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double4(_GGE256_neg_pd(f.vec));
#else
		return double4(_GGE_neg_pd(f.vec0), _GGE_neg_pd(f.vec1));
#endif
	}

	GGE_inline double1 operator % (const double1& f1, const double1& f2) { return double1(_GGE_fmod_pd(f1.vec, f2.vec)); }
	GGE_inline double2 operator % (const double2& f1, const double2& f2) { return double2(_GGE_fmod_pd(f1.vec, f2.vec)); }
	GGE_inline double3 operator % (const double3& f1, const double3& f2)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double3(_GGE256_fmod_pd(f1.vec, f2.vec));
#else
		return double3(_GGE_fmod_pd(f1.vec0, f2.vec0), _GGE_fmod_pd(f1.vec1, f2.vec1));
#endif
	}

	GGE_inline double4 operator % (const double4& f1, const double4& f2)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double4(_GGE256_fmod_pd(f1.vec, f2.vec));
#else
		return double4(_GGE_fmod_pd(f1.vec0, f2.vec0), _GGE_fmod_pd(f1.vec1, f2.vec1));
#endif
	}

	GGE_inline double1 operator == (const double1& f1, const double1& f2) { return double1(_GGE_cmpeq1_pd(f1.vec, f2.vec)); }
	GGE_inline double2 operator == (const double2& f1, const double2& f2) { return double2(_GGE_cmpeq1_pd(f1.vec, f2.vec)); }
	GGE_inline double3 operator == (const double3& f1, const double3& f2)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double3(_GGE256_cmpeq1_pd(f1.vec, f2.vec));
#else
		return double3(_GGE_cmpeq1_pd(f1.vec0, f2.vec0), _GGE_cmpeq1_pd(f1.vec1, f2.vec1));
#endif
	}

	GGE_inline double4 operator == (const double4& f1, const double4& f2)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double4(_GGE256_cmpeq1_pd(f1.vec, f2.vec));
#else
		return double4(_GGE_cmpeq1_pd(f1.vec0, f2.vec0), _GGE_cmpeq1_pd(f1.vec1, f2.vec1));
#endif
	}
	
	GGE_inline double1 operator != (const double1& f1, const double1& f2) { return double1(_GGE_cmpneq1_pd(f1.vec, f2.vec)); }
	GGE_inline double2 operator != (const double2& f1, const double2& f2) { return double2(_GGE_cmpneq1_pd(f1.vec, f2.vec)); }
	
	GGE_inline double3 operator != (const double3& f1, const double3& f2)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double3(_GGE256_cmpneq1_pd(f1.vec, f2.vec));
#else
		return double3(_GGE_cmpneq1_pd(f1.vec0, f2.vec0), _GGE_cmpneq1_pd(f1.vec1, f2.vec1));
#endif
	}

	GGE_inline double4 operator != (const double4& f1, const double4& f2)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double4(_GGE256_cmpneq1_pd(f1.vec, f2.vec));
#else
		return double4(_GGE_cmpneq1_pd(f1.vec0, f2.vec0), _GGE_cmpneq1_pd(f1.vec1, f2.vec1));
#endif
	}

	GGE_inline double1 operator > (const double1& f1, const double1& f2) { return double1(_GGE_cmpgt1_pd(f1.vec, f2.vec)); }
	GGE_inline double2 operator > (const double2& f1, const double2& f2) { return double2(_GGE_cmpgt1_pd(f1.vec, f2.vec)); }
	GGE_inline double3 operator > (const double3& f1, const double3& f2)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double3(_GGE256_cmpgt1_pd(f1.vec, f2.vec));
#else
		return double3(_GGE_cmpgt1_pd(f1.vec0, f2.vec0), _GGE_cmpgt1_pd(f1.vec1, f2.vec1));
#endif
	}

	GGE_inline double4 operator > (const double4& f1, const double4& f2)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double4(_GGE256_cmpgt1_pd(f1.vec, f2.vec));
#else
		return double4(_GGE_cmpgt1_pd(f1.vec0, f2.vec0), _GGE_cmpgt1_pd(f1.vec1, f2.vec1));
#endif
	}

	GGE_inline double1 operator >= (const double1& f1, const double1& f2) { return double1(_GGE_cmpge1_pd(f1.vec, f2.vec)); }
	GGE_inline double2 operator >= (const double2& f1, const double2& f2) { return double2(_GGE_cmpge1_pd(f1.vec, f2.vec)); }
	GGE_inline double3 operator >= (const double3& f1, const double3& f2)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double3(_GGE256_cmpge1_pd(f1.vec, f2.vec));
#else
		return double3(_GGE_cmpge1_pd(f1.vec0, f2.vec0), _GGE_cmpge1_pd(f1.vec1, f2.vec1));
#endif
	}

	GGE_inline double4 operator >= (const double4& f1, const double4& f2)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double4(_GGE256_cmpge1_pd(f1.vec, f2.vec));
#else
		return double4(_GGE_cmpge1_pd(f1.vec0, f2.vec0), _GGE_cmpge1_pd(f1.vec1, f2.vec1));
#endif
	}

	GGE_inline double1 operator < (const double1& f1, const double1& f2) { return double1(_GGE_cmplt1_pd(f1.vec, f2.vec)); }
	GGE_inline double2 operator < (const double2& f1, const double2& f2) { return double2(_GGE_cmplt1_pd(f1.vec, f2.vec)); }
	
	GGE_inline double3 operator < (const double3& f1, const double3& f2)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double3(_GGE256_cmplt1_pd(f1.vec, f2.vec));
#else
		return double3(_GGE_cmplt1_pd(f1.vec0, f2.vec0), _GGE_cmplt1_pd(f1.vec1, f2.vec1));
#endif
	}

	GGE_inline double4 operator < (const double4& f1, const double4& f2)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double4(_GGE256_cmplt1_pd(f1.vec, f2.vec));
#else
		return double4(_GGE_cmplt1_pd(f1.vec0, f2.vec0), _GGE_cmplt1_pd(f1.vec1, f2.vec1));
#endif
	}

	GGE_inline double1 operator <= (const double1& f1, const double1& f2) { return double1(_GGE_cmple1_pd(f1.vec, f2.vec)); }
	GGE_inline double2 operator <= (const double2& f1, const double2& f2) { return double2(_GGE_cmple1_pd(f1.vec, f2.vec)); }
	GGE_inline double3 operator <= (const double3& f1, const double3& f2)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double3(_GGE256_cmple1_pd(f1.vec, f2.vec));
#else
		return double3(_GGE_cmple1_pd(f1.vec0, f2.vec0), _GGE_cmple1_pd(f1.vec1, f2.vec1));
#endif
	}

	GGE_inline double4 operator <= (const double4& f1, const double4& f2)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double4(_GGE256_cmple1_pd(f1.vec, f2.vec));
#else
		return double4(_GGE_cmple1_pd(f1.vec0, f2.vec0), _GGE_cmple1_pd(f1.vec1, f2.vec1));
#endif
	}

	GGE_inline double1& operator += (double1& f1, const double1& f2) { f1 = f1 + f2; return f1; }
	GGE_inline double2& operator += (double2& f1, const double2& f2) { f1 = f1 + f2; return f1; }
	GGE_inline double3& operator += (double3& f1, const double3& f2) { f1 = f1 + f2; return f1; }
	GGE_inline double4& operator += (double4& f1, const double4& f2) { f1 = f1 + f2; return f1; }

	GGE_inline double1& operator -= (double1& f1, const double1& f2) { f1 = f1 - f2; return f1; }
	GGE_inline double2& operator -= (double2& f1, const double2& f2) { f1 = f1 - f2; return f1; }
	GGE_inline double3& operator -= (double3& f1, const double3& f2) { f1 = f1 - f2; return f1; }
	GGE_inline double4& operator -= (double4& f1, const double4& f2) { f1 = f1 - f2; return f1; }

	GGE_inline double1& operator *= (double1& f1, const double1& f2) { f1 = f1 * f2; return f1; }
	GGE_inline double2& operator *= (double2& f1, const double2& f2) { f1 = f1 * f2; return f1; }
	GGE_inline double3& operator *= (double3& f1, const double3& f2) { f1 = f1 * f2; return f1; }
	GGE_inline double4& operator *= (double4& f1, const double4& f2) { f1 = f1 * f2; return f1; }

	GGE_inline double1& operator /= (double1& f1, const double1& f2) { f1 = f1 / f2; return f1; }
	GGE_inline double2& operator /= (double2& f1, const double2& f2) { f1 = f1 / f2; return f1; }
	GGE_inline double3& operator /= (double3& f1, const double3& f2) { f1 = f1 / f2; return f1; }
	GGE_inline double4& operator /= (double4& f1, const double4& f2) { f1 = f1 / f2; return f1; }

	GGE_inline double1& operator %= (double1& f1, const double1& f2) { f1 = f1 % f2; return f1; }
	GGE_inline double2& operator %= (double2& f1, const double2& f2) { f1 = f1 % f2; return f1; }
	GGE_inline double3& operator %= (double3& f1, const double3& f2) { f1 = f1 % f2; return f1; }
	GGE_inline double4& operator %= (double4& f1, const double4& f2) { f1 = f1 % f2; return f1; }

GGE_WARNING_IMPLICIT_CONSTRUCTOR_BEGIN

	// Pre-increment

	GGE_inline double1& operator ++ (double1& f) { f = f + double1(1.0); return f; }
	GGE_inline double2& operator ++ (double2& f) { f = f + double2(1.0); return f; }
	GGE_inline double3& operator ++ (double3& f) { f = f + double3(1.0); return f; }
	GGE_inline double4& operator ++ (double4& f) { f = f + double4(1.0); return f; }

	template<int X> GGE_inline dswizzle1<X>& operator ++ (dswizzle1<X>& f) { f = f + double1(1.0); return f; }
	template<int X, int Y> GGE_inline dswizzle2<X, Y>& operator ++ (dswizzle2<X, Y>& f) { f = f + double2(1.0); return f; }
	template<int X, int Y, int Z> GGE_inline dswizzle3<X, Y, Z>& operator ++ (dswizzle3<X, Y, Z>& f) { f = f + double3(1.0); return f; }
	template<int X, int Y, int Z, int W> GGE_inline dswizzle4<X, Y, Z, W>& operator ++ (dswizzle4<X, Y, Z, W>& f) { f = f + double4(1.0); return f; }

	GGE_inline double1& operator -- (double1& f) { f = f - double1(1.0); return f; }
	GGE_inline double2& operator -- (double2& f) { f = f - double2(1.0); return f; }
	GGE_inline double3& operator -- (double3& f) { f = f - double3(1.0); return f; }
	GGE_inline double4& operator -- (double4& f) { f = f - double4(1.0); return f; }

	template<int X> GGE_inline dswizzle1<X>& operator -- (dswizzle1<X>& f) { f = f - double1(1.0); return f; }
	template<int X, int Y> GGE_inline dswizzle2<X, Y>& operator -- (dswizzle2<X, Y>& f) { f = f - double2(1.0); return f; }
	template<int X, int Y, int Z> GGE_inline dswizzle3<X, Y, Z>& operator -- (dswizzle3<X, Y, Z>& f) { f = f - double3(1.0); return f; }
	template<int X, int Y, int Z, int W> GGE_inline dswizzle4<X, Y, Z, W>& operator -- (dswizzle4<X, Y, Z, W>& f) { f = f - double4(1.0); return f; }

	// Post-increment

	GGE_inline double1 operator ++ (double1& f, int) { double1 tmp = f; f = f + double1(1.0); return tmp; }
	GGE_inline double2 operator ++ (double2& f, int) { double2 tmp = f; f = f + double2(1.0); return tmp; }
	GGE_inline double3 operator ++ (double3& f, int) { double3 tmp = f; f = f + double3(1.0); return tmp; }
	GGE_inline double4 operator ++ (double4& f, int) { double4 tmp = f; f = f + double4(1.0); return tmp; }

	template<int X>
	GGE_inline dswizzle1<X> operator ++ (dswizzle1<X>& f, int) { dswizzle1<X> tmp = f; f = f + double1(1.0); return tmp; }
	template<int X, int Y>
	GGE_inline dswizzle2<X, Y> operator ++ (dswizzle2<X, Y>& f, int) { dswizzle2<X, Y> tmp = f; f = f + double2(1.0); return tmp; }
	template<int X, int Y, int Z>
	GGE_inline dswizzle3<X, Y, Z> operator ++ (dswizzle3<X, Y, Z>& f, int) { dswizzle3<X, Y, Z> tmp = f; f = f + double3(1.0); return tmp; }
	template<int X, int Y, int Z, int W>
	GGE_inline dswizzle4<X, Y, Z, W> operator ++ (dswizzle4<X, Y, Z, W>& f, int) { dswizzle4<X, Y, Z, W> tmp = f; f = f + double4(1.0); return tmp; }

	GGE_inline double1 operator -- (double1& f, int) { double1 tmp = f; f = f - double1(1.0); return tmp; }
	GGE_inline double2 operator -- (double2& f, int) { double2 tmp = f; f = f - double2(1.0); return tmp; }
	GGE_inline double3 operator -- (double3& f, int) { double3 tmp = f; f = f - double3(1.0); return tmp; }
	GGE_inline double4 operator -- (double4& f, int) { double4 tmp = f; f = f - double4(1.0); return tmp; }

	template<int X>
	GGE_inline dswizzle1<X> operator -- (dswizzle1<X>& f, int) { dswizzle1<X> tmp = f; f = f - double1(1.0); return tmp; }
	template<int X, int Y>
	GGE_inline dswizzle2<X, Y> operator -- (dswizzle2<X, Y>& f, int) { dswizzle2<X, Y> tmp = f; f = f - double2(1.0); return tmp; }
	template<int X, int Y, int Z>
	GGE_inline dswizzle3<X, Y, Z> operator -- (dswizzle3<X, Y, Z>& f, int) { dswizzle3<X, Y, Z> tmp = f; f = f - double3(1.0); return tmp; }
	template<int X, int Y, int Z, int W>
	GGE_inline dswizzle4<X, Y, Z, W> operator -- (dswizzle4<X, Y, Z, W>& f, int) { dswizzle4<X, Y, Z, W> tmp = f; f = f - double4(1.0); return tmp; }

GGE_WARNING_IMPLICIT_CONSTRUCTOR_END

	//--------------------------------------------------------------------------------------------------------------------
	// double1 and dswizzle1 need special overloads to disambiguate between our operators/functions and built-in operators
	// and functions that are part of common headers such as cmath, math.h, algorithm, etc
	//--------------------------------------------------------------------------------------------------------------------

	template<typename T> GGE_inline GGE_enable_if_return(T, double1) operator + (const double1& f1, T f2) { return f1 + double1(f2); }
	template<typename T> GGE_inline GGE_enable_if_return(T, double2) operator + (const double2& f1, T f2) { return f1 + double2(f2); }
	template<typename T> GGE_inline GGE_enable_if_return(T, double3) operator + (const double3& f1, T f2) { return f1 + double3(f2); }
	template<typename T> GGE_inline GGE_enable_if_return(T, double4) operator + (const double4& f1, T f2) { return f1 + double4(f2); }

	template<typename T> GGE_inline GGE_enable_if_return(T, double1) operator + (T f1, const double1& f2) { return double1(f1) + f2; }
	template<typename T> GGE_inline GGE_enable_if_return(T, double2) operator + (T f1, const double2& f2) { return double2(f1) + f2; }
	template<typename T> GGE_inline GGE_enable_if_return(T, double3) operator + (T f1, const double3& f2) { return double3(f1) + f2; }
	template<typename T> GGE_inline GGE_enable_if_return(T, double4) operator + (T f1, const double4& f2) { return double4(f1) + f2; }

	template<typename T> GGE_inline GGE_enable_if_return(T, double1) operator - (const double1& f1, T f2) { return f1 - double1(f2); }
	template<typename T> GGE_inline GGE_enable_if_return(T, double2) operator - (const double2& f1, T f2) { return f1 - double2(f2); }
	template<typename T> GGE_inline GGE_enable_if_return(T, double3) operator - (const double3& f1, T f2) { return f1 - double3(f2); }
	template<typename T> GGE_inline GGE_enable_if_return(T, double4) operator - (const double4& f1, T f2) { return f1 - double4(f2); }

	template<typename T> GGE_inline GGE_enable_if_return(T, double1) operator - (T f1, const double1& f2) { return double1(f1) - f2; }
	template<typename T> GGE_inline GGE_enable_if_return(T, double2) operator - (T f1, const double2& f2) { return double2(f1) - f2; }
	template<typename T> GGE_inline GGE_enable_if_return(T, double3) operator - (T f1, const double3& f2) { return double3(f1) - f2; }
	template<typename T> GGE_inline GGE_enable_if_return(T, double4) operator - (T f1, const double4& f2) { return double4(f1) - f2; }

	template<typename T> GGE_inline GGE_enable_if_return(T, double1) operator * (const double1& f1, T f2) { return f1 * double1(f2); }
	template<typename T> GGE_inline GGE_enable_if_return(T, double2) operator * (const double2& f1, T f2) { return f1 * double2(f2); }
	template<typename T> GGE_inline GGE_enable_if_return(T, double3) operator * (const double3& f1, T f2) { return f1 * double3(f2); }
	template<typename T> GGE_inline GGE_enable_if_return(T, double4) operator * (const double4& f1, T f2) { return f1 * double4(f2); }

	template<typename T> GGE_inline GGE_enable_if_return(T, double1) operator * (T f1, const double1& f2) { return double1(f1) * f2; }
	template<typename T> GGE_inline GGE_enable_if_return(T, double2) operator * (T f1, const double2& f2) { return double2(f1) * f2; }
	template<typename T> GGE_inline GGE_enable_if_return(T, double3) operator * (T f1, const double3& f2) { return double3(f1) * f2; }
	template<typename T> GGE_inline GGE_enable_if_return(T, double4) operator * (T f1, const double4& f2) { return double4(f1) * f2; }

	template<typename T> GGE_inline GGE_enable_if_return(T, double1) operator / (const double1& f1, T f2) { return f1 / double1(f2); }
	template<typename T> GGE_inline GGE_enable_if_return(T, double2) operator / (const double2& f1, T f2) { return f1 / double2(f2); }
	template<typename T> GGE_inline GGE_enable_if_return(T, double3) operator / (const double3& f1, T f2) { return f1 / double3(f2); }
	template<typename T> GGE_inline GGE_enable_if_return(T, double4) operator / (const double4& f1, T f2) { return f1 / double4(f2); }

	template<typename T> GGE_inline GGE_enable_if_return(T, double1) operator / (T f1, const double1& f2) { return double1(f1) / f2; }
	template<typename T> GGE_inline GGE_enable_if_return(T, double2) operator / (T f1, const double2& f2) { return double2(f1) / f2; }
	template<typename T> GGE_inline GGE_enable_if_return(T, double3) operator / (T f1, const double3& f2) { return double3(f1) / f2; }
	template<typename T> GGE_inline GGE_enable_if_return(T, double4) operator / (T f1, const double4& f2) { return double4(f1) / f2; }

	template<typename T> GGE_inline GGE_enable_if_return(T, double1) operator % (const double1& f1, T f2) { return f1 % double1(f2); }
	template<typename T> GGE_inline GGE_enable_if_return(T, double2) operator % (const double2& f1, T f2) { return f1 % double2(f2); }
	template<typename T> GGE_inline GGE_enable_if_return(T, double3) operator % (const double3& f1, T f2) { return f1 % double3(f2); }
	template<typename T> GGE_inline GGE_enable_if_return(T, double4) operator % (const double4& f1, T f2) { return f1 % double4(f2); }

	template<typename T> GGE_inline GGE_enable_if_return(T, double1) operator % (T f1, const double1& f2) { return double1(f1) % f2; }
	template<typename T> GGE_inline GGE_enable_if_return(T, double2) operator % (T f1, const double2& f2) { return double2(f1) % f2; }
	template<typename T> GGE_inline GGE_enable_if_return(T, double3) operator % (T f1, const double3& f2) { return double3(f1) % f2; }
	template<typename T> GGE_inline GGE_enable_if_return(T, double4) operator % (T f1, const double4& f2) { return double4(f1) % f2; }

	template<int X> GGE_inline double1 operator + (const dswizzle1<X>& s, const double1& f) { return double1(s) + f; }
	template<int X> GGE_inline double1 operator - (const dswizzle1<X>& s, const double1& f) { return double1(s) - f; }
	template<int X> GGE_inline double1 operator * (const dswizzle1<X>& s, const double1& f) { return double1(s) * f; }
	template<int X> GGE_inline double1 operator / (const dswizzle1<X>& s, const double1& f) { return double1(s) / f; }

	template<int X>	GGE_inline dswizzle1<X>& operator += (dswizzle1<X>& s, const double1& f) { s = double1(s) + f; return s; }
	template<int X>	GGE_inline dswizzle1<X>& operator -= (dswizzle1<X>& s, const double1& f) { s = double1(s) - f; return s; }
	template<int X>	GGE_inline dswizzle1<X>& operator *= (dswizzle1<X>& s, const double1& f) { s = double1(s) * f; return s; }
	template<int X>	GGE_inline dswizzle1<X>& operator /= (dswizzle1<X>& s, const double1& f) { s = double1(s) / f; return s; }
	template<int X>	GGE_inline dswizzle1<X>& operator %= (dswizzle1<X>& s, const double1& f) { s = double1(s) % f; return s; }

	template<int X, int Y> GGE_inline dswizzle2<X, Y>& operator += (dswizzle2<X, Y>& s, const double2& f) { s = double2(s) + f; return s; }
	template<int X, int Y> GGE_inline dswizzle2<X, Y>& operator -= (dswizzle2<X, Y>& s, const double2& f) { s = double2(s) - f; return s; }
	template<int X, int Y> GGE_inline dswizzle2<X, Y>& operator *= (dswizzle2<X, Y>& s, const double2& f) { s = double2(s) * f; return s; }
	template<int X, int Y> GGE_inline dswizzle2<X, Y>& operator /= (dswizzle2<X, Y>& s, const double2& f) { s = double2(s) / f; return s; }
	template<int X, int Y> GGE_inline dswizzle2<X, Y>& operator %= (dswizzle2<X, Y>& s, const double2& f) { s = double2(s) % f; return s; }

	template<int X, int Y, int Z> GGE_inline dswizzle3<X, Y, Z>& operator += (dswizzle3<X, Y, Z>& s, const double3& f) { s = double3(s) + f; return s; }
	template<int X, int Y, int Z> GGE_inline dswizzle3<X, Y, Z>& operator -= (dswizzle3<X, Y, Z>& s, const double3& f) { s = double3(s) - f; return s; }
	template<int X, int Y, int Z> GGE_inline dswizzle3<X, Y, Z>& operator *= (dswizzle3<X, Y, Z>& s, const double3& f) { s = double3(s) * f; return s; }
	template<int X, int Y, int Z> GGE_inline dswizzle3<X, Y, Z>& operator /= (dswizzle3<X, Y, Z>& s, const double3& f) { s = double3(s) / f; return s; }
	template<int X, int Y, int Z> GGE_inline dswizzle3<X, Y, Z>& operator %= (dswizzle3<X, Y, Z>& s, const double3& f) { s = double3(s) % f; return s; }

	template<int X, int Y, int Z, int W> GGE_inline dswizzle4<X, Y, Z, W>& operator += (dswizzle4<X, Y, Z, W>& s, const double4& f) { s = double4(s) + f; return s; }
	template<int X, int Y, int Z, int W> GGE_inline dswizzle4<X, Y, Z, W>& operator -= (dswizzle4<X, Y, Z, W>& s, const double4& f) { s = double4(s) - f; return s; }
	template<int X, int Y, int Z, int W> GGE_inline dswizzle4<X, Y, Z, W>& operator *= (dswizzle4<X, Y, Z, W>& s, const double4& f) { s = double4(s) * f; return s; }
	template<int X, int Y, int Z, int W> GGE_inline dswizzle4<X, Y, Z, W>& operator /= (dswizzle4<X, Y, Z, W>& s, const double4& f) { s = double4(s) / f; return s; }
	template<int X, int Y, int Z, int W> GGE_inline dswizzle4<X, Y, Z, W>& operator %= (dswizzle4<X, Y, Z, W>& s, const double4& f) { s = double4(s) % f; return s; }

	GGE_inline double1 abs(const double1& f) { return double1(_GGE_abs_pd(f.vec)); }
	GGE_inline double2 abs(const double2& f) { return double2(_GGE_abs_pd(f.vec)); }
	GGE_inline double3 abs(const double3& f)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double3(_GGE256_abs_pd(f.vec));
#else
		return double3(_GGE_abs_pd(f.vec0), _GGE_abs_pd(f.vec1));
#endif
	}

	GGE_inline double4 abs(const double4& f)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double4(_GGE256_abs_pd(f.vec));
#else
		return double4(_GGE_abs_pd(f.vec0), _GGE_abs_pd(f.vec1));
#endif
	}

	GGE_inline bool all(const double1& f) { return _GGE_all1_pd(f.vec); }
	GGE_inline bool all(const double2& f) { return _GGE_all2_pd(f.vec); }
	GGE_inline bool all(const double3& f)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return _GGE256_all3_pd(f.vec);
#else
		return _GGE_all3_pd(f.vec0, f.vec1);
#endif
	}
	GGE_inline bool all(const double4& f)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return _GGE256_all4_pd(f.vec);
#else
		return _GGE_all4_pd(f.vec0, f.vec1);
#endif
	}
	
	GGE_inline bool any(const double1& f) { return _GGE_any1_pd(f.vec); }
	GGE_inline bool any(const double2& f) { return _GGE_any2_pd(f.vec); }
	GGE_inline bool any(const double3& f)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return _GGE256_any3_pd(f.vec);
#else
		return _GGE_any3_pd(f.vec0, f.vec1);
#endif
	}

	GGE_inline bool any(const double4& f)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return _GGE256_any4_pd(f.vec);
#else
		return _GGE_any4_pd(f.vec0, f.vec1);
#endif
	}

	GGE_inline double1 ceil(const double1& f) { return double1(_GGE_ceil_pd(f.vec)); }
	GGE_inline double2 ceil(const double2& f) { return double2(_GGE_ceil_pd(f.vec)); }
	GGE_inline double3 ceil(const double3& f)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double3(_GGE256_ceil_pd(f.vec));
#else
		return double3(_GGE_ceil_pd(f.vec0), _GGE_ceil_pd(f.vec1));
#endif
	}

	GGE_inline double4 ceil(const double4& f)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double4(_GGE256_ceil_pd(f.vec));
#else
		return double4(_GGE_ceil_pd(f.vec0), _GGE_ceil_pd(f.vec1));
#endif
	}

	GGE_inline double1 clamp(const double1& f, const double1& minf, const double1& maxf) { return double1(_GGE_clamp_pd(f.vec, minf.vec, maxf.vec)); }
	GGE_inline double2 clamp(const double2& f, const double2& minf, const double2& maxf) { return double2(_GGE_clamp_pd(f.vec, minf.vec, maxf.vec)); }

	GGE_inline double3 clamp(const double3& f, const double3& minf, const double3& maxf)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double3(_GGE256_clamp_pd(f.vec, minf.vec, maxf.vec));
#else
		return double3(_GGE_clamp_pd(f.vec0, minf.vec0, maxf.vec0), _GGE_clamp_pd(f.vec1, minf.vec1, maxf.vec1));
#endif
	}

	GGE_inline double4 clamp(const double4& f, const double4& minf, const double4& maxf)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double4(_GGE256_clamp_pd(f.vec, minf.vec, maxf.vec));
#else
		return double4(_GGE_clamp_pd(f.vec0, minf.vec0, maxf.vec0), _GGE_clamp_pd(f.vec1, minf.vec1, maxf.vec1));
#endif
	}

	GGE_inline double1 copysign(const double1& from, const double1& to)
	{
		return double1(_GGE_copysign_pd(from.vec, to.vec));
	}

	GGE_inline double2 copysign(const double2& from, const double2& to)
	{
		return double2(_GGE_copysign_pd(from.vec, to.vec));
	}

	GGE_inline double3 copysign(const double3& from, const double3& to)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double3(_GGE256_copysign_pd(from.vec, to.vec));
#else
		return double3(_GGE_copysign_pd(from.vec0, to.vec0), _GGE_copysign_pd(from.vec0, to.vec1));
#endif
	}

	GGE_inline double4 copysign(const double4& from, const double4& to)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double4(_GGE256_copysign_pd(from.vec, to.vec));
#else
		return double4(_GGE_copysign_pd(from.vec0, to.vec0), _GGE_copysign_pd(from.vec0, to.vec1));
#endif
	}

	GGE_inline double3 cross(const double3& f1, const double3& f2)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double3(_GGE256_cross_pd(f1.vec, f2.vec));
#else
		n128d r0, r1;
		_GGE_cross_pd(f1.vec0, f1.vec1, f2.vec0, f2.vec1, r0, r1);
		return double3(r0, r1);
#endif
	}

	GGE_inline double1 degrees(const double1& f) { return double1(_GGE_mul_pd(f.vec, d2_rad2deg)); }
	GGE_inline double2 degrees(const double2& f) { return double2(_GGE_mul_pd(f.vec, d2_rad2deg)); }
	GGE_inline double3 degrees(const double3& f)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double3(_GGE256_mul_pd(f.vec, d4_rad2deg));
#else
		return double3(_GGE_mul_pd(f.vec0, d2_rad2deg), _GGE_mul_pd(f.vec1, d2_rad2deg));
#endif
	}
	GGE_inline double4 degrees(const double4& f)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double4(_GGE256_mul_pd(f.vec, d4_rad2deg));
#else
		return double4(_GGE_mul_pd(f.vec0, d2_rad2deg), _GGE_mul_pd(f.vec1, d2_rad2deg));
#endif
	}

	GGE_inline double1 distance(const double1& f1, const double1& f2) { return double1(_GGE_abs_pd(_GGE_sub_pd(f2.vec, f1.vec))); }
	GGE_inline double1 distance(const double2& f1, const double2& f2)
	{
		n128d delta = _GGE_sub_pd(f2.vec, f1.vec);
		return double1(_GGE_sqrt_pd(_GGE_dot2_pd(delta, delta)));
	}

	GGE_inline double1 distance(const double3& f1, const double3& f2)
	{
#if defined(GGE_SIMD_REGISTER_256)
		n256d delta = _GGE256_sub_pd(f2.vec, f1.vec);
		return double1(_GGE_sqrt_pd(_GGE256_dot3_pd(delta, delta)));
#else
		n128d delta0 = _GGE_sub_pd(f2.vec0, f1.vec0);
		n128d delta1 = _GGE_sub_pd(f2.vec1, f1.vec1);
		return double1(_GGE_sqrt_pd(_GGE_dot3_pd(delta0, delta1, delta0, delta1)));
#endif
	}

	GGE_inline double1 distance(const double4& f1, const double4& f2)
	{
#if defined(GGE_SIMD_REGISTER_256)
		n256d delta = _GGE256_sub_pd(f2.vec, f1.vec);
		return double1(_GGE_sqrt_pd(_GGE256_dot4_pd(delta, delta)));
#else
		n128d delta0 = _GGE_sub_pd(f2.vec0, f1.vec0);
		n128d delta1 = _GGE_sub_pd(f2.vec1, f1.vec1);
		return double1(_GGE_sqrt_pd(_GGE_dot4_pd(delta0, delta1, delta0, delta1)));
#endif
	}

	GGE_inline double1 dot(const double1& f1, const double1& f2) { return f1 * f2; }
	GGE_inline double1 dot(const double2& f1, const double2& f2) { return double1(_GGE_dot2_pd(f1.vec, f2.vec)); }
	GGE_inline double1 dot(const double3& f1, const double3& f2)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double1(_GGE256_dot3_pd(f1.vec, f2.vec));
#else
		return double1(_GGE_dot3_pd(f1.vec0, f1.vec1, f2.vec0, f2.vec1));
#endif
	}

	GGE_inline double1 dot(const double4& f1, const double4& f2)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double1(_GGE256_dot4_pd(f1.vec, f2.vec));
#else
		return double1(_GGE_dot4_pd(f1.vec0, f1.vec1, f2.vec0, f2.vec1));
#endif
	}

	GGE_inline double1 floor(const double1& f) { return double1(_GGE_floor_pd(f.vec)); }
	GGE_inline double2 floor(const double2& f) { return double2(_GGE_floor_pd(f.vec)); }
	GGE_inline double3 floor(const double3& f)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double3(_GGE256_floor_pd(f.vec));
#else
		return double3(_GGE_floor_pd(f.vec0), _GGE_floor_pd(f.vec1));
#endif
	}

	GGE_inline double4 floor(const double4& f)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double4(_GGE256_floor_pd(f.vec));
#else
		return double4(_GGE_floor_pd(f.vec0), _GGE_floor_pd(f.vec1));
#endif
	}

	GGE_inline double1 fmod(const double1& f1, const double1& f2) { return double1(_GGE_fmod_pd(f1.vec, f2.vec)); }
	GGE_inline double2 fmod(const double2& f1, const double2& f2) { return double2(_GGE_fmod_pd(f1.vec, f2.vec)); }
	GGE_inline double3 fmod(const double3& f1, const double3& f2)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double3(_GGE256_fmod_pd(f1.vec, f2.vec));
#else
		return double3(_GGE_fmod_pd(f1.vec0, f2.vec0), _GGE_fmod_pd(f1.vec1, f2.vec1));
#endif
	}

	GGE_inline double4 fmod(const double4& f1, const double4& f2)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double4(_GGE256_fmod_pd(f1.vec, f2.vec));
#else
		return double4(_GGE_fmod_pd(f1.vec0, f2.vec0), _GGE_fmod_pd(f1.vec1, f2.vec1));
#endif
	}

	// A note on negative numbers. Contrary to intuition, frac(-0.75) != 0.75,
	// but is actually frac(-0.75) == 0.25 This is because hlsl defines frac
	// as frac(x) = x - floor(x)
	GGE_inline double1 frac(const double1& f) { return double1(_GGE_frac_pd(f.vec)); }
	GGE_inline double2 frac(const double2& f) { return double2(_GGE_frac_pd(f.vec)); }
	GGE_inline double3 frac(const double3& f)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double3(_GGE256_frac_pd(f.vec));
#else
		return double3(_GGE_frac_pd(f.vec0), _GGE_frac_pd(f.vec1));
#endif
	}

	GGE_inline double4 frac(const double4& f)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double4(_GGE256_frac_pd(f.vec));
#else
		return double4(_GGE_frac_pd(f.vec0), _GGE_frac_pd(f.vec1));
#endif
	}

	GGE_inline double1 length(const double1& f) { return f; }
	GGE_inline double1 length(const double2& f) { return double1(_GGE_sqrt_pd(_GGE_dot2_pd(f.vec, f.vec))); }
	GGE_inline double1 length(const double3& f)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double1(_GGE_sqrt_pd(_GGE256_dot3_pd(f.vec, f.vec)));
#else
		return double1(_GGE_sqrt_pd(_GGE_dot3_pd(f.vec0, f.vec1, f.vec0, f.vec1)));
#endif
	}

	GGE_inline double1 length(const double4& f)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double1(_GGE_sqrt_pd(_GGE256_dot4_pd(f.vec, f.vec)));
#else
		return double1(_GGE_sqrt_pd(_GGE_dot4_pd(f.vec0, f.vec1, f.vec0, f.vec1)));
#endif
	}

	GGE_inline double1 lerp(const double1& f1, const double1& f2, const double1& a) { return double1(_GGE_lerp_pd(f1.vec, f2.vec, a.vec)); }
	GGE_inline double2 lerp(const double2& f1, const double2& f2, const double2& a) { return double2(_GGE_lerp_pd(f1.vec, f2.vec, a.vec)); }

	GGE_inline double3 lerp(const double3& f1, const double3& f2, const double3& a)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double3(_GGE256_lerp_pd(f1.vec, f2.vec, a.vec));
#else
		return double3(_GGE_lerp_pd(f1.vec0, f2.vec0, a.vec0), _GGE_lerp_pd(f1.vec1, f2.vec1, a.vec1));
#endif
	}

	GGE_inline double4 lerp(const double4& f1, const double4& f2, const double4& a)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double4(_GGE256_lerp_pd(f1.vec, f2.vec, a.vec));
#else
		return double4(_GGE_lerp_pd(f1.vec0, f2.vec0, a.vec0), _GGE_lerp_pd(f1.vec1, f2.vec1, a.vec1));
#endif
	}

	GGE_inline double1 min(const double1& f1, const double1& f2) { return double1(_GGE_min_pd(f1.vec, f2.vec)); }
	GGE_inline double2 min(const double2& f1, const double2& f2) { return double2(_GGE_min_pd(f1.vec, f2.vec)); }
	GGE_inline double3 min(const double3& f1, const double3& f2)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double3(_GGE256_min_pd(f1.vec, f2.vec));
#else
		return double3(_GGE_min_pd(f1.vec0, f2.vec0), _GGE_min_pd(f1.vec1, f2.vec1));
#endif
	}

	GGE_inline double4 min(const double4& f1, const double4& f2)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double4(_GGE256_min_pd(f1.vec, f2.vec));
#else
		return double4(_GGE_min_pd(f1.vec0, f2.vec0), _GGE_min_pd(f1.vec1, f2.vec1));
#endif
	}

	GGE_inline double1 mad(const double1& f1, const double1& f2, const double1& f3) { return double1(_GGE_madd_pd(f1.vec, f2.vec, f3.vec)); }
	GGE_inline double2 mad(const double2& f1, const double2& f2, const double2& f3) { return double2(_GGE_madd_pd(f1.vec, f2.vec, f3.vec)); }
	GGE_inline double3 mad(const double3& f1, const double3& f2, const double3& f3)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double3(_GGE256_madd_pd(f1.vec, f2.vec, f3.vec));
#else
		return double3(_GGE_madd_pd(f1.vec0, f2.vec0, f3.vec0), _GGE_madd_pd(f1.vec1, f2.vec1, f3.vec1));
#endif
	}

	GGE_inline double4 mad(const double4& f1, const double4& f2, const double4& f3)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double4(_GGE256_madd_pd(f1.vec, f2.vec, f3.vec));
#else
		return double4(_GGE_madd_pd(f1.vec0, f2.vec0, f3.vec0), _GGE_madd_pd(f1.vec1, f2.vec1, f3.vec1));
#endif
	}

	GGE_inline double1 max(const double1& f1, const double1& f2) { return double1(_GGE_max_pd(f1.vec, f2.vec)); }
	GGE_inline double2 max(const double2& f1, const double2& f2) { return double2(_GGE_max_pd(f1.vec, f2.vec)); }
	GGE_inline double3 max(const double3& f1, const double3& f2)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double3(_GGE256_max_pd(f1.vec, f2.vec));
#else
		return double3(_GGE_max_pd(f1.vec0, f2.vec0), _GGE_max_pd(f1.vec1, f2.vec1));
#endif
	}

	GGE_inline double4 max(const double4& f1, const double4& f2)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double4(_GGE256_max_pd(f1.vec, f2.vec));
#else
		return double4(_GGE_max_pd(f1.vec0, f2.vec0), _GGE_max_pd(f1.vec1, f2.vec1));
#endif
	}

	GGE_inline double1 modf(const double1& f1, double1& integerPart)
	{
		n128d signedFrac, signedInteger;
		_GGE_modf_pd(f1.vec, signedInteger, signedFrac);
		integerPart = double1(signedInteger);
		return double1(signedFrac);
	}

	GGE_inline double2 modf(const double2& f1, double2& integerPart)
	{
		n128d signedFrac, signedInteger;
		_GGE_modf_pd(f1.vec, signedInteger, signedFrac);
		integerPart = double2(signedInteger);
		return double2(signedFrac);
	}

	GGE_inline double3 modf(const double3& f1, double3& integerPart)
	{
#if defined(GGE_SIMD_REGISTER_256)
		n256d signedFrac, signedInteger;
		_GGE256_modf_pd(f1.vec, signedInteger, signedFrac);
		integerPart = double3(signedInteger);
		return double3(signedFrac);
#else
		n128d signedFrac0, signedInteger0, signedFrac1, signedInteger1;
		_GGE_modf_pd(f1.vec0, signedInteger0, signedFrac0);
		_GGE_modf_pd(f1.vec1, signedInteger1, signedFrac1);
		integerPart = double3(signedInteger0, signedInteger1);
		return double3(signedFrac0, signedFrac1);
#endif
	}

	GGE_inline double4 modf(const double4& f1, double4& integerPart)
	{
#if defined(GGE_SIMD_REGISTER_256)
		n256d signedFrac, signedInteger;
		_GGE256_modf_pd(f1.vec, signedInteger, signedFrac);
		integerPart = double4(signedInteger);
		return double4(signedFrac);
#else
		n128d signedFrac0, signedInteger0, signedFrac1, signedInteger1;
		_GGE_modf_pd(f1.vec0, signedInteger0, signedFrac0);
		_GGE_modf_pd(f1.vec1, signedInteger1, signedFrac1);
		integerPart = double4(signedInteger0, signedInteger1);
		return double4(signedFrac0, signedFrac1);
#endif
	}

	GGE_inline double1 normalize(const double1&/* f*/) { return double1(1.0f); }
	GGE_inline double2 normalize(const double2& f) { return double2(_GGE_div_pd(f.vec, _GGE_perm_xx_pd(_GGE_sqrt_pd(_GGE_dot2_pd(f.vec, f.vec))))); }
	GGE_inline double3 normalize(const double3& f)
	{
#if defined(GGE_SIMD_REGISTER_256)		
		n128d dot3 = _GGE256_dot3_pd(f.vec, f.vec);
		return double3(_GGE256_div_pd(f.vec, _GGE256_perm_xxxx_pd(_GGE256_sqrt_pd(_GGE256_set128_pd(dot3, dot3)))));
#else
		return double3(
			_GGE_div_pd(f.vec0, _GGE_perm_xx_pd(_GGE_sqrt_pd(_GGE_dot3_pd(f.vec0, f.vec1, f.vec0, f.vec1)))),
			_GGE_div_pd(f.vec1, _GGE_perm_xx_pd(_GGE_sqrt_pd(_GGE_dot3_pd(f.vec0, f.vec1, f.vec0, f.vec1))))
		);
#endif
	}

	GGE_inline double4 normalize(const double4& f)
	{
#if defined(GGE_SIMD_REGISTER_256)
		n128d dot4 = _GGE256_dot4_pd(f.vec, f.vec);
		return double4(_GGE256_div_pd(f.vec, _GGE256_perm_xxxx_pd(_GGE256_sqrt_pd(_GGE256_set128_pd(dot4, dot4)))));
#else
		return double4(
			_GGE_div_pd(f.vec0, _GGE_perm_xx_pd(_GGE_sqrt_pd(_GGE_dot4_pd(f.vec0, f.vec1, f.vec0, f.vec1)))),
			_GGE_div_pd(f.vec1, _GGE_perm_xx_pd(_GGE_sqrt_pd(_GGE_dot4_pd(f.vec0, f.vec1, f.vec0, f.vec1))))
		);
#endif
	}

	GGE_inline double1 select(const double1& condition, const double1& f1, const double1& f2) { return double1(_GGE_sel_pd(f1.vec, f2.vec, _GGE_cmpeq_pd(condition.vec, _GGE_setzero_pd()))); }
	GGE_inline double2 select(const double2& condition, const double2& f1, const double2& f2) { return double2(_GGE_sel_pd(f1.vec, f2.vec, _GGE_cmpeq_pd(condition.vec, _GGE_setzero_pd()))); }

	GGE_inline double3 select(const double3& condition, const double3& f1, const double3& f2)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double3(_GGE256_sel_pd(f1.vec, f2.vec, _GGE256_cmpeq_pd(condition.vec, _GGE256_setzero_pd())));
#else
		return double3
		(
			_GGE_sel_pd(f1.vec0, f2.vec0, _GGE_cmpeq_pd(condition.vec0, _GGE_setzero_pd())),
			_GGE_sel_pd(f1.vec1, f2.vec1, _GGE_cmpeq_pd(condition.vec1, _GGE_setzero_pd()))
		);
#endif
	}

	GGE_inline double4 select(const double4& condition, const double4& f1, const double4& f2)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double4(_GGE256_sel_pd(f1.vec, f2.vec, _GGE256_cmpeq_pd(condition.vec, _GGE256_setzero_pd())));
#else
		return double4
		(
			_GGE_sel_pd(f1.vec0, f2.vec0, _GGE_cmpeq_pd(condition.vec0, _GGE_setzero_pd())),
			_GGE_sel_pd(f1.vec1, f2.vec1, _GGE_cmpeq_pd(condition.vec1, _GGE_setzero_pd()))
		);
#endif
	}

	GGE_inline double1 radians(const double1& f) { return double1(_GGE_mul_pd(f.vec, d2_deg2rad)); }
	GGE_inline double2 radians(const double2& f) { return double2(_GGE_mul_pd(f.vec, d2_deg2rad)); }
	GGE_inline double3 radians(const double3& f)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double3(_GGE256_mul_pd(f.vec, d4_deg2rad));
#else
		return double3(_GGE_mul_pd(f.vec0, d2_deg2rad), _GGE_mul_pd(f.vec1, d2_deg2rad));
#endif
	}

	GGE_inline double4 radians(const double4& f)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double4(_GGE256_mul_pd(f.vec, d4_deg2rad));
#else
		return double4(_GGE_mul_pd(f.vec0, d2_deg2rad), _GGE_mul_pd(f.vec1, d2_deg2rad));
#endif
	}

	GGE_inline double1 rcp(const double1& f) { return double1(_GGE_rcp_pd(f.vec)); }
	GGE_inline double2 rcp(const double2& f) { return double2(_GGE_rcp_pd(f.vec)); }
	GGE_inline double3 rcp(const double3& f)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double3(_GGE256_rcp_pd(f.vec));
#else
		return double3(_GGE_rcp_pd(f.vec0), _GGE_rcp_pd(f.vec1));
#endif
	
	}
	GGE_inline double4 rcp(const double4& f)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double4(_GGE256_rcp_pd(f.vec));
#else
		return double4(_GGE_rcp_pd(f.vec0), _GGE_rcp_pd(f.vec1));
#endif
	}

	GGE_inline double1 rsqrt(const double1& f) { return double1(_GGE_rsqrt_pd(f.vec)); }
	GGE_inline double2 rsqrt(const double2& f) { return double2(_GGE_rsqrt_pd(f.vec)); }
	GGE_inline double3 rsqrt(const double3& f)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double3(_GGE256_rsqrt_pd(f.vec));
#else
		return double3(_GGE_rsqrt_pd(f.vec0), _GGE_rsqrt_pd(f.vec1));
#endif
	}

	GGE_inline double4 rsqrt(const double4& f)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double4(_GGE256_rsqrt_pd(f.vec));
#else
		return double4(_GGE_rsqrt_pd(f.vec0), _GGE_rsqrt_pd(f.vec1));
#endif
	}

	GGE_inline double1 round(const double1& f) { return double1(_GGE_round_pd(f.vec)); }
	GGE_inline double2 round(const double2& f) { return double2(_GGE_round_pd(f.vec)); }
	GGE_inline double3 round(const double3& f)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double3(_GGE256_round_pd(f.vec));
#else
		return double3(_GGE_round_pd(f.vec0), _GGE_round_pd(f.vec1));
#endif
	}

	GGE_inline double4 round(const double4& f)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double4(_GGE256_round_pd(f.vec));
#else
		return double4(_GGE_round_pd(f.vec0), _GGE_round_pd(f.vec1));
#endif
	}

	GGE_inline double1 saturate(const double1& f) { return double1(_GGE_sat_pd(f.vec)); }
	GGE_inline double2 saturate(const double2& f) { return double2(_GGE_sat_pd(f.vec)); }
	GGE_inline double3 saturate(const double3& f)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double3(_GGE256_sat_pd(f.vec));
#else
		return double3(_GGE_sat_pd(f.vec0), _GGE_sat_pd(f.vec1));
#endif
	}

	GGE_inline double4 saturate(const double4& f)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double4(_GGE256_sat_pd(f.vec));
#else
		return double4(_GGE_sat_pd(f.vec0), _GGE_sat_pd(f.vec1));
#endif
	}

	GGE_inline double1 sign(const double1& f) { return double1(_GGE_sign_pd(f.vec)); }
	GGE_inline double2 sign(const double2& f) { return double2(_GGE_sign_pd(f.vec)); }
	GGE_inline double3 sign(const double3& f)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double3(_GGE256_sign_pd(f.vec));
#else
		return double3(_GGE_sign_pd(f.vec0), _GGE_sign_pd(f.vec1));
#endif
	}

	GGE_inline double4 sign(const double4& f)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double4(_GGE256_sign_pd(f.vec));
#else
		return double4(_GGE_sign_pd(f.vec0), _GGE_sign_pd(f.vec1));
#endif
	}

	GGE_inline double1 sqrt(const double1& f) { return double1(_GGE_sqrt_pd(f.vec)); }
	GGE_inline double2 sqrt(const double2& f) { return double2(_GGE_sqrt_pd(f.vec)); }
	GGE_inline double3 sqrt(const double3& f)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double3(_GGE256_sqrt_pd(f.vec));
#else
		return double3(_GGE_sqrt_pd(f.vec0), _GGE_sqrt_pd(f.vec1));
#endif
	}

	GGE_inline double4 sqrt(const double4& f)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double4(_GGE256_sqrt_pd(f.vec));
#else
		return double4(_GGE_sqrt_pd(f.vec0), _GGE_sqrt_pd(f.vec1));
#endif
	}

	GGE_inline double1 step(const double1& f1, const double1& f2) { return double1(_GGE_step_pd(f1.vec, f2.vec)); }
	GGE_inline double2 step(const double2& f1, const double2& f2) { return double2(_GGE_step_pd(f1.vec, f2.vec)); }
	GGE_inline double3 step(const double3& f1, const double3& f2)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double3(_GGE256_step_pd(f1.vec, f2.vec));
#else
		return double3(_GGE_step_pd(f1.vec0, f2.vec0), _GGE_step_pd(f1.vec1, f2.vec1));
#endif
	}

	GGE_inline double4 step(const double4& f1, const double4& f2)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double4(_GGE256_step_pd(f1.vec, f2.vec));
#else
		return double4(_GGE_step_pd(f1.vec0, f2.vec0), _GGE_step_pd(f1.vec1, f2.vec1));
#endif
	}
	
	GGE_inline double1 trunc(const double1& f) { return double1(_GGE_trunc_pd(f.vec)); }
	GGE_inline double2 trunc(const double2& f) { return double2(_GGE_trunc_pd(f.vec)); }
	GGE_inline double3 trunc(const double3& f)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double3(_GGE256_trunc_pd(f.vec));
#else
		return double3(_GGE_trunc_pd(f.vec0), _GGE_trunc_pd(f.vec1));
#endif
	}

	GGE_inline double4 trunc(const double4& f)
	{
#if defined(GGE_SIMD_REGISTER_256)
		return double4(_GGE256_trunc_pd(f.vec));
#else
		return double4(_GGE_trunc_pd(f.vec0), _GGE_trunc_pd(f.vec1));
#endif
	}

	//--------------------------------------------------------------------------------------------------------------------------
	// Function disambiguation. This typically happens when pulling in math.h, <cmath> or <algorithm>, where functions now live
	// in the global namespace. Due to implicit conversions, we need to clarify to the compiler which functions it needs to use.
	//--------------------------------------------------------------------------------------------------------------------------

	template<typename T> GGE_inline GGE_enable_if_return(T, double1) operator == (const double1& f1, T f2) { return f1 == double1(f2); }
	template<typename T> GGE_inline GGE_enable_if_return(T, double1) operator == (T f1, const double1& f2) { return double1(f1) == f2; }

	template<int X> GGE_inline double1 operator - (const dswizzle1<X>& s) { return -double1(s); }

	template<int X> GGE_inline double1 abs(const dswizzle1<X>& s) { return abs(double1(s)); }

	template<int X> GGE_inline double1 ceil(const dswizzle1<X>& s) { return ceil(double1(s)); }
	template<int X> GGE_inline double1 floor(const dswizzle1<X>& s) { return floor(double1(s)); }
	template<int X> GGE_inline double1 frac(const dswizzle1<X>& s) { return frac(double1(s)); }
	template<int X> GGE_inline double1 round(const dswizzle1<X>& s) { return round(double1(s)); }
	template<int X> GGE_inline double1 sqrt(const dswizzle1<X>& s) { return sqrt(double1(s)); }
	template<int X> GGE_inline double1 trunc(const dswizzle1<X>& s) { return trunc(double1(s)); }

	template<int X>
	GGE_inline dswizzle1<X>& dswizzle1<X>::operator = (double f)
	{
		vec[X / 2] = _GGE_blend_pd(vec[X / 2], _GGE_set1_pd(f), GGE_COMPONENT_X(X % 2));
		return *this;
	}

	// Revise these functions. Can I not do with swizzle?

	template<int X>
	template<int A>
	GGE_inline dswizzle1<X>& dswizzle1<X>::operator = (const dswizzle1<A>& s)
	{
		n128d t = _GGE_shuffle_pd(s.vec[A / 2], s.vec[A / 2], GGE_SHUFFLE_MASK_PD(A % 2, A % 2));
		vec[X / 2] = _GGE_blend_pd(vec[X / 2], t, GGE_COMPONENT_X(X % 2));
		return *this;
	}

	template<int X>
	GGE_inline dswizzle1<X>& dswizzle1<X>::operator = (const dswizzle1<X>& s)
	{
		n128d t = _GGE_shuffle_pd(s.vec[X / 2], s.vec[X / 2], GGE_SHUFFLE_MASK_PD(X % 2, X % 2));
		vec[X / 2] = _GGE_blend_pd(vec[X / 2], t, GGE_COMPONENT_X(X % 2));
		return *this;
	}

	template<int X>
	GGE_inline dswizzle1<X>& dswizzle1<X>::operator = (const double1& f)
	{
		vec[X / 2] = _GGE_blend_pd(vec[X / 2], _GGE_perm_xx_pd(f.vec), GGE_COMPONENT_X(X));
		return *this;
	}

	template<int X, int Y>
	template<int E, int F>
	GGE_inline dswizzle2<X, Y>& dswizzle2<X, Y>::operator = (const dswizzle2<E, F>& s)
	{
		static_assert(X != Y, "\"l-value specifies const object\" No component can be equal for assignment.");
		swizzle_all<E, F>(s);
		return *this;
	}

	template<int X, int Y>
	GGE_inline dswizzle2<X, Y>& dswizzle2<X, Y>::operator = (const dswizzle2<X, Y>& s)
	{
		static_assert(X != Y, "\"l-value specifies const object\" No component can be equal for assignment.");
		swizzle_all<X, Y>(s);
		return *this;
	}

	template<int X, int Y>
	dswizzle2<X, Y>& dswizzle2<X, Y>::operator = (const double2& f)
	{
		static_assert(X != Y, "\"l-value specifies const object\" No component can be equal for assignment.");

		GGE_constexpr_if((X < 2 && Y < 2) || (X >= 2 && Y >= 2))
		{
			vec[(X < 2 && Y < 2) ? 0 : 1] = _GGE_perm_pd(f.vec, GGE_SHUFFLE_MASK_PD((X % 2) == 0 ? 0 : 1, (Y % 2) == 0 ? 0 : 1));
			//vec[(X < 2 && Y < 2) ? 0 : 1] = swizzle<0, 1, X, Y>(f.vec);
		}
		else
		{
			// Swizzle E and F into both 0 and 1
			n128d swizzledE = _GGE_perm_xx_pd(f.vec);
			n128d swizzledF = _GGE_perm_yy_pd(f.vec);

			// Blend with original vectors to preserve contents in remaining entries
			vec[X / 2] = _GGE_blend_pd(vec[X / 2], swizzledE, GGE_BLEND_MASK_PD((X % 2) == 1, (X % 2) == 0));
			vec[Y / 2] = _GGE_blend_pd(vec[Y / 2], swizzledF, GGE_BLEND_MASK_PD((Y % 2) == 1, (Y % 2) == 0));
		}

		return *this;
	}

	template<int X, int Y, int Z>
	template<int A, int B, int C>
	GGE_inline dswizzle3<X, Y, Z>& dswizzle3<X, Y, Z>::operator = (const dswizzle3<A, B, C>& s)
	{
		static_assert(X != Y && X != Z && Y != Z, "\"l-value specifies const object\" No component can be equal for assignment.");
		swizzle_all<A, B, C>(s);
		return *this;
	}

	template<int X, int Y, int Z>
	GGE_inline dswizzle3<X, Y, Z>& dswizzle3<X, Y, Z>::operator = (const dswizzle3<X, Y, Z>& s)
	{
		static_assert(X != Y && X != Z && Y != Z, "\"l-value specifies const object\" No component can be equal for assignment.");
		swizzle_all<X, Y, Z>(s);
		return *this;
	}

	template<int X, int Y, int Z>
	dswizzle3<X, Y, Z>& dswizzle3<X, Y, Z>::operator = (const double3& f)
	{
		static_assert(X != Y && X != Z && Y != Z, "\"l-value specifies const object\" No component can be equal for assignment.");
#if defined(GGE_SIMD_REGISTER_256)
		swizzleblend<0, 1, 2, X, Y, Z>(f.vec, vec);
#else
		swizzleblend<0, 1, 2, X, Y, Z>(f.vec0, f.vec1, vec[0], vec[1]);
#endif
		return *this;
	}

	template<int X, int Y, int Z, int W>
	template<int A, int B, int C, int D>
	GGE_inline dswizzle4<X, Y, Z, W>& dswizzle4<X, Y, Z, W>::operator = (const dswizzle4<A, B, C, D>& s)
	{
		static_assert(X != Y && X != Z && X != W && Y != Z && Y != W && Z != W, "\"l-value specifies const object\" No component can be equal for assignment.");
#if defined(GGE_SIMD_REGISTER_256)
		swizzle<A, B, C, D, X, Y, Z, W>(s.vec, vec);
#else
		swizzle<A, B, C, D, X, Y, Z, W>(s.vec[0], s.vec[1], vec[0], vec[1]);
#endif
		return *this;
	}

	template<int X, int Y, int Z, int W>
	dswizzle4<X, Y, Z, W>& dswizzle4<X, Y, Z, W>::operator = (const double4& f)
	{
		static_assert(X != Y && X != Z && X != W && Y != Z && Y != W && Z != W, "\"l-value specifies const object\" No component can be equal for assignment.");
#if defined(GGE_SIMD_REGISTER_256)
		swizzle<0, 1, 2, 3, X, Y, Z, W>(f.vec, vec);
#else
		swizzle<0, 1, 2, 3, X, Y, Z, W>(f.vec0, f.vec1, vec[0], vec[1]);
#endif
		return *this;
	}
}

#endif