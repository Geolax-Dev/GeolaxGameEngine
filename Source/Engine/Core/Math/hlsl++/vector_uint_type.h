#pragma once

#include <Core/Math/hlsl++/common.h>

GGE_WARNING_IMPLICIT_CONSTRUCTOR_BEGIN

namespace GGE
{
	template<int X>
	struct GGE_nodiscard uswizzle1
	{
		template<int A> friend struct uswizzle1;
	
		// Cast
	
		GGE_inline operator uint32_t() const { return u32[X]; }

		// Return the address of this uint32 in the same way we return the value
		GGE_inline uint32_t* operator&() { return &u32[X]; }
	
		#define GGE_uswizzle1_swizzle(E, A, v) (_GGE_perm_epi32(v, A == 0 ? E : 0, A == 1 ? E : 1, A == 2 ? E : 2, A == 3 ? E : 3))

		GGE_inline uswizzle1& operator = (uint32_t i);

		template<int A>
		GGE_inline uswizzle1& operator = (const uswizzle1<A>& s);

		GGE_inline uswizzle1& operator = (const uswizzle1<X>& s);

		GGE_inline uswizzle1& operator = (const uint1& i);

		union
		{
			n128u vec;
			uint32_t u32[4];
		};
	};
	
	template<int X, int Y>
	struct GGE_nodiscard uswizzle2
	{
		#define GGE_uswizzle2_swizzle(E, F, A, B, v) \
		    (_GGE_perm_epi32(v, A == 0 ? E : B == 0 ? F : 0, \
		                           A == 1 ? E : B == 1 ? F : 1, \
		                           A == 2 ? E : B == 2 ? F : 2, \
		                           A == 3 ? E : B == 3 ? F : 3))

		// Select based on property mask
		#define GGE_uswizzle2_blend(x, y) _GGE_blend_epi32(x, y, GGE_COMPONENT_XY(X, Y))

		template<int A, int B>
		GGE_inline uswizzle2& operator = (const uswizzle2<A, B>& s);

		GGE_inline uswizzle2& operator = (const uswizzle2<X, Y>& s);

		GGE_inline uswizzle2& operator = (const uint2& i);

		n128u vec;
	};
	
	template<int X, int Y, int Z>
	struct GGE_nodiscard uswizzle3
	{
		#define GGE_uswizzle3_swizzle(E, F, G, A, B, C, v) \
		    (_GGE_perm_epi32(v, A == 0 ? E : B == 0 ? F : C == 0 ? G : 0, \
		                           A == 1 ? E : B == 1 ? F : C == 1 ? G : 1, \
		                           A == 2 ? E : B == 2 ? F : C == 2 ? G : 2, \
		                           A == 3 ? E : B == 3 ? F : C == 3 ? G : 3))

		// Select based on property mask
		#define GGE_uswizzle3_blend(x, y) _GGE_blend_epi32(x, y, GGE_COMPONENT_XYZ(X, Y, Z))

		template<int A, int B, int C>
		GGE_inline uswizzle3& operator = (const uswizzle3<A, B, C>& s);

		GGE_inline uswizzle3& operator = (const uswizzle3<X, Y, Z>& s);

		GGE_inline uswizzle3& operator = (const uint3& i);

		n128u vec;
	};

	template<int X, int Y, int Z, int W>
	struct GGE_nodiscard uswizzle4
	{
		#define GGE_uswizzle4_swizzle(E, F, G, H, A, B, C, D, v) \
		    (_GGE_perm_epi32(v, A == 0 ? E : B == 0 ? F : C == 0 ? G : D == 0 ? H : 0, \
		                           A == 1 ? E : B == 1 ? F : C == 1 ? G : D == 1 ? H : 1, \
		                           A == 2 ? E : B == 2 ? F : C == 2 ? G : D == 2 ? H : 2, \
		                           A == 3 ? E : B == 3 ? F : C == 3 ? G : D == 3 ? H : 3))

		template<int A, int B, int C, int D>
		GGE_inline uswizzle4& operator = (const uswizzle4<A, B, C, D>& s);

		GGE_inline uswizzle4& operator = (const uint4& i);

		n128u vec;
	};
	
	struct GGE_nodiscard GGE_alignas(16) uint1
	{
		GGE_inline uint1() GGE_noexcept : vec(_GGE_setzero_epu32()) {}
		GGE_inline uint1(const uint1& i) GGE_noexcept : vec(i.vec) {}
		explicit GGE_inline uint1(n128u vec) GGE_noexcept : vec(vec) {}

		template<typename T>
		GGE_inline uint1(T i, GGE_enable_if_number(T)) GGE_noexcept : vec(_GGE_set_epu32((unsigned int)i, 0, 0, 0)) {}

		template<int X> GGE_inline uint1(const uswizzle1<X>& s) GGE_noexcept
			: vec(GGE_uswizzle1_swizzle(X, 0, s.vec)) {}

		GGE_inline uint1(const float1& f) GGE_noexcept;

		GGE_inline uint1& operator = (const uint1& i) GGE_noexcept { vec = i.vec; return *this; }

		GGE_inline uint1(uint1&& i) GGE_noexcept : vec(i.vec) {}
		GGE_inline uint1& operator = (uint1&& i) GGE_noexcept { vec = i.vec; return *this; }

		GGE_inline operator uint32_t() const { return u32[0]; }

		uint32_t& operator[](int N)
		{
			GGE_assert(N == 0);
			return u32[N];
		}

		const uint32_t& operator[](int N) const
		{
			GGE_assert(N == 0);
			return u32[N];
		}

		GGE_WARNING_ANONYMOUS_STRUCT_UNION_BEGIN
		union
		{
			n128u vec;
			uint32_t u32[1];
			#include "swizzle/vector_uint_x.h"
		};
		GGE_WARNING_ANONYMOUS_STRUCT_UNION_END
	};

	struct GGE_nodiscard GGE_alignas(16) uint2
	{
		// Constructors

		GGE_inline uint2() GGE_noexcept : vec(_GGE_setzero_epu32()) {}
		GGE_inline uint2(const uint2& i) GGE_noexcept : vec(i.vec) {}
		explicit GGE_inline uint2(n128u vec) GGE_noexcept : vec(vec) {}
		explicit GGE_inline uint2(const uint1& i) GGE_noexcept : vec(_GGE_perm_xxxx_epi32(i.vec)) {}

		GGE_inline uint2(uint32_t i) GGE_noexcept : vec(_GGE_set_epu32(i, i, 0, 0)) {}

		template<typename T1, typename T2>
		GGE_inline uint2(T1 i1, T2 i2, GGE_enable_if_number_2(T1, T2)) GGE_noexcept : vec(_GGE_set_epu32((unsigned int)i1, (unsigned int)i2, 0, 0)) {}

		GGE_inline uint2(const uint1& i1, const uint1& i2) GGE_noexcept { vec = _GGE_blend_epi32(i1.vec, _GGE_perm_xxxx_epi32(i2.vec), GGE_BLEND_MASK(1, 0, 1, 1)); }
		
		template<int X, int Y> GGE_inline uint2(const uswizzle2<X, Y>& s) GGE_noexcept
			: vec(GGE_uswizzle2_swizzle(X, Y, 0, 1, s.vec)) {}

		GGE_inline uint2(const float2& f) GGE_noexcept;

		GGE_inline uint2& operator = (const uint2& i) GGE_noexcept { vec = i.vec; return *this; }

		GGE_inline uint2(uint2&& i) GGE_noexcept : vec(i.vec) {}
		GGE_inline uint2& operator = (uint2&& i) GGE_noexcept { vec = i.vec; return *this; }

		uint32_t& operator[](int N)
		{
			GGE_assert(N >= 0 && N <= 1);
			return u32[N];
		}

		const uint32_t& operator[](int N) const
		{
			GGE_assert(N >= 0 && N <= 1);
			return u32[N];
		}

		GGE_WARNING_ANONYMOUS_STRUCT_UNION_BEGIN
		union
		{
			n128u vec;
			uint32_t u32[2];
			#include "swizzle/vector_uint_x.h"
			#include "swizzle/vector_uint_y.h"
		};
		GGE_WARNING_ANONYMOUS_STRUCT_UNION_END
	};
	
	struct GGE_nodiscard GGE_alignas(16) uint3
	{
		// Constructors

		GGE_inline uint3() GGE_noexcept : vec(_GGE_setzero_epu32()) {}
		GGE_inline uint3(const uint3& i) GGE_noexcept : vec(i.vec) {}
		explicit GGE_inline uint3(n128u vec) GGE_noexcept : vec(vec) {}

		explicit GGE_inline uint3(const uint1& i) GGE_noexcept : vec(_GGE_perm_xxxx_epi32(i.vec)) {}

		GGE_inline uint3(uint32_t i) GGE_noexcept : vec(_GGE_set_epu32(i, i, i, 0)) {}

		template<typename T1, typename T2, typename T3>
		GGE_inline uint3(T1 i1, T2 i2, T3 i3, GGE_enable_if_number_3(T1, T2, T3)) GGE_noexcept : vec(_GGE_set_epu32((unsigned int)i1, (unsigned int)i2, (unsigned int)i3, 0)) {}

		GGE_inline uint3(const uint1& i1, const uint1& i2, const uint1& i3) GGE_noexcept 
		{ vec = _GGE_blend_epi32(_GGE_shuf_xxxx_epi32(i1.vec, i3.vec), _GGE_perm_xxxx_epi32(i2.vec), GGE_BLEND_MASK(1, 0, 1, 0)); }

		GGE_inline uint3(const uint2& i1, const uint1& i2) GGE_noexcept { vec = _GGE_shuf_xyxx_epi32(i1.vec, i2.vec); }
		GGE_inline uint3(const uint1& i1, const uint2& i2) GGE_noexcept { vec = _GGE_blend_epi32(i1.vec, _GGE_perm_xxyx_epi32(i2.vec), GGE_BLEND_MASK(1, 0, 0, 1)); }

		template<int X, int Y, int Z>
		GGE_inline uint3(const uswizzle3<X, Y, Z>& s) GGE_noexcept
			: vec(GGE_uswizzle3_swizzle(X, Y, Z, 0, 1, 2, s.vec)) {}

		GGE_inline uint3(const float3& f) GGE_noexcept;

		GGE_inline uint3& operator = (const uint3& i) GGE_noexcept { vec = i.vec; return *this; }

		GGE_inline uint3(uint3&& i) GGE_noexcept : vec(i.vec) {}
		GGE_inline uint3& operator = (uint3&& i) GGE_noexcept { vec = i.vec; return *this; }

		uint32_t& operator[](int N)
		{
			GGE_assert(N >= 0 && N <= 2);
			return u32[N];
		}

		const uint32_t& operator[](int N) const
		{
			GGE_assert(N >= 0 && N <= 2);
			return u32[N];
		}

		GGE_WARNING_ANONYMOUS_STRUCT_UNION_BEGIN
		union
		{
			n128u vec;
			uint32_t u32[3];
			#include "swizzle/vector_uint_x.h"
			#include "swizzle/vector_uint_y.h"
			#include "swizzle/vector_uint_z.h"
		};
		GGE_WARNING_ANONYMOUS_STRUCT_UNION_END
	};

	struct GGE_nodiscard GGE_alignas(16) uint4
	{
		GGE_inline uint4() GGE_noexcept : vec(_GGE_setzero_epu32()) {}
		GGE_inline uint4(const uint4& i) GGE_noexcept : vec(i.vec) {}
		explicit GGE_inline uint4(n128u vec) GGE_noexcept : vec(vec) {}

		explicit GGE_inline uint4(const uint1& i) GGE_noexcept : vec(_GGE_perm_xxxx_epi32(i.vec)) {}

		GGE_inline uint4(uint32_t i) GGE_noexcept : vec(_GGE_set1_epu32(i)) {}

		template<typename T1, typename T2, typename T3, typename T4>
		GGE_inline uint4(T1 i1, T2 i2, T3 i3, T4 i4, GGE_enable_if_number_4(T1, T2, T3, T4)) GGE_noexcept : vec(_GGE_set_epu32((unsigned int)i1, (unsigned int)i2, (unsigned int)i3, (unsigned int)i4)) {}

		GGE_inline uint4(const uint1& i1, const uint1& i2, const uint1& i3, const uint1& i4) GGE_noexcept 
		{ vec = _GGE_blend_epi32(_GGE_shuf_xxxx_epi32(i1.vec, i3.vec), _GGE_shuf_xxxx_epi32(i2.vec, i4.vec), GGE_BLEND_MASK(1, 0, 1, 0)); }
		
		GGE_inline uint4(const uint2& i1, const uint1& i2, const uint1& i3) GGE_noexcept 
		{ vec = _GGE_blend_epi32(_GGE_shuf_xyxx_epi32(i1.vec, i2.vec), _GGE_perm_xxxx_epi32(i3.vec), GGE_BLEND_MASK(1, 1, 1, 0)); }

		GGE_inline uint4(const uint1& i1, const uint2& i2, const uint1& i3) GGE_noexcept 
		{ vec = _GGE_blend_epi32(_GGE_shuf_xxxx_epi32(i1.vec, i3.vec), _GGE_perm_xxyx_epi32(i2.vec), GGE_BLEND_MASK(1, 0, 0, 1)); }

		GGE_inline uint4(const uint1& i1, const uint1& i2, const uint2& i3) GGE_noexcept 
		{ vec = _GGE_blend_epi32(_GGE_shuf_xxxy_epi32(i1.vec, i3.vec), _GGE_perm_xxxx_epi32(i2.vec), GGE_BLEND_MASK(1, 0, 1, 1)); }

		GGE_inline uint4(const uint2& i1, const uint2& f2) GGE_noexcept { vec = _GGE_shuf_xyxy_epi32(i1.vec, f2.vec); }

		GGE_inline uint4(const uint1& i1, const uint3& i2) GGE_noexcept { vec = _GGE_blend_epi32(i1.vec, _GGE_perm_xxyz_epi32(i2.vec), GGE_BLEND_MASK(1, 0, 0, 0)); }
		GGE_inline uint4(const uint3& i1, const uint1& i2) GGE_noexcept { vec = _GGE_blend_epi32(i1.vec, _GGE_perm_xxxx_epi32(i2.vec), GGE_BLEND_MASK(1, 1, 1, 0)); }

		template<int X, int Y, int Z, int W>
		GGE_inline uint4(const uswizzle4<X, Y, Z, W>& s) GGE_noexcept
			: vec(GGE_uswizzle4_swizzle(X, Y, Z, W, 0, 1, 2, 3, s.vec)) {}

		GGE_inline uint4(const float4& f) GGE_noexcept;

		GGE_inline uint4& operator = (const uint4& i) GGE_noexcept { vec = i.vec; return *this; }

		GGE_inline uint4(uint4&& i) GGE_noexcept : vec(i.vec) {}
		GGE_inline uint4& operator = (uint4&& i) GGE_noexcept { vec = i.vec; return *this; }

		uint32_t& operator[](int N)
		{
			GGE_assert(N >= 0 && N <= 3);
			return u32[N];
		}

		const uint32_t& operator[](int N) const
		{
			GGE_assert(N >= 0 && N <= 3);
			return u32[N];
		}

		GGE_WARNING_ANONYMOUS_STRUCT_UNION_BEGIN
		union
		{
			n128u vec;
			uint32_t u32[4];
			#include "swizzle/vector_uint_x.h"
			#include "swizzle/vector_uint_y.h"
			#include "swizzle/vector_uint_z.h"
			#include "swizzle/vector_uint_w.h"
		};
		GGE_WARNING_ANONYMOUS_STRUCT_UNION_END
	};

	GGE_inline void store(uint32_t* dst, const uint1& src)
	{
		_GGE_store1_epu32(dst, src.vec);
	}

	GGE_inline void store(uint32_t* dst, const uint2& src)
	{
		_GGE_store2_epu32(dst, src.vec);
	}

	GGE_inline void store(uint32_t* dst, const uint3& src)
	{
		_GGE_store3_epu32(dst, src.vec);
	}

	GGE_inline void store(uint32_t* dst, const uint4& src)
	{
		_GGE_store4_epu32(dst, src.vec);
	}

	GGE_inline void load(uint1& dst, const uint32_t* src)
	{
		_GGE_load1_epu32(dst.vec, src);
	}

	GGE_inline void load(uint2& dst, const uint32_t* src)
	{
		_GGE_load2_epu32(dst.vec, src);
	}

	GGE_inline void load(uint3& dst, const uint32_t* src)
	{
		_GGE_load3_epu32(dst.vec, src);
	}

	GGE_inline void load(uint4& dst, const uint32_t* src)
	{
		_GGE_load4_epu32(dst.vec, src);
	}

	namespace interop
	{
		struct uint4
		{
			uint4() GGE_constructor_default;
			uint4(const GGE::uint4& f) { GGE::store(&x, f); }
			uint32_t x, y, z, w;
		};

		struct uint3
		{
			uint3() GGE_constructor_default;
			uint3(const GGE::uint3& f) { GGE::store(&x, f); }
			uint32_t x, y, z;
		};

		struct uint2
		{
			uint2() GGE_constructor_default;
			uint2(const GGE::uint2& f) { GGE::store(&x, f); }
			uint32_t x, y;
		};

		typedef uint32_t uint1;
	};

	static_assert(GGE_alignof(uint4) == 16, "Mismatched alignment");
};

GGE_WARNING_IMPLICIT_CONSTRUCTOR_END