#if GGE_ENABLE_MATRIX_SWIZZLE_M00

// -------------------------------
// _mNM
// -------------------------------

GGE_swizzle_start swizzle1<0> _m30; GGE_swizzle_end
GGE_swizzle_start swizzle2<0, 0> _m30_m30; GGE_swizzle_end
GGE_swizzle_start swizzle3<0, 0, 0> _m30_m30_m30; GGE_swizzle_end
GGE_swizzle_start swizzle4<0, 0, 0, 0> _m30_m30_m30_m30; GGE_swizzle_end

#endif

#if GGE_ENABLE_MATRIX_SWIZZLE_11

// -------------------------------
// _NM
// -------------------------------

GGE_swizzle_start swizzle1<0> _41; GGE_swizzle_end
GGE_swizzle_start swizzle2<0, 0> _41_41; GGE_swizzle_end
GGE_swizzle_start swizzle3<0, 0, 0> _41_41_41; GGE_swizzle_end
GGE_swizzle_start swizzle4<0, 0, 0, 0> _41_41_41_41; GGE_swizzle_end

#endif