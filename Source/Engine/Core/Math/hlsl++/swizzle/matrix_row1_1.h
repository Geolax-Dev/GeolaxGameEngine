#if GGE_ENABLE_MATRIX_SWIZZLE_M00

// -------------------------------
// _mNM
// -------------------------------

GGE_swizzle_start swizzle1<0> _m10; GGE_swizzle_end
GGE_swizzle_start swizzle2<0, 0> _m10_m10; GGE_swizzle_end
GGE_swizzle_start swizzle3<0, 0, 0> _m10_m10_m10; GGE_swizzle_end
GGE_swizzle_start swizzle4<0, 0, 0, 0> _m10_m10_m10_m10; GGE_swizzle_end

#endif

#if GGE_ENABLE_MATRIX_SWIZZLE_11

// -------------------------------
// _NM
// -------------------------------

GGE_swizzle_start swizzle1<0> _21; GGE_swizzle_end
GGE_swizzle_start swizzle2<0, 0> _21_21; GGE_swizzle_end
GGE_swizzle_start swizzle3<0, 0, 0> _21_21_21; GGE_swizzle_end
GGE_swizzle_start swizzle4<0, 0, 0, 0> _21_21_21_21; GGE_swizzle_end

#endif