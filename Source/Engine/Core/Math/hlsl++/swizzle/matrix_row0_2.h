#if GGE_ENABLE_MATRIX_SWIZZLE_M00

// -------------------------------
// _mNM
// -------------------------------

GGE_swizzle_start swizzle1<1> _m01; GGE_swizzle_end

GGE_swizzle_start swizzle2<0, 1> _m00_m01; GGE_swizzle_end
GGE_swizzle_start swizzle2<1, 0> _m01_m00; GGE_swizzle_end
GGE_swizzle_start swizzle2<1, 1> _m01_m01; GGE_swizzle_end

GGE_swizzle_start swizzle3<0, 0, 1> _m00_m00_m01; GGE_swizzle_end
GGE_swizzle_start swizzle3<0, 1, 0> _m00_m01_m00; GGE_swizzle_end
GGE_swizzle_start swizzle3<0, 1, 1> _m00_m01_m01; GGE_swizzle_end

GGE_swizzle_start swizzle3<1, 0, 0> _m01_m00_m00; GGE_swizzle_end
GGE_swizzle_start swizzle3<1, 0, 1> _m01_m00_m01; GGE_swizzle_end
GGE_swizzle_start swizzle3<1, 1, 0> _m01_m01_m00; GGE_swizzle_end
GGE_swizzle_start swizzle3<1, 1, 1> _m01_m01_m01; GGE_swizzle_end

GGE_swizzle_start swizzle4<0, 0, 0, 1> _m00_m00_m00_m01; GGE_swizzle_end

GGE_swizzle_start swizzle4<0, 0, 1, 0> _m00_m00_m01_m00; GGE_swizzle_end
GGE_swizzle_start swizzle4<0, 0, 1, 1> _m00_m00_m01_m01; GGE_swizzle_end

GGE_swizzle_start swizzle4<0, 1, 0, 0> _m00_m01_m00_m00; GGE_swizzle_end
GGE_swizzle_start swizzle4<0, 1, 0, 1> _m00_m01_m00_m01; GGE_swizzle_end

GGE_swizzle_start swizzle4<0, 1, 1, 0> _m00_m01_m01_m00; GGE_swizzle_end
GGE_swizzle_start swizzle4<0, 1, 1, 1> _m00_m01_m01_m01; GGE_swizzle_end

GGE_swizzle_start swizzle4<1, 0, 0, 0> _m01_m00_m00_m00; GGE_swizzle_end
GGE_swizzle_start swizzle4<1, 0, 0, 1> _m01_m00_m00_m01; GGE_swizzle_end

GGE_swizzle_start swizzle4<1, 0, 1, 0> _m01_m00_m01_m00; GGE_swizzle_end
GGE_swizzle_start swizzle4<1, 0, 1, 1> _m01_m00_m01_m01; GGE_swizzle_end

GGE_swizzle_start swizzle4<1, 1, 0, 0> _m01_m01_m00_m00; GGE_swizzle_end
GGE_swizzle_start swizzle4<1, 1, 0, 1> _m01_m01_m00_m01; GGE_swizzle_end

GGE_swizzle_start swizzle4<1, 1, 1, 0> _m01_m01_m01_m00; GGE_swizzle_end
GGE_swizzle_start swizzle4<1, 1, 1, 1> _m01_m01_m01_m01; GGE_swizzle_end

#endif

#if GGE_ENABLE_MATRIX_SWIZZLE_11

// -------------------------------
// _NM
// -------------------------------

GGE_swizzle_start swizzle1<1> _12; GGE_swizzle_end

GGE_swizzle_start swizzle2<0, 1> _11_12; GGE_swizzle_end
GGE_swizzle_start swizzle2<1, 0> _12_11; GGE_swizzle_end
GGE_swizzle_start swizzle2<1, 1> _12_12; GGE_swizzle_end

GGE_swizzle_start swizzle3<0, 0, 1> _11_11_12; GGE_swizzle_end
GGE_swizzle_start swizzle3<0, 1, 0> _11_12_11; GGE_swizzle_end
GGE_swizzle_start swizzle3<0, 1, 1> _11_12_12; GGE_swizzle_end

GGE_swizzle_start swizzle3<1, 0, 0> _12_11_11; GGE_swizzle_end
GGE_swizzle_start swizzle3<1, 0, 1> _12_11_12; GGE_swizzle_end
GGE_swizzle_start swizzle3<1, 1, 0> _12_12_11; GGE_swizzle_end
GGE_swizzle_start swizzle3<1, 1, 1> _12_12_12; GGE_swizzle_end

GGE_swizzle_start swizzle4<0, 0, 0, 1> _11_11_11_12; GGE_swizzle_end

GGE_swizzle_start swizzle4<0, 0, 1, 0> _11_11_12_11; GGE_swizzle_end
GGE_swizzle_start swizzle4<0, 0, 1, 1> _11_11_12_12; GGE_swizzle_end

GGE_swizzle_start swizzle4<0, 1, 0, 0> _11_12_11_11; GGE_swizzle_end
GGE_swizzle_start swizzle4<0, 1, 0, 1> _11_12_11_12; GGE_swizzle_end

GGE_swizzle_start swizzle4<0, 1, 1, 0> _11_12_12_11; GGE_swizzle_end
GGE_swizzle_start swizzle4<0, 1, 1, 1> _11_12_12_12; GGE_swizzle_end

GGE_swizzle_start swizzle4<1, 0, 0, 0> _12_11_11_11; GGE_swizzle_end
GGE_swizzle_start swizzle4<1, 0, 0, 1> _12_11_11_12; GGE_swizzle_end

GGE_swizzle_start swizzle4<1, 0, 1, 0> _12_11_12_11; GGE_swizzle_end
GGE_swizzle_start swizzle4<1, 0, 1, 1> _12_11_12_12; GGE_swizzle_end

GGE_swizzle_start swizzle4<1, 1, 0, 0> _12_12_11_11; GGE_swizzle_end
GGE_swizzle_start swizzle4<1, 1, 0, 1> _12_12_11_12; GGE_swizzle_end

GGE_swizzle_start swizzle4<1, 1, 1, 0> _12_12_12_11; GGE_swizzle_end
GGE_swizzle_start swizzle4<1, 1, 1, 1> _12_12_12_12; GGE_swizzle_end

#endif