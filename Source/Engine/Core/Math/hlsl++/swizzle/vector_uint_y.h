// -------------------------------
// XYZW
// -------------------------------

GGE_swizzle_start uswizzle1<1> y; GGE_swizzle_end

GGE_swizzle_start uswizzle2<0, 1> xy; GGE_swizzle_end
GGE_swizzle_start uswizzle2<1, 0> yx; GGE_swizzle_end
GGE_swizzle_start uswizzle2<1, 1> yy; GGE_swizzle_end

GGE_swizzle_start uswizzle3<0, 0, 1> xxy; GGE_swizzle_end
GGE_swizzle_start uswizzle3<0, 1, 0> xyx; GGE_swizzle_end
GGE_swizzle_start uswizzle3<0, 1, 1> xyy; GGE_swizzle_end

GGE_swizzle_start uswizzle3<1, 0, 0> yxx; GGE_swizzle_end
GGE_swizzle_start uswizzle3<1, 0, 1> yxy; GGE_swizzle_end
GGE_swizzle_start uswizzle3<1, 1, 0> yyx; GGE_swizzle_end
GGE_swizzle_start uswizzle3<1, 1, 1> yyy; GGE_swizzle_end

GGE_swizzle_start uswizzle4<0, 0, 0, 1> xxxy; GGE_swizzle_end

GGE_swizzle_start uswizzle4<0, 0, 1, 0> xxyx; GGE_swizzle_end
GGE_swizzle_start uswizzle4<0, 0, 1, 1> xxyy; GGE_swizzle_end

GGE_swizzle_start uswizzle4<0, 1, 0, 0> xyxx; GGE_swizzle_end
GGE_swizzle_start uswizzle4<0, 1, 0, 1> xyxy; GGE_swizzle_end

GGE_swizzle_start uswizzle4<0, 1, 1, 0> xyyx; GGE_swizzle_end
GGE_swizzle_start uswizzle4<0, 1, 1, 1> xyyy; GGE_swizzle_end

GGE_swizzle_start uswizzle4<1, 0, 0, 0> yxxx; GGE_swizzle_end
GGE_swizzle_start uswizzle4<1, 0, 0, 1> yxxy; GGE_swizzle_end

GGE_swizzle_start uswizzle4<1, 0, 1, 0> yxyx; GGE_swizzle_end
GGE_swizzle_start uswizzle4<1, 0, 1, 1> yxyy; GGE_swizzle_end

GGE_swizzle_start uswizzle4<1, 1, 0, 0> yyxx; GGE_swizzle_end
GGE_swizzle_start uswizzle4<1, 1, 0, 1> yyxy; GGE_swizzle_end

GGE_swizzle_start uswizzle4<1, 1, 1, 0> yyyx; GGE_swizzle_end
GGE_swizzle_start uswizzle4<1, 1, 1, 1> yyyy; GGE_swizzle_end

// -------------------------------
// RGBA
// -------------------------------

GGE_swizzle_start uswizzle1<1> g; GGE_swizzle_end

GGE_swizzle_start uswizzle2<0, 1> rg; GGE_swizzle_end
GGE_swizzle_start uswizzle2<1, 0> gr; GGE_swizzle_end
GGE_swizzle_start uswizzle2<1, 1> gg; GGE_swizzle_end

GGE_swizzle_start uswizzle3<0, 0, 1> rrg; GGE_swizzle_end
GGE_swizzle_start uswizzle3<0, 1, 0> rgr; GGE_swizzle_end
GGE_swizzle_start uswizzle3<0, 1, 1> rgg; GGE_swizzle_end

GGE_swizzle_start uswizzle3<1, 0, 0> grr; GGE_swizzle_end
GGE_swizzle_start uswizzle3<1, 0, 1> grg; GGE_swizzle_end
GGE_swizzle_start uswizzle3<1, 1, 0> ggr; GGE_swizzle_end
GGE_swizzle_start uswizzle3<1, 1, 1> ggg; GGE_swizzle_end

GGE_swizzle_start uswizzle4<0, 0, 0, 1> rrrg; GGE_swizzle_end

GGE_swizzle_start uswizzle4<0, 0, 1, 0> rrgr; GGE_swizzle_end
GGE_swizzle_start uswizzle4<0, 0, 1, 1> rrgg; GGE_swizzle_end

GGE_swizzle_start uswizzle4<0, 1, 0, 0> rgrr; GGE_swizzle_end
GGE_swizzle_start uswizzle4<0, 1, 0, 1> rgrg; GGE_swizzle_end

GGE_swizzle_start uswizzle4<0, 1, 1, 0> rggr; GGE_swizzle_end
GGE_swizzle_start uswizzle4<0, 1, 1, 1> rggg; GGE_swizzle_end

GGE_swizzle_start uswizzle4<1, 0, 0, 0> grrr; GGE_swizzle_end
GGE_swizzle_start uswizzle4<1, 0, 0, 1> grrg; GGE_swizzle_end

GGE_swizzle_start uswizzle4<1, 0, 1, 0> grgr; GGE_swizzle_end
GGE_swizzle_start uswizzle4<1, 0, 1, 1> grgg; GGE_swizzle_end

GGE_swizzle_start uswizzle4<1, 1, 0, 0> ggrr; GGE_swizzle_end
GGE_swizzle_start uswizzle4<1, 1, 0, 1> ggrg; GGE_swizzle_end

GGE_swizzle_start uswizzle4<1, 1, 1, 0> gggr; GGE_swizzle_end
GGE_swizzle_start uswizzle4<1, 1, 1, 1> gggg; GGE_swizzle_end