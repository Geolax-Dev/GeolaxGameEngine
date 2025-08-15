#pragma once

#include <Core/Math/hlsl++/common.h>

#if defined(GGE_DOUBLE)

GGE_WARNING_IMPLICIT_CONSTRUCTOR_BEGIN

GGE_module_export namespace GGE
{
	template<int X>
	struct GGE_nodiscard dswizzle1
	{
		template<int A> friend struct dswizzle1;

		GGE_inline operator double() const { return f64[X]; }

		// Return the address of this double in the same way we return the value
		GGE_inline double* operator&() { return &f64[X]; }

		template<int E, int A>
		static GGE_inline n128d swizzle(n128d v)
		{
			return _GGE_perm_pd(v, (((IdentityMask2 >> E) & 1) << A) | (IdentityMask2 & ~((1 << A))));
		}

		template<int E, int A>
		GGE_inline n128d swizzle() const
		{
			return swizzle<E % 2, A % 2>(vec[X / 2]);
		}

		// Assignment

		GGE_inline dswizzle1& operator = (double f);

		template<int A>
		GGE_inline dswizzle1& operator = (const dswizzle1<A>& s);

		GGE_inline dswizzle1& operator = (const dswizzle1<X>& s);

		GGE_inline dswizzle1& operator = (const double1& f);

	private:

		union
		{
			n128d vec[X < 2 ? 1 : 2];
			double f64[X < 2 ? 2 : 4];
		};
	};

	template<int X, int Y>
	struct GGE_nodiscard dswizzle2
	{
		template<int SrcA, int SrcB, int DstA, int DstB>
		static GGE_inline n128d swizzle(n128d vec0, n128d vec1)
		{
			// Select which vector to read from and how to build the mask based on the output
			#define GGE_SELECT(Dst) ((Dst % 2) == 0 ? (SrcA < 2 ? vec0 : vec1) : (SrcB < 2 ? vec0 : vec1))
			n128d result = _GGE_shuffle_pd(GGE_SELECT(DstA), GGE_SELECT(DstB), GGE_SHUFFLE_MASK_PD((DstA % 2) == 0 ? (SrcA % 2) : (SrcB % 2), (DstB % 2) == 0 ? (SrcA % 2) : (SrcB % 2)));
			#undef GGE_SELECT
			return result;
		}

		template<int SrcA, int SrcB, int DstA, int DstB>
		GGE_inline n128d swizzle() const
		{
			// Select which vector to read from and how to build the mask based on the output
			#define GGE_SELECT(Dst) (Dst % 2) == 0 ? vec[(SrcA < 2) ? 0 : 1] : vec[(SrcB < 2) ? 0 : 1]
			n128d result = _GGE_shuffle_pd(GGE_SELECT(DstA), GGE_SELECT(DstB), GGE_SHUFFLE_MASK_PD((DstA % 2) == 0 ? (SrcA % 2) : (SrcB % 2), (DstB % 2) == 0 ? (SrcA % 2) : (SrcB % 2)));
			#undef GGE_SELECT
			return result;
		}
	
		template<int E, int F>
		GGE_inline void swizzle_all(const dswizzle2<E, F>& s)
		{
			GGE_constexpr_if((X < 2 && Y < 2) || (X >= 2 && Y >= 2))
			{
				vec[(X < 2 && Y < 2) ? 0 : 1] = s.template swizzle<E, F, X, Y>();
			}
			else
			{
				// Swizzle E and F into both 0 and 1
				n128d swizzledE = s.template swizzle<E, E, 0, 1>();
				n128d swizzledF = s.template swizzle<F, F, 0, 1>();

				// Blend with original vectors to preserve contents in remaining entries
				vec[X / 2] = _GGE_blend_pd(vec[X / 2], swizzledE, GGE_BLEND_MASK_PD((X % 2) == 1, (X % 2) == 0));
				vec[Y / 2] = _GGE_blend_pd(vec[Y / 2], swizzledF, GGE_BLEND_MASK_PD((Y % 2) == 1, (Y % 2) == 0));
			}
		}

		// Assignment
	
		template<int E, int F>
		GGE_inline dswizzle2& operator = (const dswizzle2<E, F>& s);

		GGE_inline dswizzle2& operator = (const dswizzle2<X, Y>& s);
	
		GGE_inline dswizzle2& operator = (const double2& f);
	
		union
		{
			n128d vec[(X < 2 && Y < 2) ? 1 : 2];
			double f64[(X < 2 && Y < 2) ? 2 : 4];
		};
	};

	template<int X, int Y, int Z>
	struct GGE_nodiscard dswizzle3
	{
		template<int A, int B, int C>
		GGE_inline void swizzle_all(const dswizzle3<A, B, C>& s)
		{
#if defined(GGE_SIMD_REGISTER_256)
			swizzleblend<A, B, C, X, Y, Z>(s.vec, vec);
#else
			swizzleblend<A, B, C, X, Y, Z>(s.vec[0], s.vec[1], vec[0], vec[1]);
#endif
		}

		// Assignment

		template<int A, int B, int C>
		GGE_inline dswizzle3& operator = (const dswizzle3<A, B, C>& s);

		GGE_inline dswizzle3& operator = (const dswizzle3<X, Y, Z>& s);

		GGE_inline dswizzle3& operator = (const double3& f);

#if defined(GGE_SIMD_REGISTER_256)

		// Swizzles SrcA into 0, SrcB into 1 and SrcC into 2
		// This version doesn't blend so only works for dswizzle3 -> double3 conversions
		template<int SrcA, int SrcB, int SrcC>
		static GGE_inline void swizzle(n256d vec, n256d& ovec)
		{
			ovec = _GGE256_perm_pd(vec, SrcA, SrcB, SrcC, SrcC);
		}

		// Swizzles SrcA, SrcB, SrcC into DstA, DstB, DstC
		template<int SrcA, int SrcB, int SrcC, int DstA, int DstB, int DstC>
		static GGE_inline void swizzleblend(n256d vec, n256d& ovec)
		{
			#define GGE_SELECT(x) (DstA == x ? SrcA : (DstB == x ? SrcB : SrcC))
			#define GGE_BLEND(x) ((DstA == x || DstB == x || DstC == x) ? 1 : 0)
			n256d perm = _GGE256_perm_pd(vec, GGE_SELECT(0), GGE_SELECT(1), GGE_SELECT(2), GGE_SELECT(3));
			ovec = _GGE256_blend_pd(perm, ovec, GGE_BLEND_MASK(GGE_BLEND(0), GGE_BLEND(1), GGE_BLEND(2), GGE_BLEND(3)));
			#undef GGE_SELECT
			#undef GGE_BLEND
		}

#else

		// Swizzles SrcA into position 0 and SrcB into position 1
		template<int SrcA, int SrcB>
		static GGE_inline n128d swizzle(n128d vec0, n128d vec1)
		{
			return _GGE_shuffle_pd(SrcA < 2 ? vec0 : vec1, SrcB < 2 ? vec0 : vec1, GGE_SHUFFLE_MASK_PD(SrcA % 2, SrcB % 2));
		}

		// Swizzles SrcA into 0, SrcB into 1 and SrcC into 2
		// This version doesn't blend so only works for dswizzle3 -> double3 conversions
		template<int SrcA, int SrcB, int SrcC>
		static GGE_inline void swizzle(n128d vec0, n128d vec1, n128d& ovec0, n128d& ovec1)
		{
			ovec0 = swizzle<SrcA, SrcB>(vec0, vec1);
			ovec1 = swizzle<SrcC, 0   >(vec0, vec1);
		}

		// Swizzles SrcA into DstA, SrcB into DstB and SrcC into DstC
		// Needs to blend to be able to preserve the remaining component
		template<int SrcA, int SrcB, int SrcC, int DstA, int DstB, int DstC>
		static GGE_inline void swizzleblend(n128d vec0, n128d vec1, n128d& ovec0, n128d& ovec1)
		{
			#define GGE_SELECT(x) (DstA == x ? SrcA : (DstB == x ? SrcB : SrcC))
			#define GGE_BLEND(x) ((DstA == x || DstB == x || DstC == x) ? 1 : 0)

			n128d swizzle0 = swizzle<GGE_SELECT(0), GGE_SELECT(1)>(vec0, vec1);
			n128d swizzle1 = swizzle<GGE_SELECT(2), GGE_SELECT(3)>(vec0, vec1);

			ovec0 = _GGE_blend_pd(swizzle0, ovec0, GGE_BLEND_MASK_PD(GGE_BLEND(0), GGE_BLEND(1)));
			ovec1 = _GGE_blend_pd(swizzle1, ovec1, GGE_BLEND_MASK_PD(GGE_BLEND(2), GGE_BLEND(3)));

			#undef GGE_SELECT
			#undef GGE_BLEND
		}

#endif

		union
		{
#if defined(GGE_SIMD_REGISTER_256)
			n256d vec;
#else
			n128d vec[2];
#endif
			double f64[4];
		};
	};

	template<int X, int Y, int Z, int W>
	struct GGE_nodiscard dswizzle4
	{
		template<int A, int B, int C, int D>
		GGE_inline dswizzle4& operator = (const dswizzle4<A, B, C, D>& s);
		
		GGE_inline dswizzle4& operator = (const double4& f);

#if defined(GGE_SIMD_REGISTER_256)

		// Swizzles SrcA, SrcB, SrcC into DstA, DstB, DstC
		template<int SrcA, int SrcB, int SrcC, int SrcD, int DstA, int DstB, int DstC, int DstD>
		static GGE_inline void swizzle(n256d vec, n256d& ovec)
		{
			#define GGE_SELECT(x) DstA == x ? SrcA : (DstB == x ? SrcB : (DstC == x ? SrcC : SrcD))
			ovec = _GGE256_perm_pd(vec, GGE_SELECT(0), GGE_SELECT(1), GGE_SELECT(2), GGE_SELECT(3));
			#undef GGE_SELECT
		}

#else

		template<int SrcA, int SrcB, int SrcC, int SrcD, int DstA, int DstB, int DstC, int DstD>
		static GGE_inline void swizzle(n128d vec0, n128d vec1, n128d& ovec0, n128d& ovec1)
		{
			#define GGE_SELECT(x) (DstA == x ? SrcA : (DstB == x ? SrcB : (DstC == x ? SrcC : SrcD)))

			#define GGE_dswizzle4_swizzle2(SrcA, SrcB, vec0, vec1) \
				_GGE_shuffle_pd((SrcA) < 2 ? vec0 : vec1, (SrcB) < 2 ? vec0 : vec1, GGE_SHUFFLE_MASK_PD((SrcA) % 2, (SrcB) % 2))

			ovec0 = GGE_dswizzle4_swizzle2(GGE_SELECT(0), GGE_SELECT(1), vec0, vec1);
			ovec1 = GGE_dswizzle4_swizzle2(GGE_SELECT(2), GGE_SELECT(3), vec0, vec1);

			#undef GGE_SELECT
		}

#endif

		union
		{
#if defined(GGE_SIMD_REGISTER_256)
			n256d vec;
#else
			n128d vec[2];
#endif
			double f64[4];
		};
	};

	//-------------//
	// Double type //
	//-------------//

	struct GGE_nodiscard double1
	{
		GGE_inline double1() : vec(_GGE_setzero_pd()) {}
		GGE_inline double1(const double1& f) : vec(f.vec) {}
		explicit GGE_inline double1(n128d vec) : vec(vec) {}

		template<typename T>
		GGE_inline double1(T f, GGE_enable_if_number(T)) : vec(_GGE_set_pd(double(f), 0.0)) {}

		template<int X> GGE_inline double1(const dswizzle1<X>& s) : vec(s.template swizzle<X, 0>()) {}

		//double1(const int1& i);

		GGE_inline double1& operator = (const double1& f) { vec = f.vec; return *this; }

		operator double() const { return f64[0]; }

		GGE_WARNING_ANONYMOUS_STRUCT_UNION_BEGIN
		union
		{
			n128d vec;
			double f64[2];
			#include "swizzle/vector_double_x.h"
		};
		GGE_WARNING_ANONYMOUS_STRUCT_UNION_END
	};

	struct GGE_nodiscard double2
	{
		// Constructors

		GGE_inline double2() : vec(_GGE_setzero_pd()) {}
		GGE_inline double2(const double2& f) : vec(f.vec) {}
		explicit GGE_inline double2(n128d vec) : vec(vec) {}
		explicit GGE_inline double2(const double1& f) : vec(_GGE_perm_xx_pd(f.vec)) {}

		template<typename T>
		GGE_inline double2(T f, GGE_enable_if_number(T)) : vec(_GGE_set_pd(double(f), double(f))) {}

		template<typename T1, typename T2>
		GGE_inline double2(T1 f1, T2 f2, GGE_enable_if_number_2(T1, T2)) : vec(_GGE_set_pd(double(f1), double(f2))) {}

		GGE_inline double2(const double1& f1, const double1& f2) { vec = _GGE_blend_pd(f1.vec, _GGE_perm_xx_pd(f2.vec), GGE_BLEND_MASK_PD(1, 0)); }
		
		template<int X, int Y> GGE_inline double2(const dswizzle2<X, Y>& s) : vec(s.template swizzle<X, Y, 0, 1>()) {}

		//double2(const int2& i);

		GGE_inline double2& operator = (const double2& f) { vec = f.vec; return *this; }

		GGE_WARNING_ANONYMOUS_STRUCT_UNION_BEGIN
		union
		{
			n128d vec;
			double f64[2];
			#include "swizzle/vector_double_x.h"
			#include "swizzle/vector_double_y.h"
		};
		GGE_WARNING_ANONYMOUS_STRUCT_UNION_END
	};

	struct GGE_nodiscard double3
	{
		// Constructors

#if defined(GGE_SIMD_REGISTER_256)

		GGE_inline double3() : vec(_GGE256_setzero_pd()) {}
		GGE_inline double3(const double3& f) : vec(f.vec) {}
		explicit GGE_inline double3(n256d vec) : vec(vec) {}
		explicit GGE_inline double3(const double1& f) : vec(_GGE256_set128_pd(_GGE_perm_xx_pd(f.vec), _GGE_perm_xx_pd(f.vec))) {}

		template<typename T>
		GGE_inline double3(T f, GGE_enable_if_number(T)) : vec(_GGE256_set_pd(double(f), double(f), double(f), 0.0)) {}

		template<typename T1, typename T2, typename T3>
		GGE_inline double3(T1 f1, T2 f2, T3 f3, GGE_enable_if_number_3(T1, T2, T3)) : vec(_GGE256_set_pd(double(f1), double(f2), double(f3), 0.0)) {}

		GGE_inline double3& operator = (const double3& f) { vec = f.vec; return *this; }

#else

		GGE_inline double3() : vec0(_GGE_setzero_pd()), vec1(_GGE_setzero_pd()) {}
		GGE_inline double3(const double3& f) : vec0(f.vec0), vec1(f.vec1) {}
		explicit GGE_inline double3(n128d vec0, n128d vec1) : vec0(vec0), vec1(vec1) {}
		explicit GGE_inline double3(const double1& f) : vec0(_GGE_perm_xx_pd(f.vec)), vec1(_GGE_perm_xx_pd(f.vec)) {}

		template<typename T>
		GGE_inline double3(T f, GGE_enable_if_number(T)) : vec0(_GGE_set_pd(double(f), double(f))), vec1(_GGE_set_pd(double(f), 0.0)) {}

		template<typename T1, typename T2, typename T3>
		GGE_inline double3(T1 f1, T2 f2, T3 f3, GGE_enable_if_number_3(T1, T2, T3)) : vec0(_GGE_set_pd(double(f1), double(f2))), vec1(_GGE_set_pd(double(f3), 0.0)) {}

		GGE_inline double3& operator = (const double3& f) { vec0 = f.vec0; vec1 = f.vec1; return *this; }

#endif

		GGE_inline double3(const double1& f1, const double1& f2, const double1& f3)
		{
#if defined(GGE_SIMD_REGISTER_256)
			n128d f1f2 = _GGE_shuf_xx_pd(f1.vec, f2.vec);
			vec = _GGE256_set128_pd(f1f2, f3.vec);
#else
			vec0 = _GGE_shuf_xx_pd(f1.vec, f2.vec);
			vec1 = f3.vec;
#endif
		}

		GGE_inline double3(const double2& f1, const double1& f2)
		{
#if defined(GGE_SIMD_REGISTER_256)
			vec = _GGE256_set128_pd(f1.vec, f2.vec);
#else
			vec0 = f1.vec;
			vec1 = f2.vec;
#endif
		}

		GGE_inline double3(const double1& f1, const double2& f2)
		{
#if defined(GGE_SIMD_REGISTER_256)
			n128d f1f2x = _GGE_shuf_xx_pd(f1.vec, f2.vec);
			n128d f2y = _GGE_perm_yx_pd(f2.vec);
			vec = _GGE256_set128_pd(f1f2x, f2y);
#else
			vec0 = _GGE_shuf_xx_pd(f1.vec, f2.vec);
			vec1 = _GGE_perm_yx_pd(f2.vec);
#endif
		}

		template<int X, int Y, int Z>
		GGE_inline double3(const dswizzle3<X, Y, Z>& s)
		{
#if defined(GGE_SIMD_REGISTER_256)
			dswizzle3<X, Y, Z>::template swizzle<X, Y, Z>(s.vec, vec);
#else
			dswizzle3<X, Y, Z>::template swizzle<X, Y, Z>(s.vec[0], s.vec[1], vec0, vec1);
#endif
		}
		
		//float3(const int3& i);

		GGE_WARNING_ANONYMOUS_STRUCT_UNION_BEGIN
		union
		{
#if defined(GGE_SIMD_REGISTER_256)

			n256d vec;

#else

			GGE_WARNING_ANONYMOUS_STRUCT_UNION_BEGIN
			struct
			{
				n128d vec0;
				n128d vec1;
			};
			GGE_WARNING_ANONYMOUS_STRUCT_UNION_END

#endif

			double f64[4];
			#include "swizzle/vector_double_x.h"
			#include "swizzle/vector_double_y.h"
			#include "swizzle/vector_double_z.h"
		};
		GGE_WARNING_ANONYMOUS_STRUCT_UNION_END
	};

	struct GGE_nodiscard double4
	{
#if defined(GGE_SIMD_REGISTER_256)

		GGE_inline double4() : vec(_GGE256_setzero_pd()) {}
		GGE_inline double4(const double4& f) : vec(f.vec) {}
		explicit GGE_inline double4(n256d vec) : vec(vec) {}
		explicit GGE_inline double4(const double1& f) : vec(_GGE256_set128_pd(_GGE_perm_xx_pd(f.vec), _GGE_perm_xx_pd(f.vec))) {}

		template<typename T>
		GGE_inline double4(T f, GGE_enable_if_number(T)) : vec(_GGE256_set1_pd(double(f))) {}

		template<typename T1, typename T2, typename T3, typename T4>
		GGE_inline double4(T1 f1, T2 f2, T3 f3, T4 f4, GGE_enable_if_number_4(T1, T2, T3, T4)) : vec(_GGE256_set_pd(double(f1), double(f2), double(f3), double(f4))) {}

		GGE_inline double4& operator = (const double4& f) { vec = f.vec; return *this; }

#else

		GGE_inline double4() : vec0(_GGE_setzero_pd()), vec1(_GGE_setzero_pd()) {}
		GGE_inline double4(const double4& f) : vec0(f.vec0), vec1(f.vec1) {}
		explicit GGE_inline double4(n128d vec0, n128d vec1) : vec0(vec0), vec1(vec1) {}
		explicit GGE_inline double4(const double1& f) : vec0(_GGE_perm_xx_pd(f.vec)), vec1(_GGE_perm_xx_pd(f.vec)) {}

		template<typename T>
		GGE_inline double4(T f, GGE_enable_if_number(T)) : vec0(_GGE_set1_pd(double(f))), vec1(_GGE_set1_pd(double(f))) {}

		template<typename T1, typename T2, typename T3, typename T4>
		GGE_inline double4(T1 f1, T2 f2, T3 f3, T4 f4, GGE_enable_if_number_4(T1, T2, T3, T4)) : vec0(_GGE_set_pd(double(f1), double(f2))), vec1(_GGE_set_pd(double(f3), double(f4))) {}

		GGE_inline double4& operator = (const double4& f) { vec0 = f.vec0; vec1 = f.vec1; return *this; }

#endif

		GGE_inline double4(const double1& f1, const double1& f2, const double1& f3, const double1& f4)
		{
#if defined(GGE_SIMD_REGISTER_256)
			n128d f1f2 = _GGE_shuf_xx_pd(f1.vec, f2.vec);
			n128d f3f4 = _GGE_shuf_xx_pd(f3.vec, f4.vec);
			vec = _GGE256_set128_pd(f1f2, f3f4);
#else
			vec0 = _GGE_shuf_xx_pd(f1.vec, f2.vec);
			vec1 = _GGE_shuf_xx_pd(f3.vec, f4.vec);
#endif
		}

		GGE_inline double4(const double2& f1, const double1& f2, const double1& f3)
		{
#if defined(GGE_SIMD_REGISTER_256)
			vec = _GGE256_set128_pd(f1.vec, _GGE_shuf_xx_pd(f2.vec, f3.vec));
#else
			vec0 = f1.vec;
			vec1 = _GGE_shuf_xx_pd(f2.vec, f3.vec);
#endif
		}

		GGE_inline double4(const double1& f1, const double2& f2, const double1& f3)
		{
#if defined(GGE_SIMD_REGISTER_256)
			vec = _GGE256_set128_pd(_GGE_shuf_xx_pd(f1.vec, f2.vec), _GGE_shuf_yx_pd(f2.vec, f3.vec));
#else
			vec0 = _GGE_shuf_xx_pd(f1.vec, f2.vec);
			vec1 = _GGE_shuf_yx_pd(f2.vec, f3.vec);
#endif
		}

		GGE_inline double4(const double1& f1, const double1& f2, const double2& f3)
		{
#if defined(GGE_SIMD_REGISTER_256)
			vec = _GGE256_set128_pd(_GGE_shuf_xx_pd(f1.vec, f2.vec), f3.vec);
#else
			vec0 = _GGE_shuf_xx_pd(f1.vec, f2.vec);
			vec1 = f3.vec;
#endif
		}

		GGE_inline double4(const double2& f1, const double2& f2)
		{
#if defined(GGE_SIMD_REGISTER_256)
			vec = _GGE256_set128_pd(f1.vec, f2.vec);
#else
			vec0 = f1.vec;
			vec1 = f2.vec;
#endif
		}

		GGE_inline double4(const double1& f1, const double3& f2)
		{
#if defined(GGE_SIMD_REGISTER_256)
			vec = _GGE256_set128_pd(_GGE_shuf_xx_pd(f1.vec, _GGE256_low_pd(f2.vec)), _GGE_shuf_yx_pd(_GGE256_low_pd(f2.vec), _GGE256_high_pd(f2.vec)));
#else
			vec0 = _GGE_shuf_xx_pd(f1.vec, f2.vec0);
			vec1 = _GGE_shuf_yx_pd(f2.vec0, f2.vec1);
#endif
		}

		GGE_inline double4(const double3& f1, const double1& f2)
		{
#if defined(GGE_SIMD_REGISTER_256)

			vec = _GGE256_set128_pd(_GGE256_low_pd(f1.vec), _GGE_shuf_xx_pd(_GGE256_high_pd(f1.vec), f2.vec));
#else
			vec0 = f1.vec0;
			vec1 = _GGE_shuf_xx_pd(f1.vec1, f2.vec);
#endif
		}
		
		template<int X, int Y, int Z, int W>
		GGE_inline double4(const dswizzle4<X, Y, Z, W>& s)
		{
#if defined(GGE_SIMD_REGISTER_256)
			dswizzle4<X, Y, Z, W>::template swizzle<X, Y, Z, W, 0, 1, 2, 3>(s.vec, vec);
#else
			dswizzle4<X, Y, Z, W>::template swizzle<X, Y, Z, W, 0, 1, 2, 3>(s.vec[0], s.vec[1], vec[0], vec[1]);
#endif
		}

		//double4(const int4& i);

		GGE_WARNING_ANONYMOUS_STRUCT_UNION_BEGIN
		union
		{
#if defined(GGE_SIMD_REGISTER_256)
			n256d vec;
#else
			GGE_WARNING_ANONYMOUS_STRUCT_UNION_BEGIN
			struct
			{
				n128d vec0;
				n128d vec1;
			};
			GGE_WARNING_ANONYMOUS_STRUCT_UNION_END

			n128d vec[2];
#endif
			double f64[4];
			#include "swizzle/vector_double_x.h"
			#include "swizzle/vector_double_y.h"
			#include "swizzle/vector_double_z.h"
			#include "swizzle/vector_double_w.h"
		};
		GGE_WARNING_ANONYMOUS_STRUCT_UNION_END
	};

	GGE_inline void store(double* dst, const double1& src)
	{
		_GGE_store1_pd(dst, src.vec);
	}

	GGE_inline void store(double* dst, const double2& sc)
	{
		_GGE_store2_pd(dst, sc.vec);
	}

	GGE_inline void store(double* dst, const double3& src)
	{
#if defined(GGE_SIMD_REGISTER_256)
		_GGE256_store3_pd(dst, src.vec);
#else
		_GGE_store3_pd(dst, src.vec0, src.vec1);
#endif
	}

	GGE_inline void store(double* dst, const double4& src)
	{
#if defined(GGE_SIMD_REGISTER_256)
		_GGE256_store4_pd(dst, src.vec);
#else
		_GGE_store4_pd(dst, src.vec0, src.vec1);
#endif
	}

	GGE_inline void load(double1& dst, const double* src)
	{
		_GGE_load1_pd(dst.vec, src);
	}

	GGE_inline void load(double2& dst, const double* src)
	{
		_GGE_load2_pd(dst.vec, src);
	}

	GGE_inline void load(double3& dst, const double* src)
	{
#if defined(GGE_SIMD_REGISTER_256)
		_GGE256_load3_pd(dst.vec, src);
#else
		_GGE_load3_pd(dst.vec0, dst.vec1, src);
#endif
	}

	GGE_inline void load(double4& dst, const double* src)
	{
#if defined(GGE_SIMD_REGISTER_256)
		_GGE256_load4_pd(dst.vec, src);
#else
		_GGE_load4_pd(dst.vec0, dst.vec1, src);
#endif
	}

	namespace interop
	{
		struct double4
		{
			double4() GGE_constructor_default;
			double4(const GGE::double4& f) { GGE::store(&x, f); }
			double x, y, z, w;
		};

		struct double3
		{
			double3() GGE_constructor_default;
			double3(const GGE::double3& f) { GGE::store(&x, f); }
			double x, y, z;
		};

		struct double2
		{
			double2() GGE_constructor_default;
			double2(const GGE::double2& f) { GGE::store(&x, f); }
			double x, y;
		};

		typedef double double1;
	};
};

GGE_WARNING_IMPLICIT_CONSTRUCTOR_BEGIN

#endif