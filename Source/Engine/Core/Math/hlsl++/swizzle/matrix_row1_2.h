#if GGE_ENABLE_MATRIX_SWIZZLE_M00

// -------------------------------
// _mNM
// -------------------------------

GGE_swizzle_start swizzle1<1> _m11; GGE_swizzle_end

GGE_swizzle_start swizzle2<0, 1> _m10_m11; GGE_swizzle_end
GGE_swizzle_start swizzle2<1, 0> _m11_m10; GGE_swizzle_end
GGE_swizzle_start swizzle2<1, 1> _m11_m11; GGE_swizzle_end

GGE_swizzle_start swizzle3<0, 0, 1> _m10_m10_m11; GGE_swizzle_end
GGE_swizzle_start swizzle3<0, 1, 0> _m10_m11_m10; GGE_swizzle_end
GGE_swizzle_start swizzle3<0, 1, 1> _m10_m11_m11; GGE_swizzle_end

GGE_swizzle_start swizzle3<1, 0, 0> _m11_m10_m10; GGE_swizzle_end
GGE_swizzle_start swizzle3<1, 0, 1> _m11_m10_m11; GGE_swizzle_end
GGE_swizzle_start swizzle3<1, 1, 0> _m11_m11_m10; GGE_swizzle_end
GGE_swizzle_start swizzle3<1, 1, 1> _m11_m11_m11; GGE_swizzle_end

GGE_swizzle_start swizzle4<0, 0, 0, 1> _m10_m10_m10_m11; GGE_swizzle_end

GGE_swizzle_start swizzle4<0, 0, 1, 0> _m10_m10_m11_m10; GGE_swizzle_end
GGE_swizzle_start swizzle4<0, 0, 1, 1> _m10_m10_m11_m11; GGE_swizzle_end

GGE_swizzle_start swizzle4<0, 1, 0, 0> _m10_m11_m10_m10; GGE_swizzle_end
GGE_swizzle_start swizzle4<0, 1, 0, 1> _m10_m11_m10_m11; GGE_swizzle_end

GGE_swizzle_start swizzle4<0, 1, 1, 0> _m10_m11_m11_m10; GGE_swizzle_end
GGE_swizzle_start swizzle4<0, 1, 1, 1> _m10_m11_m11_m11; GGE_swizzle_end

GGE_swizzle_start swizzle4<1, 0, 0, 0> _m11_m10_m10_m10; GGE_swizzle_end
GGE_swizzle_start swizzle4<1, 0, 0, 1> _m11_m10_m10_m11; GGE_swizzle_end

GGE_swizzle_start swizzle4<1, 0, 1, 0> _m11_m10_m11_m10; GGE_swizzle_end
GGE_swizzle_start swizzle4<1, 0, 1, 1> _m11_m10_m11_m11; GGE_swizzle_end

GGE_swizzle_start swizzle4<1, 1, 0, 0> _m11_m11_m10_m10; GGE_swizzle_end
GGE_swizzle_start swizzle4<1, 1, 0, 1> _m11_m11_m10_m11; GGE_swizzle_end

GGE_swizzle_start swizzle4<1, 1, 1, 0> _m11_m11_m11_m10; GGE_swizzle_end
GGE_swizzle_start swizzle4<1, 1, 1, 1> _m11_m11_m11_m11; GGE_swizzle_end

#endif

#if GGE_ENABLE_MATRIX_SWIZZLE_11

// -------------------------------
// _NM
// -------------------------------

GGE_swizzle_start swizzle1<1> _22; GGE_swizzle_end

GGE_swizzle_start swizzle2<0, 1> _21_22; GGE_swizzle_end
GGE_swizzle_start swizzle2<1, 0> _22_21; GGE_swizzle_end
GGE_swizzle_start swizzle2<1, 1> _22_22; GGE_swizzle_end

GGE_swizzle_start swizzle3<0, 0, 1> _21_21_22; GGE_swizzle_end
GGE_swizzle_start swizzle3<0, 1, 0> _21_22_21; GGE_swizzle_end
GGE_swizzle_start swizzle3<0, 1, 1> _21_22_22; GGE_swizzle_end

GGE_swizzle_start swizzle3<1, 0, 0> _22_21_21; GGE_swizzle_end
GGE_swizzle_start swizzle3<1, 0, 1> _22_21_22; GGE_swizzle_end
GGE_swizzle_start swizzle3<1, 1, 0> _22_22_21; GGE_swizzle_end
GGE_swizzle_start swizzle3<1, 1, 1> _22_22_22; GGE_swizzle_end

GGE_swizzle_start swizzle4<0, 0, 0, 1> _21_21_21_22; GGE_swizzle_end

GGE_swizzle_start swizzle4<0, 0, 1, 0> _21_21_22_21; GGE_swizzle_end
GGE_swizzle_start swizzle4<0, 0, 1, 1> _21_21_22_22; GGE_swizzle_end

GGE_swizzle_start swizzle4<0, 1, 0, 0> _21_22_21_21; GGE_swizzle_end
GGE_swizzle_start swizzle4<0, 1, 0, 1> _21_22_21_22; GGE_swizzle_end

GGE_swizzle_start swizzle4<0, 1, 1, 0> _21_22_22_21; GGE_swizzle_end
GGE_swizzle_start swizzle4<0, 1, 1, 1> _21_22_22_22; GGE_swizzle_end

GGE_swizzle_start swizzle4<1, 0, 0, 0> _22_21_21_21; GGE_swizzle_end
GGE_swizzle_start swizzle4<1, 0, 0, 1> _22_21_21_22; GGE_swizzle_end

GGE_swizzle_start swizzle4<1, 0, 1, 0> _22_21_22_21; GGE_swizzle_end
GGE_swizzle_start swizzle4<1, 0, 1, 1> _22_21_22_22; GGE_swizzle_end

GGE_swizzle_start swizzle4<1, 1, 0, 0> _22_22_21_21; GGE_swizzle_end
GGE_swizzle_start swizzle4<1, 1, 0, 1> _22_22_21_22; GGE_swizzle_end

GGE_swizzle_start swizzle4<1, 1, 1, 0> _22_22_22_21; GGE_swizzle_end
GGE_swizzle_start swizzle4<1, 1, 1, 1> _22_22_22_22; GGE_swizzle_end

#endif