#if GGE_ENABLE_MATRIX_SWIZZLE_M00

// -------------------------------
// _mNM
// -------------------------------

GGE_swizzle_start swizzle1<1> _m21; GGE_swizzle_end

GGE_swizzle_start swizzle2<0, 1> _m20_m21; GGE_swizzle_end
GGE_swizzle_start swizzle2<1, 0> _m21_m20; GGE_swizzle_end
GGE_swizzle_start swizzle2<1, 1> _m21_m21; GGE_swizzle_end

GGE_swizzle_start swizzle3<0, 0, 1> _m20_m20_m21; GGE_swizzle_end
GGE_swizzle_start swizzle3<0, 1, 0> _m20_m21_m20; GGE_swizzle_end
GGE_swizzle_start swizzle3<0, 1, 1> _m20_m21_m21; GGE_swizzle_end

GGE_swizzle_start swizzle3<1, 0, 0> _m21_m20_m20; GGE_swizzle_end
GGE_swizzle_start swizzle3<1, 0, 1> _m21_m20_m21; GGE_swizzle_end
GGE_swizzle_start swizzle3<1, 1, 0> _m21_m21_m20; GGE_swizzle_end
GGE_swizzle_start swizzle3<1, 1, 1> _m21_m21_m21; GGE_swizzle_end

GGE_swizzle_start swizzle4<0, 0, 0, 1> _m20_m20_m20_m21; GGE_swizzle_end

GGE_swizzle_start swizzle4<0, 0, 1, 0> _m20_m20_m21_m20; GGE_swizzle_end
GGE_swizzle_start swizzle4<0, 0, 1, 1> _m20_m20_m21_m21; GGE_swizzle_end

GGE_swizzle_start swizzle4<0, 1, 0, 0> _m20_m21_m20_m20; GGE_swizzle_end
GGE_swizzle_start swizzle4<0, 1, 0, 1> _m20_m21_m20_m21; GGE_swizzle_end

GGE_swizzle_start swizzle4<0, 1, 1, 0> _m20_m21_m21_m20; GGE_swizzle_end
GGE_swizzle_start swizzle4<0, 1, 1, 1> _m20_m21_m21_m21; GGE_swizzle_end

GGE_swizzle_start swizzle4<1, 0, 0, 0> _m21_m20_m20_m20; GGE_swizzle_end
GGE_swizzle_start swizzle4<1, 0, 0, 1> _m21_m20_m20_m21; GGE_swizzle_end

GGE_swizzle_start swizzle4<1, 0, 1, 0> _m21_m20_m21_m20; GGE_swizzle_end
GGE_swizzle_start swizzle4<1, 0, 1, 1> _m21_m20_m21_m21; GGE_swizzle_end

GGE_swizzle_start swizzle4<1, 1, 0, 0> _m21_m21_m20_m20; GGE_swizzle_end
GGE_swizzle_start swizzle4<1, 1, 0, 1> _m21_m21_m20_m21; GGE_swizzle_end

GGE_swizzle_start swizzle4<1, 1, 1, 0> _m21_m21_m21_m20; GGE_swizzle_end
GGE_swizzle_start swizzle4<1, 1, 1, 1> _m21_m21_m21_m21; GGE_swizzle_end

#endif

#if GGE_ENABLE_MATRIX_SWIZZLE_11

// -------------------------------
// _NM
// -------------------------------

GGE_swizzle_start swizzle1<1> _32; GGE_swizzle_end

GGE_swizzle_start swizzle2<0, 1> _31_32; GGE_swizzle_end
GGE_swizzle_start swizzle2<1, 0> _32_31; GGE_swizzle_end
GGE_swizzle_start swizzle2<1, 1> _32_32; GGE_swizzle_end

GGE_swizzle_start swizzle3<0, 0, 1> _31_31_32; GGE_swizzle_end
GGE_swizzle_start swizzle3<0, 1, 0> _31_32_31; GGE_swizzle_end
GGE_swizzle_start swizzle3<0, 1, 1> _31_32_32; GGE_swizzle_end

GGE_swizzle_start swizzle3<1, 0, 0> _32_31_31; GGE_swizzle_end
GGE_swizzle_start swizzle3<1, 0, 1> _32_31_32; GGE_swizzle_end
GGE_swizzle_start swizzle3<1, 1, 0> _32_32_31; GGE_swizzle_end
GGE_swizzle_start swizzle3<1, 1, 1> _32_32_32; GGE_swizzle_end

GGE_swizzle_start swizzle4<0, 0, 0, 1> _31_31_31_32; GGE_swizzle_end

GGE_swizzle_start swizzle4<0, 0, 1, 0> _31_31_32_31; GGE_swizzle_end
GGE_swizzle_start swizzle4<0, 0, 1, 1> _31_31_32_32; GGE_swizzle_end

GGE_swizzle_start swizzle4<0, 1, 0, 0> _31_32_31_31; GGE_swizzle_end
GGE_swizzle_start swizzle4<0, 1, 0, 1> _31_32_31_32; GGE_swizzle_end

GGE_swizzle_start swizzle4<0, 1, 1, 0> _31_32_32_31; GGE_swizzle_end
GGE_swizzle_start swizzle4<0, 1, 1, 1> _31_32_32_32; GGE_swizzle_end

GGE_swizzle_start swizzle4<1, 0, 0, 0> _32_31_31_31; GGE_swizzle_end
GGE_swizzle_start swizzle4<1, 0, 0, 1> _32_31_31_32; GGE_swizzle_end

GGE_swizzle_start swizzle4<1, 0, 1, 0> _32_31_32_31; GGE_swizzle_end
GGE_swizzle_start swizzle4<1, 0, 1, 1> _32_31_32_32; GGE_swizzle_end

GGE_swizzle_start swizzle4<1, 1, 0, 0> _32_32_31_31; GGE_swizzle_end
GGE_swizzle_start swizzle4<1, 1, 0, 1> _32_32_31_32; GGE_swizzle_end

GGE_swizzle_start swizzle4<1, 1, 1, 0> _32_32_32_31; GGE_swizzle_end
GGE_swizzle_start swizzle4<1, 1, 1, 1> _32_32_32_32; GGE_swizzle_end

#endif