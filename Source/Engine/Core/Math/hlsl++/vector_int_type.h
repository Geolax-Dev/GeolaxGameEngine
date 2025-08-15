#pragma once

#include <Core/Math/hlsl++/common.h>

GGE_WARNING_IMPLICIT_CONSTRUCTOR_BEGIN

GGE_module_export namespace GGE
{
	template<int X>
	struct GGE_nodiscard iswizzle1
	{
		template<int A> friend struct iswizzle1;
	
		// Cast
	
		GGE_inline operator int32_t() const { return i32[X]; }

		// Return the address of this int32 in the same way we return the value
		GGE_inline int32_t* operator&() { return &i32[X]; }
	
		#define GGE_iswizzle1_swizzle(E, A, v) (_GGE_perm_epi32(v, A == 0 ? E : 0, A == 1 ? E : 1, A == 2 ? E : 2, A == 3 ? E : 3))

		GGE_inline iswizzle1& operator = (int32_t i);

		template<int A>
		GGE_inline iswizzle1& operator = (const iswizzle1<A>& s);

		GGE_inline iswizzle1& operator = (const iswizzle1<X>& s);

		GGE_inline iswizzle1& operator = (const int1& i);

		union
		{
			n128i vec;
			int32_t i32[4];
		};
	};


	template<int X, int Y>
	struct GGE_nodiscard iswizzle2
	{
		#define GGE_iswizzle2_swizzle(E, F, A, B, v) \
		    (_GGE_perm_epi32(v, A == 0 ? E : B == 0 ? F : 0, \
		                           A == 1 ? E : B == 1 ? F : 1, \
		                           A == 2 ? E : B == 2 ? F : 2, \
		                           A == 3 ? E : B == 3 ? F : 3))

		// Select based on property mask
		#define GGE_iswizzle2_blend(x, y) _GGE_blend_epi32(x, y, GGE_COMPONENT_XY(X, Y))

		// Assignment

		template<int A, int B>
		GGE_inline iswizzle2& operator = (const iswizzle2<A, B>& s);

		GGE_inline iswizzle2& operator = (const iswizzle2<X, Y>& s);

		GGE_inline iswizzle2& operator = (const int2& i);

		n128i vec;
	};

	template<int X, int Y, int Z>
	struct GGE_nodiscard iswizzle3
	{
		#define GGE_iswizzle3_swizzle(E, F, G, A, B, C, v) \
		    (_GGE_perm_epi32(v, A == 0 ? E : B == 0 ? F : C == 0 ? G : 0, \
		                           A == 1 ? E : B == 1 ? F : C == 1 ? G : 1, \
		                           A == 2 ? E : B == 2 ? F : C == 2 ? G : 2, \
		                           A == 3 ? E : B == 3 ? F : C == 3 ? G : 3))

		// Select based on property mask
		#define GGE_iswizzle3_blend(x, y) _GGE_blend_epi32(x, y, GGE_COMPONENT_XYZ(X, Y, Z))

		// Assignment

		template<int A, int B, int C>
		GGE_inline iswizzle3& operator = (const iswizzle3<A, B, C>& s);

		GGE_inline iswizzle3& operator = (const iswizzle3<X, Y, Z>& s);

		GGE_inline iswizzle3& operator = (const int3& i);

		n128i vec;
	};

	template<int X, int Y, int Z, int W>
	struct GGE_nodiscard iswizzle4
	{
		#define GGE_iswizzle4_swizzle(E, F, G, H, A, B, C, D, v) \
		    (_GGE_perm_epi32(v, A == 0 ? E : B == 0 ? F : C == 0 ? G : D == 0 ? H : 0, \
		                           A == 1 ? E : B == 1 ? F : C == 1 ? G : D == 1 ? H : 1, \
		                           A == 2 ? E : B == 2 ? F : C == 2 ? G : D == 2 ? H : 2, \
		                           A == 3 ? E : B == 3 ? F : C == 3 ? G : D == 3 ? H : 3))

		template<int A, int B, int C, int D>
		GGE_inline iswizzle4& operator = (const iswizzle4<A, B, C, D>& s);

		GGE_inline iswizzle4& operator = (const int4& i);

		n128i vec;
	};

	struct GGE_nodiscard GGE_alignas(16) int1
	{
		GGE_inline int1() GGE_noexcept : vec(_GGE_setzero_epi32()) {}
		GGE_inline int1(const int1& i) GGE_noexcept : vec(i.vec) {}
		explicit GGE_inline int1(n128i vec) GGE_noexcept : vec(vec) {}

		template<typename T>
		GGE_inline int1(T i, GGE_enable_if_number(T)) GGE_noexcept : vec(_GGE_set_epi32((int)i, 0, 0, 0)) {}

		template<int X> GGE_inline int1(const iswizzle1<X>& s) GGE_noexcept
			: vec(GGE_iswizzle1_swizzle(X, 0, s.vec)) {}

		GGE_inline int1(const float1& f) GGE_noexcept;

		GGE_inline int1& operator = (const int1& i) GGE_noexcept { vec = i.vec; return *this; }

		GGE_inline int1(int1&& i) GGE_noexcept : vec(i.vec) {}
		GGE_inline int1& operator = (int1&& i) GGE_noexcept { vec = i.vec; return *this; }

		GGE_inline operator int32_t() const { return i32[0]; }

		int32_t& operator[](int N)
		{
			GGE_assert(N == 0);
			return i32[N];
		}

		const int32_t& operator[](int N) const
		{
			GGE_assert(N == 0);
			return i32[N];
		}

		GGE_WARNING_ANONYMOUS_STRUCT_UNION_BEGIN
		union
		{
			n128i vec;
			int32_t i32[1];
			#include "swizzle/vector_int_x.h"
		};
		GGE_WARNING_ANONYMOUS_STRUCT_UNION_END
	};

	
	struct GGE_nodiscard GGE_alignas(16) int2
	{
		// Constructors

		GGE_inline int2() GGE_noexcept : vec(_GGE_setzero_epi32()) {}
		GGE_inline int2(const int2& i) GGE_noexcept : vec(i.vec) {}
		explicit GGE_inline int2(n128i vec) GGE_noexcept : vec(vec) {}
		explicit GGE_inline int2(const int1& i) GGE_noexcept : vec(_GGE_perm_xxxx_epi32(i.vec)) {}

		GGE_inline int2(int32_t i) GGE_noexcept : vec(_GGE_set_epi32(i, i, 0, 0)) {}

		template<typename T1, typename T2>
		GGE_inline int2(T1 i1, T2 i2, GGE_enable_if_number_2(T1, T2)) GGE_noexcept : vec(_GGE_set_epi32((int)i1, (int)i2, 0, 0)) {}

		GGE_inline int2(const int1& i1, const int1& i2) GGE_noexcept { vec = _GGE_blend_epi32(i1.vec, _GGE_perm_xxxx_epi32(i2.vec), GGE_BLEND_MASK(1, 0, 1, 1)); }
		
		template<int X, int Y> GGE_inline int2(const iswizzle2<X, Y>& s) GGE_noexcept
			: vec(GGE_iswizzle2_swizzle(X, Y, 0, 1, s.vec)) {}

		GGE_inline int2(const float2& f) GGE_noexcept;

		GGE_inline int2& operator = (const int2& i) GGE_noexcept { vec = i.vec; return *this; }

		GGE_inline int2(int2&& i) GGE_noexcept : vec(i.vec) {}
		GGE_inline int2& operator = (int2&& i) GGE_noexcept { vec = i.vec; return *this; }

		int32_t& operator[](int N)
		{
			GGE_assert(N >= 0 && N <= 1);
			return i32[N];
		}

		const int32_t& operator[](int N) const
		{
			GGE_assert(N >= 0 && N <= 1);
			return i32[N];
		}

		GGE_WARNING_ANONYMOUS_STRUCT_UNION_BEGIN
		union
		{
			n128i vec;
			int32_t i32[2];
			#include "swizzle/vector_int_x.h"
			#include "swizzle/vector_int_y.h"
		};
		GGE_WARNING_ANONYMOUS_STRUCT_UNION_END
	};

	struct GGE_nodiscard GGE_alignas(16) int3
	{
		// Constructors

		GGE_inline int3() GGE_noexcept : vec(_GGE_setzero_epi32()) {}
		GGE_inline int3(const int3& i) GGE_noexcept : vec(i.vec) {}
		explicit GGE_inline int3(n128i vec) GGE_noexcept : vec(vec) {}

		explicit GGE_inline int3(const int1& i) GGE_noexcept : vec(_GGE_perm_xxxx_epi32(i.vec)) {}

		GGE_inline int3(int32_t i) GGE_noexcept : vec(_GGE_set_epi32(i, i, i, 0)) {}

		template<typename T1, typename T2, typename T3>
		GGE_inline int3(T1 i1, T2 i2, T3 i3, GGE_enable_if_number_3(T1, T2, T3)) GGE_noexcept : vec(_GGE_set_epi32((int)i1, (int)i2, (int)i3, 0)) {}

		GGE_inline int3(const int1& i1, const int1& i2, const int1& i3) GGE_noexcept { vec = _GGE_blend_epi32(_GGE_shuf_xxxx_epi32(i1.vec, i3.vec), _GGE_perm_xxxx_epi32(i2.vec), GGE_BLEND_MASK(1, 0, 1, 0)); }

		GGE_inline int3(const int2& i1, const int1& i2) GGE_noexcept { vec = _GGE_shuf_xyxx_epi32(i1.vec, i2.vec); }
		GGE_inline int3(const int1& i1, const int2& i2) GGE_noexcept { vec = _GGE_blend_epi32(i1.vec, _GGE_perm_xxyx_epi32(i2.vec), GGE_BLEND_MASK(1, 0, 0, 1)); }

		template<int X, int Y, int Z>
		GGE_inline int3(const iswizzle3<X, Y, Z>& s) GGE_noexcept
			: vec(GGE_iswizzle3_swizzle(X, Y, Z, 0, 1, 2, s.vec)) {}

		GGE_inline int3(const float3& f) GGE_noexcept;

		GGE_inline int3& operator = (const int3& i) GGE_noexcept { vec = i.vec; return *this; }

		GGE_inline int3(int3&& i) GGE_noexcept : vec(i.vec) {}
		GGE_inline int3& operator = (int3&& i) GGE_noexcept { vec = i.vec; return *this; }

		int32_t& operator[](int N)
		{
			GGE_assert(N >= 0 && N <= 2);
			return i32[N];
		}

		const int32_t& operator[](int N) const
		{
			GGE_assert(N >= 0 && N <= 2);
			return i32[N];
		}

		GGE_WARNING_ANONYMOUS_STRUCT_UNION_BEGIN
		union
		{
			n128i vec;
			int32_t i32[3];
			#include "swizzle/vector_int_x.h"
			#include "swizzle/vector_int_y.h"
			#include "swizzle/vector_int_z.h"
		};
		GGE_WARNING_ANONYMOUS_STRUCT_UNION_END
	};

	struct GGE_nodiscard GGE_alignas(16) int4
	{
		GGE_inline int4() GGE_noexcept : vec(_GGE_setzero_epi32()) {}
		GGE_inline int4(const int4& i) GGE_noexcept : vec(i.vec) {}
		explicit GGE_inline int4(n128i vec) GGE_noexcept : vec(vec) {}

		explicit GGE_inline int4(const int1& i) GGE_noexcept : vec(_GGE_perm_xxxx_epi32(i.vec)) {}

		GGE_inline int4(int32_t i) GGE_noexcept : vec(_GGE_set1_epi32(i)) {}

		template<typename T1, typename T2, typename T3, typename T4>
		GGE_inline int4(T1 i1, T2 i2, T3 i3, T4 i4, GGE_enable_if_number_4(T1, T2, T3, T4)) GGE_noexcept : vec(_GGE_set_epi32((int)i1, (int)i2, (int)i3, (int)i4)) {}

		GGE_inline int4(const int1& i1, const int1& i2, const int1& i3, const int1& i4) GGE_noexcept
		{ vec = _GGE_blend_epi32(_GGE_shuf_xxxx_epi32(i1.vec, i3.vec), _GGE_shuf_xxxx_epi32(i2.vec, i4.vec), GGE_BLEND_MASK(1, 0, 1, 0)); }
		
		GGE_inline int4(const int2& i1, const int1& i2, const int1& i3) GGE_noexcept
		{ vec = _GGE_blend_epi32(_GGE_shuf_xyxx_epi32(i1.vec, i2.vec), _GGE_perm_xxxx_epi32(i3.vec), GGE_BLEND_MASK(1, 1, 1, 0)); }

		GGE_inline int4(const int1& i1, const int2& i2, const int1& i3) GGE_noexcept
		{ vec = _GGE_blend_epi32(_GGE_shuf_xxxx_epi32(i1.vec, i3.vec), _GGE_perm_xxyx_epi32(i2.vec), GGE_BLEND_MASK(1, 0, 0, 1)); }

		GGE_inline int4(const int1& i1, const int1& i2, const int2& i3) GGE_noexcept
		{ vec = _GGE_blend_epi32(_GGE_shuf_xxxy_epi32(i1.vec, i3.vec), _GGE_perm_xxxx_epi32(i2.vec), GGE_BLEND_MASK(1, 0, 1, 1)); }

		GGE_inline int4(const int2& i1, const int2& f2) GGE_noexcept { vec = _GGE_shuf_xyxy_epi32(i1.vec, f2.vec); }

		GGE_inline int4(const int1& i1, const int3& i2) GGE_noexcept { vec = _GGE_blend_epi32(i1.vec, _GGE_perm_xxyz_epi32(i2.vec), GGE_BLEND_MASK(1, 0, 0, 0)); }
		GGE_inline int4(const int3& i1, const int1& i2) GGE_noexcept { vec = _GGE_blend_epi32(i1.vec, _GGE_perm_xxxx_epi32(i2.vec), GGE_BLEND_MASK(1, 1, 1, 0)); }

		template<int X, int Y, int Z, int W>
		GGE_inline int4(const iswizzle4<X, Y, Z, W>& s) GGE_noexcept
			: vec(GGE_iswizzle4_swizzle(X, Y, Z, W, 0, 1, 2, 3, s.vec)) {}

		GGE_inline int4(const float4& f) GGE_noexcept;

		GGE_inline int4& operator = (const int4& i) GGE_noexcept { vec = i.vec; return *this; }

		GGE_inline int4(int4&& i) GGE_noexcept : vec(i.vec) {}
		GGE_inline int4& operator = (int4&& i) GGE_noexcept { vec = i.vec; return *this; }

		int32_t& operator[](int N)
		{
			GGE_assert(N >= 0 && N <= 3);
			return i32[N];
		}

		const int32_t& operator[](int N) const
		{
			GGE_assert(N >= 0 && N <= 3);
			return i32[N];
		}

		GGE_WARNING_ANONYMOUS_STRUCT_UNION_BEGIN
		union
		{
			n128i vec;
			int32_t i32[4];
			#include "swizzle/vector_int_x.h"
			#include "swizzle/vector_int_y.h"
			#include "swizzle/vector_int_z.h"
			#include "swizzle/vector_int_w.h"
		};
		GGE_WARNING_ANONYMOUS_STRUCT_UNION_END
	};

	GGE_inline void store(int32_t* dst, const int1& src)
	{
		_GGE_store1_epi32(dst, src.vec);
	}

	GGE_inline void store(int32_t* dst, const int2& src)
	{
		_GGE_store2_epi32(dst, src.vec);
	}

	GGE_inline void store(int32_t* dst, const int3& src)
	{
		_GGE_store3_epi32(dst, src.vec);
	}

	GGE_inline void store(int32_t* dst, const int4& src)
	{
		_GGE_store4_epi32(dst, src.vec);
	}

	GGE_inline void load(int1& dst, const int32_t* src)
	{
		_GGE_load1_epi32(dst.vec, src);
	}

	GGE_inline void load(int2& dst, const int32_t* src)
	{
		_GGE_load2_epi32(dst.vec, src);
	}

	GGE_inline void load(int3& dst, const int32_t* src)
	{
		_GGE_load3_epi32(dst.vec, src);
	}

	GGE_inline void load(int4& dst, const int32_t* src)
	{
		_GGE_load4_epi32(dst.vec, src);
	}

	namespace interop
	{
		struct int4
		{
			int4() GGE_constructor_default;
			int4(const GGE::int4& f) { GGE::store(&x, f); }
			int32_t x, y, z, w;
		};

		struct int3
		{
			int3() GGE_constructor_default;
			int3(const GGE::int3& f) { GGE::store(&x, f); }
			int32_t x, y, z;
		};

		struct int2
		{
			int2() GGE_constructor_default;
			int2(const GGE::int2& f) { GGE::store(&x, f); }
			int32_t x, y;
		};

		typedef int32_t int1;
	};

	static_assert(GGE_alignof(int4) == 16, "Mismatched alignment");
};

GGE_WARNING_IMPLICIT_CONSTRUCTOR_END