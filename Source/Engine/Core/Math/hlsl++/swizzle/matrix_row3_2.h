#if GGE_ENABLE_MATRIX_SWIZZLE_M00

// -------------------------------
// _mNM
// -------------------------------

GGE_swizzle_start swizzle1<1> _m31; GGE_swizzle_end

GGE_swizzle_start swizzle2<0, 1> _m30_m31; GGE_swizzle_end
GGE_swizzle_start swizzle2<1, 0> _m31_m30; GGE_swizzle_end
GGE_swizzle_start swizzle2<1, 1> _m31_m31; GGE_swizzle_end

GGE_swizzle_start swizzle3<0, 0, 1> _m30_m30_m31; GGE_swizzle_end
GGE_swizzle_start swizzle3<0, 1, 0> _m30_m31_m30; GGE_swizzle_end
GGE_swizzle_start swizzle3<0, 1, 1> _m30_m31_m31; GGE_swizzle_end

GGE_swizzle_start swizzle3<1, 0, 0> _m31_m30_m30; GGE_swizzle_end
GGE_swizzle_start swizzle3<1, 0, 1> _m31_m30_m31; GGE_swizzle_end
GGE_swizzle_start swizzle3<1, 1, 0> _m31_m31_m30; GGE_swizzle_end
GGE_swizzle_start swizzle3<1, 1, 1> _m31_m31_m31; GGE_swizzle_end

GGE_swizzle_start swizzle4<0, 0, 0, 1> _m30_m30_m30_m31; GGE_swizzle_end

GGE_swizzle_start swizzle4<0, 0, 1, 0> _m30_m30_m31_m30; GGE_swizzle_end
GGE_swizzle_start swizzle4<0, 0, 1, 1> _m30_m30_m31_m31; GGE_swizzle_end

GGE_swizzle_start swizzle4<0, 1, 0, 0> _m30_m31_m30_m30; GGE_swizzle_end
GGE_swizzle_start swizzle4<0, 1, 0, 1> _m30_m31_m30_m31; GGE_swizzle_end

GGE_swizzle_start swizzle4<0, 1, 1, 0> _m30_m31_m31_m30; GGE_swizzle_end
GGE_swizzle_start swizzle4<0, 1, 1, 1> _m30_m31_m31_m31; GGE_swizzle_end

GGE_swizzle_start swizzle4<1, 0, 0, 0> _m31_m30_m30_m30; GGE_swizzle_end
GGE_swizzle_start swizzle4<1, 0, 0, 1> _m31_m30_m30_m31; GGE_swizzle_end

GGE_swizzle_start swizzle4<1, 0, 1, 0> _m31_m30_m31_m30; GGE_swizzle_end
GGE_swizzle_start swizzle4<1, 0, 1, 1> _m31_m30_m31_m31; GGE_swizzle_end

GGE_swizzle_start swizzle4<1, 1, 0, 0> _m31_m31_m30_m30; GGE_swizzle_end
GGE_swizzle_start swizzle4<1, 1, 0, 1> _m31_m31_m30_m31; GGE_swizzle_end

GGE_swizzle_start swizzle4<1, 1, 1, 0> _m31_m31_m31_m30; GGE_swizzle_end
GGE_swizzle_start swizzle4<1, 1, 1, 1> _m31_m31_m31_m31; GGE_swizzle_end

#endif

#if GGE_ENABLE_MATRIX_SWIZZLE_11

// -------------------------------
// _NM
// -------------------------------

GGE_swizzle_start swizzle1<1> _42; GGE_swizzle_end

GGE_swizzle_start swizzle2<0, 1> _41_42; GGE_swizzle_end
GGE_swizzle_start swizzle2<1, 0> _42_41; GGE_swizzle_end
GGE_swizzle_start swizzle2<1, 1> _42_42; GGE_swizzle_end

GGE_swizzle_start swizzle3<0, 0, 1> _41_41_42; GGE_swizzle_end
GGE_swizzle_start swizzle3<0, 1, 0> _41_42_41; GGE_swizzle_end
GGE_swizzle_start swizzle3<0, 1, 1> _41_42_42; GGE_swizzle_end

GGE_swizzle_start swizzle3<1, 0, 0> _42_41_41; GGE_swizzle_end
GGE_swizzle_start swizzle3<1, 0, 1> _42_41_42; GGE_swizzle_end
GGE_swizzle_start swizzle3<1, 1, 0> _42_42_41; GGE_swizzle_end
GGE_swizzle_start swizzle3<1, 1, 1> _42_42_42; GGE_swizzle_end

GGE_swizzle_start swizzle4<0, 0, 0, 1> _41_41_41_42; GGE_swizzle_end

GGE_swizzle_start swizzle4<0, 0, 1, 0> _41_41_42_41; GGE_swizzle_end
GGE_swizzle_start swizzle4<0, 0, 1, 1> _41_41_42_42; GGE_swizzle_end

GGE_swizzle_start swizzle4<0, 1, 0, 0> _41_42_41_41; GGE_swizzle_end
GGE_swizzle_start swizzle4<0, 1, 0, 1> _41_42_41_42; GGE_swizzle_end

GGE_swizzle_start swizzle4<0, 1, 1, 0> _41_42_42_41; GGE_swizzle_end
GGE_swizzle_start swizzle4<0, 1, 1, 1> _41_42_42_42; GGE_swizzle_end

GGE_swizzle_start swizzle4<1, 0, 0, 0> _42_41_41_41; GGE_swizzle_end
GGE_swizzle_start swizzle4<1, 0, 0, 1> _42_41_41_42; GGE_swizzle_end

GGE_swizzle_start swizzle4<1, 0, 1, 0> _42_41_42_41; GGE_swizzle_end
GGE_swizzle_start swizzle4<1, 0, 1, 1> _42_41_42_42; GGE_swizzle_end

GGE_swizzle_start swizzle4<1, 1, 0, 0> _42_42_41_41; GGE_swizzle_end
GGE_swizzle_start swizzle4<1, 1, 0, 1> _42_42_41_42; GGE_swizzle_end

GGE_swizzle_start swizzle4<1, 1, 1, 0> _42_42_42_41; GGE_swizzle_end
GGE_swizzle_start swizzle4<1, 1, 1, 1> _42_42_42_42; GGE_swizzle_end

#endif