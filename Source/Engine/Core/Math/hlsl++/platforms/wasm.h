#pragma once

#include <wasm_simd128.h>

typedef __f32x4 n128;
typedef __i32x4 n128i;
typedef __i32x4 n128u;
typedef __i64x2 n128d;

//------
// Float
//------

#define _GGE_set1_ps(x)						wasm_f32x4_splat((x))
#define _GGE_set_ps(x, y, z, w)				wasm_f32x4_make((x), (y), (z), (w))
#define _GGE_setzero_ps()					wasm_f32x4_const_splat(0.0f)

#define _GGE_add_ps(x, y)					wasm_f32x4_add((x), (y))
#define _GGE_sub_ps(x, y)					wasm_f32x4_sub((x), (y))
#define _GGE_mul_ps(x, y)					wasm_f32x4_mul((x), (y))
#define _GGE_div_ps(x, y)					wasm_f32x4_div((x), (y))

#define _GGE_rcp_ps(x)						wasm_f32x4_div(wasm_f32x4_const_splat(1.0f), (x))

#define _GGE_neg_ps(x)						wasm_v128_xor((x), f4negativeMask)

#define _GGE_madd_ps(x, y, z)				wasm_f32x4_add(wasm_f32x4_mul((x), (y)), (z)) // x * y + z
#define _GGE_msub_ps(x, y, z)				wasm_f32x4_sub(wasm_f32x4_mul((x), (y)), (z)) // x * y - z
#define _GGE_subm_ps(x, y, z)				wasm_f32x4_sub((x), wasm_f32x4_mul((y), (z))) // x - y * z

// Reference http://www.liranuna.com/sse-intrinsics-optimizations-in-popular-compilers/
#define _GGE_abs_ps(x)						wasm_v128_and(wasm_i32x4_splat(0x7fffffff), (x))

#define _GGE_sqrt_ps(x)						wasm_f32x4_sqrt((x))
#define _GGE_rsqrt_ps(x)						wasm_f32x4_div(wasm_f32x4_const_splat(1.0f), wasm_f32x4_sqrt(x))

#define _GGE_cmpeq_ps(x, y)					wasm_f32x4_eq((x), (y))
#define _GGE_cmpneq_ps(x, y)					wasm_f32x4_ne((x), (y))

#define _GGE_cmpgt_ps(x, y)					wasm_f32x4_gt((x), (y))
#define _GGE_cmpge_ps(x, y)					wasm_f32x4_ge((x), (y))

#define _GGE_cmplt_ps(x, y)					wasm_f32x4_lt((x), (y))
#define _GGE_cmple_ps(x, y)					wasm_f32x4_le((x), (y))

#define _GGE_max_ps(x, y)					wasm_f32x4_pmax((x), (y))
#define _GGE_min_ps(x, y)					wasm_f32x4_pmin((x), (y))

#define _GGE_sel_ps(x, y, mask)				wasm_v128_xor((x), wasm_v128_and(mask, wasm_v128_xor((y), (x))))

#define _GGE_blend_ps(x, y, mask)			wasm_i32x4_shuffle(x, y, (mask & 1) ? 4 : 0, ((mask >> 1) & 1) ? 5 : 1, ((mask >> 2) & 1) ? 6 : 2, ((mask >> 3) & 1) ? 7 : 3)

#define _GGE_trunc_ps(x)						wasm_f32x4_trunc((x))
#define _GGE_floor_ps(x)						wasm_f32x4_floor((x))
#define _GGE_ceil_ps(x)						wasm_f32x4_ceil((x))
#define _GGE_round_ps(x)						wasm_f32x4_nearest((x))

#define _GGE_frac_ps(x)						wasm_f32x4_sub((x), wasm_f32x4_floor(x))

#define _GGE_clamp_ps(x, minx, maxx)			wasm_f32x4_pmax(wasm_f32x4_pmin((x), (maxx)), (minx))
#define _GGE_sat_ps(x)						wasm_f32x4_pmax(wasm_f32x4_pmin((x), wasm_f32x4_const_splat(1.0f)), wasm_f32x4_const_splat(0.0f))

#define _GGE_and_ps(x, y)					wasm_v128_and((x), (y))
#define _GGE_andnot_ps(x, y)					wasm_v128_andnot((x), (y))
#define _GGE_not_ps(x)						wasm_v128_andnot((x), f4_fff)
#define _GGE_or_ps(x, y)						wasm_v128_or((x), (y))
#define _GGE_xor_ps(x, y)					wasm_v128_xor((x), (y))

// Equivalent to shuffle(x, y, X, Y, X, Y)
#define _GGE_movelh_ps(x, y)					wasm_i32x4_shuffle((x), (y), 0, 1, 4, 5)

// Equivalent to shuffle(y, x, Z, W, Z, W)
#define _GGE_movehl_ps(x, y)					wasm_i32x4_shuffle((x), (y), 2, 3, 6, 7)

// Equivalent to shuffle(x, x, Y, Y, W, W)
#define _GGE_movehdup_ps(x)					wasm_i32x4_shuffle((x), (x), 1, 1, 7, 7)

#define _GGE_perm_ps(x, X, Y, Z, W)			wasm_i32x4_shuffle((x), (x), X, Y, Z, W)

#define _GGE_shuffle_ps(x, y, X, Y, A, B)	wasm_i32x4_shuffle((x), (y), X, Y, 4 + A, 4 + B)

#define _GGE_unpacklo_ps(x, y)				wasm_i32x4_shuffle((x), (y), 0, 4, 1, 5)

#define _GGE_unpackhi_ps(x, y)				wasm_i32x4_shuffle((x), (y), 2, 6, 3, 7)

GGE_inline n128 _GGE_dot4_ps(n128 x, n128 y)
{
	n128 mul    = wasm_f32x4_mul(x, y);                      // Multiply components
	n128 shuf   = wasm_i32x4_shuffle(mul, mul, 1, 0, 3, 0);  // Move y into x, and w into z (ignore the rest)
	n128 add    = wasm_f32x4_add(shuf, mul);                 // Contains x+y, _, z+w, _
	shuf        = wasm_i32x4_shuffle(shuf, add, 2, 0, 0, 0); // Move (z + w) into x
	n128 result = wasm_f32x4_add(add, shuf);                 // Contains x+y+z+w, _, _, _
	return result;
}

GGE_inline bool _GGE_any1_ps(n128 x)
{
	return (wasm_i32x4_bitmask(wasm_f32x4_eq(x, wasm_f32x4_const_splat(0.0f))) & 0x1) != 0x1;
}

GGE_inline bool _GGE_any2_ps(n128 x)
{
	return (wasm_i32x4_bitmask(wasm_f32x4_eq(x, wasm_f32x4_const_splat(0.0f))) & 0x3) != 0x3;
}

GGE_inline bool _GGE_any3_ps(n128 x)
{
	return (wasm_i32x4_bitmask(wasm_f32x4_eq(x, wasm_f32x4_const_splat(0.0f))) & 0x7) != 0x7;
}

GGE_inline bool _GGE_any4_ps(n128 x)
{
	return wasm_i32x4_bitmask(wasm_f32x4_eq(x, wasm_f32x4_const_splat(0.0f))) != 0xf;
}

GGE_inline bool _GGE_all1_ps(n128 x)
{
	return (wasm_i32x4_bitmask(wasm_f32x4_eq(x, wasm_f32x4_const_splat(0.0f))) & 0x1) == 0;
}

GGE_inline bool _GGE_all2_ps(n128 x)
{
	return (wasm_i32x4_bitmask(wasm_f32x4_eq(x, wasm_f32x4_const_splat(0.0f))) & 0x3) == 0;
}

GGE_inline bool _GGE_all3_ps(n128 x)
{
	return (wasm_i32x4_bitmask(wasm_f32x4_eq(x, wasm_f32x4_const_splat(0.0f))) & 0x7) == 0;
}

GGE_inline bool _GGE_all4_ps(n128 x)
{
	return wasm_i32x4_bitmask(wasm_f32x4_eq(x, wasm_f32x4_const_splat(0.0f))) == 0;
}

//-----------------
// Float Store/Load
//-----------------

GGE_inline void _GGE_store1_ps(float* dst, n128 src)
{
	wasm_v128_store32_lane(dst, src, 0);
}

GGE_inline void _GGE_store2_ps(float* dst, n128 src)
{
	wasm_v128_store64_lane(dst, src, 0);
}

GGE_inline void _GGE_store3_ps(float* dst, n128 src)
{
	wasm_v128_store64_lane(dst, src, 0);
	wasm_v128_store32_lane(dst + 2, src, 2);
}

GGE_inline void _GGE_store4_ps(float* dst, n128 src)
{
	wasm_v128_store(dst, src);
}

// Store first 3, store second 3, store last 2 and then the last one
// We need to do it this way to avoid stomping memory outside the provided buffer
GGE_inline void _GGE_store3x3_ps(float* dst, n128 src0, n128 src1, n128 src2)
{
	wasm_v128_store(dst, src0);
	wasm_v128_store(dst + 3, src1);
	wasm_v128_store64_lane(dst + 6, src2, 0);
	wasm_v128_store32_lane(dst + 8, src2, 2);
}

GGE_inline void _GGE_store4x4_ps(float* dst, const n128& src0, const n128& src1, const n128& src2, const n128& src3)
{
	wasm_v128_store(dst, src0);
	wasm_v128_store(dst + 4, src1);
	wasm_v128_store(dst + 8, src2);
	wasm_v128_store(dst + 12, src3);
}

GGE_inline void _GGE_load1_ps(n128& dst, const float* src)
{
	dst = wasm_v128_load32_lane(src, dst, 0);
}

GGE_inline void _GGE_load2_ps(n128& dst, const float* src)
{
	dst = wasm_v128_load64_lane(src, dst, 0);
}

GGE_inline void _GGE_load3_ps(n128& dst, const float* src)
{
	dst = wasm_i32x4_shuffle(wasm_v128_load64_lane(src, dst, 0), wasm_v128_load32_lane(src + 2, dst, 0), 0, 1, 4, 5);
}

GGE_inline void _GGE_load4_ps(n128& dst, const float* src)
{
	dst = wasm_v128_load(src);
}

GGE_inline void _GGE_load3x3_ps(n128& dst0, n128& dst1, n128& dst2, const float* src)
{
	dst0 = wasm_v128_load(src);
	dst1 = wasm_v128_load(src + 3);
	dst2 = wasm_v128_load(src + 6);
}

GGE_inline void _GGE_load4x4_ps(n128& dst0, n128& dst1, n128& dst2, n128& dst3, const float* src)
{
	dst0 = wasm_v128_load(src);
	dst1 = wasm_v128_load(src + 4);
	dst2 = wasm_v128_load(src + 8);
	dst3 = wasm_v128_load(src + 12);
}

//--------
// Integer
//--------

#define _GGE_set1_epi32(x)					wasm_i32x4_splat((x))
#define _GGE_set_epi32(x, y, z, w)			wasm_i32x4_make((x), (y), (z), (w))
#define _GGE_setzero_epi32()					wasm_i32x4_const_splat(0)

#define _GGE_add_epi32(x, y)					wasm_i32x4_add((x), (y))
#define _GGE_sub_epi32(x, y)					wasm_i32x4_sub((x), (y))
#define _GGE_mul_epi32(x, y)					wasm_i32x4_mul((x), (y))
#define _GGE_div_epi32(x, y)					wasm_i32x4_trunc_sat_f32x4(wasm_f32x4_div(wasm_f32x4_convert_i32x4(x), wasm_f32x4_convert_i32x4(y)))

#define _GGE_neg_epi32(x)					wasm_i32x4_add(wasm_v128_xor((x), i4fffMask), wasm_i32x4_const_splat(1))

#define _GGE_madd_epi32(x, y, z)				wasm_i32x4_add(wasm_i32x4_mul((x), (y)), (z))
#define _GGE_msub_epi32(x, y, z)				wasm_i32x4_sub(wasm_i32x4_mul((x), (y)), (z))
#define _GGE_subm_epi32(x, y, z)				wasm_i32x4_sub((x), wasm_i32x4_mul((y), (z)))

#define _GGE_abs_epi32(x)					wasm_i32x4_abs((x))

#define _GGE_cmpeq_epi32(x, y)				wasm_i32x4_eq((x), (y))
#define _GGE_cmpneq_epi32(x, y)				wasm_i32x4_ne((x), (y))

#define _GGE_cmpgt_epi32(x, y)				wasm_i32x4_gt((x), (y))
#define _GGE_cmpge_epi32(x, y)				wasm_i32x4_ge((x), (y))

#define _GGE_cmplt_epi32(x, y)				wasm_i32x4_lt((x), (y))
#define _GGE_cmple_epi32(x, y)				wasm_i32x4_le((x), (y))

#define _GGE_max_epi32(x, y)					wasm_i32x4_max((x), (y))
#define _GGE_min_epi32(x, y)					wasm_i32x4_min((x), (y))

#define _GGE_sel_epi32(x, y, mask)			wasm_v128_xor((x), wasm_v128_and(mask, wasm_v128_xor((y), (x))))

#define _GGE_blend_epi32(x, y, mask)			wasm_i32x4_shuffle(x, y, (mask & 1) ? 4 : 0, ((mask >> 1) & 1) ? 5 : 1, ((mask >> 2) & 1) ? 6 : 2, ((mask >> 3) & 1) ? 7 : 3)

#define _GGE_clamp_epi32(x, minx, maxx)		wasm_i32x4_max(wasm_i32x4_min((x), (maxx)), (minx))
#define _GGE_sat_epi32(x)					wasm_i32x4_max(wasm_i32x4_min((x), i4_1), i4_0)

#define _GGE_and_si128(x, y)					wasm_v128_and((x), (y))
#define _GGE_andnot_si128(x, y)				wasm_v128_andnot((x), (y))
#define _GGE_not_si128(x)					wasm_v128_andnot((x), i4fffMask)
#define _GGE_or_si128(x, y)					wasm_v128_or((x), (y))
#define _GGE_xor_si128(x, y)					wasm_v128_xor((x), (y))

#define _GGE_perm_epi32(x, X, Y, Z, W)		wasm_i32x4_shuffle((x), (x), X, Y, Z, W)
#define _GGE_shuffle_epi32(x, y, X, Y, A, B)	wasm_i32x4_shuffle((x), (y), X, Y, 4 + A, 4 + B)

#define _GGE_castps_si128(x)					(x)
#define _GGE_castsi128_ps(x)					(x)

#define _GGE_cvtepi32_ps(x)					wasm_f32x4_convert_i32x4((x))
#define _GGE_cvttps_epi32(x)					wasm_i32x4_trunc_sat_f32x4((x))

// Shift left/right while shifting in zeroes
#define _GGE_slli_epi32(x, y)				wasm_i32x4_shl((x), (y))
#define _GGE_srli_epi32(x, y)				wasm_i32x4_shr((x), (y))

#define _GGE_sllv_epi32(x, y)				(x) // _mm_sllv_epi32((x), (y))
#define _GGE_srlv_epi32(x, y)				(x) // _mm_srlv_epi32((x), (y))

GGE_inline bool _GGE_any1_epi32(n128i x)
{
	return (wasm_i8x16_bitmask(wasm_i32x4_eq(x, wasm_i32x4_const_splat(0))) & 0xf) != 0xf;
}

GGE_inline bool _GGE_any2_epi32(n128i x)
{
	return (wasm_i8x16_bitmask(wasm_i32x4_eq(x, wasm_i32x4_const_splat(0))) & 0xff) != 0xff;
}

GGE_inline bool _GGE_any3_epi32(n128i x)
{
	return (wasm_i8x16_bitmask(wasm_i32x4_eq(x, wasm_i32x4_const_splat(0))) & 0xfff) != 0xfff;
}

GGE_inline bool _GGE_any4_epi32(n128i x)
{
	return (wasm_i8x16_bitmask(wasm_i32x4_eq(x, wasm_i32x4_const_splat(0))) & 0xffff) != 0xffff;
}

GGE_inline bool _GGE_all1_epi32(n128i x)
{
	return (wasm_i8x16_bitmask(wasm_i32x4_eq(x, wasm_i32x4_const_splat(0))) & 0xf) == 0;
}

GGE_inline bool _GGE_all2_epi32(n128i x)
{
	return (wasm_i8x16_bitmask(wasm_i32x4_eq(x, wasm_i32x4_const_splat(0))) & 0xff) == 0;
}

GGE_inline bool _GGE_all3_epi32(n128i x)
{
	return (wasm_i8x16_bitmask(wasm_i32x4_eq(x, wasm_i32x4_const_splat(0))) & 0xfff) == 0;
}

GGE_inline bool _GGE_all4_epi32(n128i x)
{
	return (wasm_i8x16_bitmask(wasm_i32x4_eq(x, wasm_i32x4_const_splat(0))) & 0xffff) == 0;
}

//-------------------
// Integer Store/Load
//-------------------

GGE_inline void _GGE_store1_epi32(int32_t* p, n128i x)
{
	wasm_v128_store32_lane(p, x, 0);
}

GGE_inline void _GGE_store2_epi32(int32_t* p, n128i x)
{
	wasm_v128_store64_lane(p, x, 0);
}

GGE_inline void _GGE_store3_epi32(int32_t* p, n128i x)
{
	wasm_v128_store64_lane(p, x, 0);
	wasm_v128_store32_lane(p + 2, x, 2);
}

GGE_inline void _GGE_store4_epi32(int32_t* p, n128i x)
{
	wasm_v128_store(p, x);
}

GGE_inline void _GGE_load1_epi32(int32_t* p, n128i& x)
{
	x = wasm_v128_load32_lane(p, x, 0);
}

GGE_inline void _GGE_load2_epi32(int32_t* p, n128i& x)
{
	x = wasm_v128_load64_lane(p, x, 0);
}

GGE_inline void _GGE_load3_epi32(int32_t* p, n128i& x)
{
	x = wasm_i32x4_shuffle(wasm_v128_load64_lane(p, x, 0), wasm_v128_load32_lane(p, x, 2), 0, 1, 3, 4);
}

GGE_inline void _GGE_load4_epi32(int32_t* p, n128i& x)
{
	x = wasm_v128_load(p);
}

//-----------------
// Unsigned Integer
//-----------------

#define _GGE_set1_epu32(x)					wasm_u32x4_splat((x))
#define _GGE_set_epu32(x, y, z, w)			wasm_u32x4_make((x), (y), (z), (w))
#define _GGE_setzero_epu32()					wasm_u32x4_const_splat(0)

#define _GGE_add_epu32(x, y)					wasm_i32x4_add((x), (y))
#define _GGE_sub_epu32(x, y)					wasm_i32x4_sub((x), (y))
#define _GGE_mul_epu32(x, y)					wasm_i32x4_mul((x), (y))
#define _GGE_div_epu32(x, y)					_GGE_div_epi32((x), (y))

#define _GGE_madd_epu32(x, y, z)				wasm_i32x4_add(wasm_i32x4_mul((x), (y)), (z))
#define _GGE_msub_epu32(x, y, z)				wasm_i32x4_sub(wasm_i32x4_mul((x), (y)), (z))
#define _GGE_subm_epu32(x, y, z)				wasm_i32x4_sub((x), wasm_i32x4_mul((y), (z)))

#define _GGE_cmpeq_epu32(x, y)				wasm_i32x4_eq((x), (y))
#define _GGE_cmpneq_epu32(x, y)				wasm_i32x4_ne((x), (y))

#define _GGE_cmpgt_epu32(x, y)				wasm_u32x4_gt((x), (y))
#define _GGE_cmpge_epu32(x, y)				wasm_u32x4_ge((x), (y))

#define _GGE_cmplt_epu32(x, y)				wasm_u32x4_lt((x), (y))
#define _GGE_cmple_epu32(x, y)				wasm_u32x4_le((x), (y))

#define _GGE_max_epu32(x, y)					wasm_u32x4_max((x), (y))
#define _GGE_min_epu32(x, y)					wasm_u32x4_min((x), (y))

#define _GGE_sel_epu32(x, y, mask)			_GGE_sel_epi32((x), (y), (mask))
#define _GGE_blend_epu32(x, y, mask)			_GGE_blend_epi32((x), (y), (mask))

#define _GGE_clamp_epu32(x, minx, maxx)		_GGE_max_epu32(_GGE_min_epu32((x), (maxx)), (minx))
#define _GGE_sat_epu32(x)					_GGE_max_epu32(_GGE_min_epu32((x), i4_1), i4_0)

#define _GGE_perm_epu32(x, X, Y, Z, W)		_GGE_perm_epi32((x), X, Y, Z, W)
#define _GGE_shuffle_epu32(x, y, X, Y, A, B)	_GGE_shuffle_epi32((x), (y), X, Y, A, B)

#define _GGE_cvttps_epu32(x)					_GGE_cvttps_epi32((x))
#define _GGE_cvtepu32_ps(x)					_GGE_cvtepi32_ps((x))

#define _GGE_slli_epu32(x, y)				_GGE_slli_epi32((x), (y))
#define _GGE_srli_epu32(x, y)				_GGE_srli_epi32((x), (y))

#define _GGE_sllv_epu32(x, y)				_GGE_sllv_epi32((x), (y))
#define _GGE_srlv_epu32(x, y)				_GGE_srlv_epi32((x), (y))

#define _GGE_any1_epu32(x)					_GGE_any1_epi32(x)
#define _GGE_any2_epu32(x)					_GGE_any2_epi32(x)
#define _GGE_any3_epu32(x)					_GGE_any3_epi32(x)
#define _GGE_any4_epu32(x)					_GGE_any4_epi32(x)

#define _GGE_all1_epu32(x)					_GGE_all1_epi32(x)
#define _GGE_all2_epu32(x)					_GGE_all2_epi32(x)
#define _GGE_all3_epu32(x)					_GGE_all3_epi32(x)
#define _GGE_all4_epu32(x)					_GGE_all4_epi32(x)

//----------------------------
// Unsigned Integer Store/Load
//----------------------------

GGE_inline void _GGE_store1_epu32(uint32_t* p, n128u x) { _GGE_store1_epi32((int32_t*)p, x); }
GGE_inline void _GGE_store2_epu32(uint32_t* p, n128u x) { _GGE_store2_epi32((int32_t*)p, x); }
GGE_inline void _GGE_store3_epu32(uint32_t* p, n128u x) { _GGE_store3_epi32((int32_t*)p, x); }
GGE_inline void _GGE_store4_epu32(uint32_t* p, n128u x) { _GGE_store4_epi32((int32_t*)p, x); }
GGE_inline void _GGE_load1_epu32(uint32_t* p, n128u& x) { _GGE_load1_epi32((int32_t*)p, x); }
GGE_inline void _GGE_load2_epu32(uint32_t* p, n128u& x) { _GGE_load2_epi32((int32_t*)p, x); }
GGE_inline void _GGE_load3_epu32(uint32_t* p, n128u& x) { _GGE_load3_epi32((int32_t*)p, x); }
GGE_inline void _GGE_load4_epu32(uint32_t* p, n128u& x) { _GGE_load4_epi32((int32_t*)p, x); }

//-------------
// Data Packing
//-------------

GGE_inline uint32_t _GGE_pack_epu32_rgba8_unorm(__f32x4 v)
{
	__f32x4 v255f = _GGE_madd_ps(v, wasm_f32x4_const_splat(255.0f), wasm_f32x4_const_splat(0.5f));
	__i32x4 v255i = wasm_i32x4_trunc_sat_f32x4(v255f);
	return wasm_i8x16_shuffle(v255i, v255i, 0, 4, 8, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)[0];
}

GGE_inline __f32x4 _GGE_unpack_rgba8_unorm_epu32(uint32_t p)
{
	__i32x4 i = wasm_u32x4_splat(p);
	__f32x4 t = wasm_f32x4_convert_u32x4(wasm_u32x4_extend_low_u16x8(wasm_u16x8_extend_low_u8x16(i)));
	return wasm_f32x4_mul(t, wasm_f32x4_const_splat(1.0f / 255.0f));
}

inline uint32_t _GGE_pack_epu32_rgba8_snorm(__f32x4 v)
{
	// Copy sign from x to 0.5
	__f32x4 vbias = wasm_v128_or(wasm_f32x4_const_splat(0.5f), wasm_v128_and(v, wasm_i32x4_const_splat(0x80000000u)));
	__f32x4 v127f = _GGE_madd_ps(v, wasm_f32x4_const_splat(127.0f), vbias);
	__i32x4 v127i = wasm_i32x4_trunc_sat_f32x4(v127f);
	return wasm_i8x16_shuffle(v127i, v127i, 0, 4, 8, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)[0];
}

inline __f32x4 _GGE_unpack_rgba8_snorm_epu32(uint32_t p)
{
	__i32x4 i = wasm_u32x4_splat(p);
	__f32x4 t = wasm_f32x4_convert_i32x4(wasm_i32x4_extend_low_i16x8(wasm_i16x8_extend_low_i8x16(i)));
	return wasm_f32x4_mul(t, wasm_f32x4_const_splat(1.0f / 127.0f));
}