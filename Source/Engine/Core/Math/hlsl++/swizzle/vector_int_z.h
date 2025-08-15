// -------------------------------
// XYZW
// -------------------------------

GGE_swizzle_start iswizzle1<2> z; GGE_swizzle_end

GGE_swizzle_start iswizzle2<0, 2> xz; GGE_swizzle_end
GGE_swizzle_start iswizzle2<1, 2> yz; GGE_swizzle_end
GGE_swizzle_start iswizzle2<2, 0> zx; GGE_swizzle_end
GGE_swizzle_start iswizzle2<2, 1> zy; GGE_swizzle_end
GGE_swizzle_start iswizzle2<2, 2> zz; GGE_swizzle_end

GGE_swizzle_start iswizzle3<0, 0, 2> xxz; GGE_swizzle_end
GGE_swizzle_start iswizzle3<0, 1, 2> xyz; GGE_swizzle_end
GGE_swizzle_start iswizzle3<0, 2, 0> xzx; GGE_swizzle_end
GGE_swizzle_start iswizzle3<0, 2, 1> xzy; GGE_swizzle_end
GGE_swizzle_start iswizzle3<0, 2, 2> xzz; GGE_swizzle_end

GGE_swizzle_start iswizzle3<1, 0, 2> yxz; GGE_swizzle_end
GGE_swizzle_start iswizzle3<1, 1, 2> yyz; GGE_swizzle_end
GGE_swizzle_start iswizzle3<1, 2, 0> yzx; GGE_swizzle_end
GGE_swizzle_start iswizzle3<1, 2, 1> yzy; GGE_swizzle_end
GGE_swizzle_start iswizzle3<1, 2, 2> yzz; GGE_swizzle_end

GGE_swizzle_start iswizzle3<2, 0, 0> zxx; GGE_swizzle_end
GGE_swizzle_start iswizzle3<2, 0, 1> zxy; GGE_swizzle_end
GGE_swizzle_start iswizzle3<2, 0, 2> zxz; GGE_swizzle_end
GGE_swizzle_start iswizzle3<2, 1, 0> zyx; GGE_swizzle_end
GGE_swizzle_start iswizzle3<2, 1, 1> zyy; GGE_swizzle_end
GGE_swizzle_start iswizzle3<2, 1, 2> zyz; GGE_swizzle_end

GGE_swizzle_start iswizzle3<2, 2, 0> zzx; GGE_swizzle_end
GGE_swizzle_start iswizzle3<2, 2, 1> zzy; GGE_swizzle_end
GGE_swizzle_start iswizzle3<2, 2, 2> zzz; GGE_swizzle_end

GGE_swizzle_start iswizzle4<0, 0, 0, 2> xxxz; GGE_swizzle_end
GGE_swizzle_start iswizzle4<0, 0, 1, 2> xxyz; GGE_swizzle_end

GGE_swizzle_start iswizzle4<0, 0, 2, 0> xxzx; GGE_swizzle_end
GGE_swizzle_start iswizzle4<0, 0, 2, 1> xxzy; GGE_swizzle_end
GGE_swizzle_start iswizzle4<0, 0, 2, 2> xxzz; GGE_swizzle_end

GGE_swizzle_start iswizzle4<0, 1, 0, 2> xyxz; GGE_swizzle_end
GGE_swizzle_start iswizzle4<0, 1, 1, 2> xyyz; GGE_swizzle_end

GGE_swizzle_start iswizzle4<0, 1, 2, 0> xyzx; GGE_swizzle_end
GGE_swizzle_start iswizzle4<0, 1, 2, 1> xyzy; GGE_swizzle_end
GGE_swizzle_start iswizzle4<0, 1, 2, 2> xyzz; GGE_swizzle_end

GGE_swizzle_start iswizzle4<0, 2, 0, 0> xzxx; GGE_swizzle_end
GGE_swizzle_start iswizzle4<0, 2, 0, 1> xzxy; GGE_swizzle_end
GGE_swizzle_start iswizzle4<0, 2, 0, 2> xzxz; GGE_swizzle_end

GGE_swizzle_start iswizzle4<0, 2, 1, 0> xzyx; GGE_swizzle_end
GGE_swizzle_start iswizzle4<0, 2, 1, 1> xzyy; GGE_swizzle_end
GGE_swizzle_start iswizzle4<0, 2, 1, 2> xzyz; GGE_swizzle_end

GGE_swizzle_start iswizzle4<0, 2, 2, 0> xzzx; GGE_swizzle_end
GGE_swizzle_start iswizzle4<0, 2, 2, 1> xzzy; GGE_swizzle_end
GGE_swizzle_start iswizzle4<0, 2, 2, 2> xzzz; GGE_swizzle_end

GGE_swizzle_start iswizzle4<1, 0, 0, 2> yxxz; GGE_swizzle_end
GGE_swizzle_start iswizzle4<1, 0, 1, 2> yxyz; GGE_swizzle_end
GGE_swizzle_start iswizzle4<1, 0, 2, 0> yxzx; GGE_swizzle_end
GGE_swizzle_start iswizzle4<1, 0, 2, 1> yxzy; GGE_swizzle_end
GGE_swizzle_start iswizzle4<1, 0, 2, 2> yxzz; GGE_swizzle_end

GGE_swizzle_start iswizzle4<1, 1, 0, 2> yyxz; GGE_swizzle_end
GGE_swizzle_start iswizzle4<1, 1, 1, 2> yyyz; GGE_swizzle_end

GGE_swizzle_start iswizzle4<1, 1, 2, 0> yyzx; GGE_swizzle_end
GGE_swizzle_start iswizzle4<1, 1, 2, 1> yyzy; GGE_swizzle_end
GGE_swizzle_start iswizzle4<1, 1, 2, 2> yyzz; GGE_swizzle_end

GGE_swizzle_start iswizzle4<1, 2, 0, 0> yzxx; GGE_swizzle_end
GGE_swizzle_start iswizzle4<1, 2, 0, 1> yzxy; GGE_swizzle_end
GGE_swizzle_start iswizzle4<1, 2, 0, 2> yzxz; GGE_swizzle_end

GGE_swizzle_start iswizzle4<1, 2, 1, 0> yzyx; GGE_swizzle_end
GGE_swizzle_start iswizzle4<1, 2, 1, 1> yzyy; GGE_swizzle_end
GGE_swizzle_start iswizzle4<1, 2, 1, 2> yzyz; GGE_swizzle_end

GGE_swizzle_start iswizzle4<1, 2, 2, 0> yzzx; GGE_swizzle_end
GGE_swizzle_start iswizzle4<1, 2, 2, 1> yzzy; GGE_swizzle_end
GGE_swizzle_start iswizzle4<1, 2, 2, 2> yzzz; GGE_swizzle_end

GGE_swizzle_start iswizzle4<2, 0, 0, 0> zxxx; GGE_swizzle_end
GGE_swizzle_start iswizzle4<2, 0, 0, 1> zxxy; GGE_swizzle_end
GGE_swizzle_start iswizzle4<2, 0, 0, 2> zxxz; GGE_swizzle_end

GGE_swizzle_start iswizzle4<2, 0, 1, 0> zxyx; GGE_swizzle_end
GGE_swizzle_start iswizzle4<2, 0, 1, 1> zxyy; GGE_swizzle_end
GGE_swizzle_start iswizzle4<2, 0, 1, 2> zxyz; GGE_swizzle_end

GGE_swizzle_start iswizzle4<2, 0, 2, 0> zxzx; GGE_swizzle_end
GGE_swizzle_start iswizzle4<2, 0, 2, 1> zxzy; GGE_swizzle_end
GGE_swizzle_start iswizzle4<2, 0, 2, 2> zxzz; GGE_swizzle_end

GGE_swizzle_start iswizzle4<2, 1, 0, 0> zyxx; GGE_swizzle_end
GGE_swizzle_start iswizzle4<2, 1, 0, 1> zyxy; GGE_swizzle_end
GGE_swizzle_start iswizzle4<2, 1, 0, 2> zyxz; GGE_swizzle_end

GGE_swizzle_start iswizzle4<2, 1, 1, 0> zyyx; GGE_swizzle_end
GGE_swizzle_start iswizzle4<2, 1, 1, 1> zyyy; GGE_swizzle_end
GGE_swizzle_start iswizzle4<2, 1, 1, 2> zyyz; GGE_swizzle_end

GGE_swizzle_start iswizzle4<2, 1, 2, 0> zyzx; GGE_swizzle_end
GGE_swizzle_start iswizzle4<2, 1, 2, 1> zyzy; GGE_swizzle_end
GGE_swizzle_start iswizzle4<2, 1, 2, 2> zyzz; GGE_swizzle_end

GGE_swizzle_start iswizzle4<2, 2, 0, 0> zzxx; GGE_swizzle_end
GGE_swizzle_start iswizzle4<2, 2, 0, 1> zzxy; GGE_swizzle_end
GGE_swizzle_start iswizzle4<2, 2, 0, 2> zzxz; GGE_swizzle_end

GGE_swizzle_start iswizzle4<2, 2, 1, 0> zzyx; GGE_swizzle_end
GGE_swizzle_start iswizzle4<2, 2, 1, 1> zzyy; GGE_swizzle_end
GGE_swizzle_start iswizzle4<2, 2, 1, 2> zzyz; GGE_swizzle_end

GGE_swizzle_start iswizzle4<2, 2, 2, 0> zzzx; GGE_swizzle_end
GGE_swizzle_start iswizzle4<2, 2, 2, 1> zzzy; GGE_swizzle_end
GGE_swizzle_start iswizzle4<2, 2, 2, 2> zzzz; GGE_swizzle_end

// -------------------------------
// RGBA
// -------------------------------

GGE_swizzle_start iswizzle1<2> b; GGE_swizzle_end

GGE_swizzle_start iswizzle2<0, 2> rb; GGE_swizzle_end
GGE_swizzle_start iswizzle2<1, 2> gb; GGE_swizzle_end
GGE_swizzle_start iswizzle2<2, 0> br; GGE_swizzle_end
GGE_swizzle_start iswizzle2<2, 1> bg; GGE_swizzle_end
GGE_swizzle_start iswizzle2<2, 2> bb; GGE_swizzle_end

GGE_swizzle_start iswizzle3<0, 0, 2> rrb; GGE_swizzle_end
GGE_swizzle_start iswizzle3<0, 1, 2> rgb; GGE_swizzle_end
GGE_swizzle_start iswizzle3<0, 2, 0> rbr; GGE_swizzle_end
GGE_swizzle_start iswizzle3<0, 2, 1> rbg; GGE_swizzle_end
GGE_swizzle_start iswizzle3<0, 2, 2> rbb; GGE_swizzle_end

GGE_swizzle_start iswizzle3<1, 0, 2> grb; GGE_swizzle_end
GGE_swizzle_start iswizzle3<1, 1, 2> ggb; GGE_swizzle_end
GGE_swizzle_start iswizzle3<1, 2, 0> gbr; GGE_swizzle_end
GGE_swizzle_start iswizzle3<1, 2, 1> gbg; GGE_swizzle_end
GGE_swizzle_start iswizzle3<1, 2, 2> gbb; GGE_swizzle_end

GGE_swizzle_start iswizzle3<2, 0, 0> brr; GGE_swizzle_end
GGE_swizzle_start iswizzle3<2, 0, 1> brg; GGE_swizzle_end
GGE_swizzle_start iswizzle3<2, 0, 2> brb; GGE_swizzle_end
GGE_swizzle_start iswizzle3<2, 1, 0> bgr; GGE_swizzle_end
GGE_swizzle_start iswizzle3<2, 1, 1> bgg; GGE_swizzle_end
GGE_swizzle_start iswizzle3<2, 1, 2> bgb; GGE_swizzle_end

GGE_swizzle_start iswizzle3<2, 2, 0> bbr; GGE_swizzle_end
GGE_swizzle_start iswizzle3<2, 2, 1> bbg; GGE_swizzle_end
GGE_swizzle_start iswizzle3<2, 2, 2> bbb; GGE_swizzle_end

GGE_swizzle_start iswizzle4<0, 0, 0, 2> rrrb; GGE_swizzle_end
GGE_swizzle_start iswizzle4<0, 0, 1, 2> rrgb; GGE_swizzle_end

GGE_swizzle_start iswizzle4<0, 0, 2, 0> rrbr; GGE_swizzle_end
GGE_swizzle_start iswizzle4<0, 0, 2, 1> rrbg; GGE_swizzle_end
GGE_swizzle_start iswizzle4<0, 0, 2, 2> rrbb; GGE_swizzle_end

GGE_swizzle_start iswizzle4<0, 1, 0, 2> rgrb; GGE_swizzle_end
GGE_swizzle_start iswizzle4<0, 1, 1, 2> rggb; GGE_swizzle_end

GGE_swizzle_start iswizzle4<0, 1, 2, 0> rgbr; GGE_swizzle_end
GGE_swizzle_start iswizzle4<0, 1, 2, 1> rgbg; GGE_swizzle_end
GGE_swizzle_start iswizzle4<0, 1, 2, 2> rgbb; GGE_swizzle_end

GGE_swizzle_start iswizzle4<0, 2, 0, 0> rbrr; GGE_swizzle_end
GGE_swizzle_start iswizzle4<0, 2, 0, 1> rbrg; GGE_swizzle_end
GGE_swizzle_start iswizzle4<0, 2, 0, 2> rbrb; GGE_swizzle_end

GGE_swizzle_start iswizzle4<0, 2, 1, 0> rbgr; GGE_swizzle_end
GGE_swizzle_start iswizzle4<0, 2, 1, 1> rbgg; GGE_swizzle_end
GGE_swizzle_start iswizzle4<0, 2, 1, 2> rbgb; GGE_swizzle_end

GGE_swizzle_start iswizzle4<0, 2, 2, 0> rbbr; GGE_swizzle_end
GGE_swizzle_start iswizzle4<0, 2, 2, 1> rbbg; GGE_swizzle_end
GGE_swizzle_start iswizzle4<0, 2, 2, 2> rbbb; GGE_swizzle_end

GGE_swizzle_start iswizzle4<1, 0, 0, 2> grrb; GGE_swizzle_end
GGE_swizzle_start iswizzle4<1, 0, 1, 2> grgb; GGE_swizzle_end
GGE_swizzle_start iswizzle4<1, 0, 2, 0> grbr; GGE_swizzle_end
GGE_swizzle_start iswizzle4<1, 0, 2, 1> grbg; GGE_swizzle_end
GGE_swizzle_start iswizzle4<1, 0, 2, 2> grbb; GGE_swizzle_end

GGE_swizzle_start iswizzle4<1, 1, 0, 2> ggrb; GGE_swizzle_end
GGE_swizzle_start iswizzle4<1, 1, 1, 2> gggb; GGE_swizzle_end

GGE_swizzle_start iswizzle4<1, 1, 2, 0> ggbr; GGE_swizzle_end
GGE_swizzle_start iswizzle4<1, 1, 2, 1> ggbg; GGE_swizzle_end
GGE_swizzle_start iswizzle4<1, 1, 2, 2> ggbb; GGE_swizzle_end

GGE_swizzle_start iswizzle4<1, 2, 0, 0> gbrr; GGE_swizzle_end
GGE_swizzle_start iswizzle4<1, 2, 0, 1> gbrg; GGE_swizzle_end
GGE_swizzle_start iswizzle4<1, 2, 0, 2> gbrb; GGE_swizzle_end

GGE_swizzle_start iswizzle4<1, 2, 1, 0> gbgr; GGE_swizzle_end
GGE_swizzle_start iswizzle4<1, 2, 1, 1> gbgg; GGE_swizzle_end
GGE_swizzle_start iswizzle4<1, 2, 1, 2> gbgb; GGE_swizzle_end

GGE_swizzle_start iswizzle4<1, 2, 2, 0> gbbr; GGE_swizzle_end
GGE_swizzle_start iswizzle4<1, 2, 2, 1> gbbg; GGE_swizzle_end
GGE_swizzle_start iswizzle4<1, 2, 2, 2> gbbb; GGE_swizzle_end

GGE_swizzle_start iswizzle4<2, 0, 0, 0> brrr; GGE_swizzle_end
GGE_swizzle_start iswizzle4<2, 0, 0, 1> brrg; GGE_swizzle_end
GGE_swizzle_start iswizzle4<2, 0, 0, 2> brrb; GGE_swizzle_end

GGE_swizzle_start iswizzle4<2, 0, 1, 0> brgr; GGE_swizzle_end
GGE_swizzle_start iswizzle4<2, 0, 1, 1> brgg; GGE_swizzle_end
GGE_swizzle_start iswizzle4<2, 0, 1, 2> brgb; GGE_swizzle_end

GGE_swizzle_start iswizzle4<2, 0, 2, 0> brbr; GGE_swizzle_end
GGE_swizzle_start iswizzle4<2, 0, 2, 1> brbg; GGE_swizzle_end
GGE_swizzle_start iswizzle4<2, 0, 2, 2> brbb; GGE_swizzle_end

GGE_swizzle_start iswizzle4<2, 1, 0, 0> bgrr; GGE_swizzle_end
GGE_swizzle_start iswizzle4<2, 1, 0, 1> bgrg; GGE_swizzle_end
GGE_swizzle_start iswizzle4<2, 1, 0, 2> bgrb; GGE_swizzle_end

GGE_swizzle_start iswizzle4<2, 1, 1, 0> bggr; GGE_swizzle_end
GGE_swizzle_start iswizzle4<2, 1, 1, 1> bggg; GGE_swizzle_end
GGE_swizzle_start iswizzle4<2, 1, 1, 2> bggb; GGE_swizzle_end

GGE_swizzle_start iswizzle4<2, 1, 2, 0> bgbr; GGE_swizzle_end
GGE_swizzle_start iswizzle4<2, 1, 2, 1> bgbg; GGE_swizzle_end
GGE_swizzle_start iswizzle4<2, 1, 2, 2> bgbb; GGE_swizzle_end

GGE_swizzle_start iswizzle4<2, 2, 0, 0> bbrr; GGE_swizzle_end
GGE_swizzle_start iswizzle4<2, 2, 0, 1> bbrg; GGE_swizzle_end
GGE_swizzle_start iswizzle4<2, 2, 0, 2> bbrb; GGE_swizzle_end

GGE_swizzle_start iswizzle4<2, 2, 1, 0> bbgr; GGE_swizzle_end
GGE_swizzle_start iswizzle4<2, 2, 1, 1> bbgg; GGE_swizzle_end
GGE_swizzle_start iswizzle4<2, 2, 1, 2> bbgb; GGE_swizzle_end

GGE_swizzle_start iswizzle4<2, 2, 2, 0> bbbr; GGE_swizzle_end
GGE_swizzle_start iswizzle4<2, 2, 2, 1> bbbg; GGE_swizzle_end
GGE_swizzle_start iswizzle4<2, 2, 2, 2> bbbb; GGE_swizzle_end