#pragma once

#include <Core/Math/hlsl++/common.h>

GGE_WARNING_IMPLICIT_CONSTRUCTOR_BEGIN

GGE_module_export namespace GGE
{
	template<int X>
	struct GGE_nodiscard swizzle1
	{
		template<int A> friend struct swizzle1;

		// Cast

		GGE_inline operator float() const { return f32[X]; }

		// Return the address of this float in the same way we return the value
		GGE_inline float* operator&() { return &f32[X]; }

		#define GGE_swizzle1_swizzle(E, A, v) (_GGE_perm_ps(v, A == 0 ? E : 0, A == 1 ? E : 1, A == 2 ? E : 2, A == 3 ? E : 3))

		GGE_inline swizzle1& operator = (float f);

		template<int A>
		GGE_inline swizzle1& operator = (const swizzle1<A>& s);

		GGE_inline swizzle1& operator = (const swizzle1& s);

		GGE_inline swizzle1& operator = (const float1& f);

		union
		{
			n128 vec;
			float f32[4];
		};
	};

	template<int X, int Y>
	struct GGE_nodiscard swizzle2
	{
		#define GGE_swizzle2_swizzle(E, F, A, B, v) \
		    (_GGE_perm_ps(v, A == 0 ? E : B == 0 ? F : 0, \
		                        A == 1 ? E : B == 1 ? F : 1, \
		                        A == 2 ? E : B == 2 ? F : 2, \
		                        A == 3 ? E : B == 3 ? F : 3))

		#define GGE_swizzle2_blend(x, y) _GGE_blend_ps(x, y, GGE_COMPONENT_XY(X, Y))

		template<int A, int B>
		GGE_inline swizzle2& operator = (const swizzle2<A, B>& s);

		GGE_inline swizzle2& operator = (const swizzle2& s);

		GGE_inline swizzle2& operator = (const float2& f);

		n128 vec;
	};

	template<int X, int Y, int Z>
	struct GGE_nodiscard swizzle3
	{
		#define GGE_swizzle3_swizzle(E, F, G, A, B, C, v) \
		    (_GGE_perm_ps(v, A == 0 ? E : B == 0 ? F : C == 0 ? G : 0, \
		                        A == 1 ? E : B == 1 ? F : C == 1 ? G : 1, \
		                        A == 2 ? E : B == 2 ? F : C == 2 ? G : 2, \
		                        A == 3 ? E : B == 3 ? F : C == 3 ? G : 3))

		#define GGE_swizzle3_blend(x, y) _GGE_blend_ps(x, y, GGE_COMPONENT_XYZ(X, Y, Z))

		template<int A, int B, int C>
		GGE_inline swizzle3& operator = (const swizzle3<A, B, C>& s);

		GGE_inline swizzle3& operator = (const swizzle3& s);

		GGE_inline swizzle3& operator = (const float3& f);

		n128 vec;
	};

	template<int X, int Y, int Z, int W>
	struct GGE_nodiscard swizzle4
	{
		#define GGE_swizzle4_swizzle(E, F, G, H, A, B, C, D, v) \
		    (_GGE_perm_ps(v, A == 0 ? E : B == 0 ? F : C == 0 ? G : D == 0 ? H : 0, \
		                        A == 1 ? E : B == 1 ? F : C == 1 ? G : D == 1 ? H : 1, \
		                        A == 2 ? E : B == 2 ? F : C == 2 ? G : D == 2 ? H : 2, \
		                        A == 3 ? E : B == 3 ? F : C == 3 ? G : D == 3 ? H : 3))
		
		template<int A, int B, int C, int D>
		GGE_inline swizzle4& operator = (const swizzle4<A, B, C, D>& s);

		GGE_inline swizzle4& operator = (const float4& f);

		n128 vec;
	};

	struct GGE_nodiscard GGE_alignas(16) float1
	{
		GGE_inline float1() GGE_noexcept : vec(_GGE_setzero_ps()) {}
		GGE_inline float1(const float1& f) GGE_noexcept : vec(f.vec) {}
		explicit GGE_inline float1(n128 vec) GGE_noexcept : vec(vec) {}

		template<typename T>
		GGE_inline float1(T f, GGE_enable_if_number(T)) GGE_noexcept : vec(_GGE_set_ps(float(f), 0.0f, 0.0f, 0.0f)) {}

		template<int X> GGE_inline float1(const swizzle1<X>& s) GGE_noexcept
			: vec(GGE_swizzle1_swizzle(X, 0, s.vec)) {}

		GGE_inline float1(const int1& i) GGE_noexcept;

		GGE_inline float1(const uint1& i) GGE_noexcept;

		GGE_inline operator float() const { return f32[0]; }

		GGE_inline float1& operator = (const float1& f) GGE_noexcept { vec = f.vec; return *this; }

		GGE_inline float1(float1&& f) GGE_noexcept : vec(f.vec) {}
		GGE_inline float1& operator = (float1&& f) GGE_noexcept { vec = f.vec; return *this; }

		float& operator[](int N)
		{
			GGE_assert(N == 0);
			return f32[N];
		}

		const float& operator[](int N) const
		{
			GGE_assert(N == 0);
			return f32[N];
		}

		GGE_WARNING_ANONYMOUS_STRUCT_UNION_BEGIN
		union
		{
			n128 vec;
			float f32[1];
			#include "swizzle/vector_float_x.h"
		};
		GGE_WARNING_ANONYMOUS_STRUCT_UNION_END
	};

	struct GGE_nodiscard GGE_alignas(16) float2
	{
		GGE_inline float2() GGE_noexcept : vec(_GGE_setzero_ps()) {}
		GGE_inline float2(const float2& f) GGE_noexcept : vec(f.vec) {}
		explicit GGE_inline float2(n128 vec) GGE_noexcept : vec(vec) {}
		explicit GGE_inline float2(const float1& f) GGE_noexcept : vec(_GGE_perm_xxxx_ps(f.vec)) {}

		template<typename T>
		GGE_inline float2(T f, GGE_enable_if_number(T)) GGE_noexcept : vec(_GGE_set_ps(float(f), float(f), 0.0f, 0.0f)) {}

		template<typename T1, typename T2>
		GGE_inline float2(T1 f1, T2 f2, GGE_enable_if_number_2(T1, T2)) GGE_noexcept : vec(_GGE_set_ps(float(f1), float(f2), 0.0f, 0.0f)) {}

		GGE_inline float2(const float1& f1, const float1& f2) GGE_noexcept { vec = _GGE_blend_ps(f1.vec, _GGE_perm_xxxx_ps(f2.vec), GGE_BLEND_MASK(1, 0, 1, 1)); }

		template<int X, int Y> GGE_inline float2(const swizzle2<X, Y>& s) GGE_noexcept
			: vec(GGE_swizzle2_swizzle(X, Y, 0, 1, s.vec)) {}

		GGE_inline float2(const int2& i) GGE_noexcept;

		GGE_inline float2(const uint2& i) GGE_noexcept;

		GGE_inline float2& operator = (const float2& f) GGE_noexcept { vec = f.vec; return *this; }

		GGE_inline float2(float2&& f) GGE_noexcept : vec(f.vec) {}
		GGE_inline float2& operator = (float2&& f) GGE_noexcept { vec = f.vec; return *this; }

		float& operator[](int N)
		{
			GGE_assert(N >= 0 && N <= 1);
			return f32[N];
		}

		const float& operator[](int N) const
		{
			GGE_assert(N >= 0 && N <= 1);
			return f32[N];
		}

		GGE_WARNING_ANONYMOUS_STRUCT_UNION_BEGIN
		union
		{
			n128 vec;
			float f32[2];
			#include "swizzle/vector_float_x.h"
			#include "swizzle/vector_float_y.h"
		};
		GGE_WARNING_ANONYMOUS_STRUCT_UNION_END
	};

	struct GGE_nodiscard GGE_alignas(16) float3
	{
		GGE_inline float3() GGE_noexcept : vec(_GGE_setzero_ps()) {}
		GGE_inline float3(const float3& f) GGE_noexcept : vec(f.vec) {}
		explicit GGE_inline float3(n128 vec) GGE_noexcept : vec(vec) {}
		explicit GGE_inline float3(const float1& f) GGE_noexcept : vec(_GGE_perm_xxxx_ps(f.vec)) {}

		template<typename T>
		GGE_inline float3(T f, GGE_enable_if_number(T)) GGE_noexcept : vec(_GGE_set_ps(float(f), float(f), float(f), 0.0f)) {}

		template<typename T1, typename T2, typename T3>
		GGE_inline float3(T1 f1, T2 f2, T3 f3, GGE_enable_if_number_3(T1, T2, T3)) GGE_noexcept : vec(_GGE_set_ps(float(f1), float(f2), float(f3), 0.0f)) {}

		GGE_inline float3(const float1& f1, const float1& f2, const float1& f3) GGE_noexcept
		{ vec = _GGE_blend_ps(_GGE_shuf_xxxx_ps(f1.vec, f3.vec), _GGE_perm_xxxx_ps(f2.vec), GGE_BLEND_MASK(1, 0, 1, 0)); }

		GGE_inline float3(const float2& f1, const float1& f2) GGE_noexcept { vec = _GGE_shuf_xyxx_ps(f1.vec, f2.vec); }
		GGE_inline float3(const float1& f1, const float2& f2) GGE_noexcept { vec = _GGE_blend_ps(f1.vec, _GGE_perm_xxyx_ps(f2.vec), GGE_BLEND_MASK(1, 0, 0, 1)); }

		template<int X, int Y, int Z>
		GGE_inline float3(const swizzle3<X, Y, Z>& s) GGE_noexcept
			: vec(GGE_swizzle3_swizzle(X, Y, Z, 0, 1, 2, s.vec)) {}

		GGE_inline float3(const int3& i) GGE_noexcept;

		GGE_inline float3(const uint3& i) GGE_noexcept;

		GGE_inline float3& operator = (const float3& f) GGE_noexcept { vec = f.vec; return *this; }

		GGE_inline float3(float3&& f) GGE_noexcept : vec(f.vec) {}
		GGE_inline float3& operator = (float3&& f) GGE_noexcept { vec = f.vec; return *this; }

		float& operator[](int N)
		{
			GGE_assert(N >= 0 && N <= 2);
			return f32[N];
		}

		const float& operator[](int N) const
		{
			GGE_assert(N >= 0 && N <= 2);
			return f32[N];
		}

		GGE_WARNING_ANONYMOUS_STRUCT_UNION_BEGIN
		union
		{
			n128 vec;
			float f32[3];
			#include "swizzle/vector_float_x.h"
			#include "swizzle/vector_float_y.h"
			#include "swizzle/vector_float_z.h"
		};
		GGE_WARNING_ANONYMOUS_STRUCT_UNION_END
	};

	struct GGE_nodiscard GGE_alignas(16) float4
	{
		GGE_inline float4() GGE_noexcept : vec(_GGE_setzero_ps()) {}
		GGE_inline float4(const float4& f) GGE_noexcept : vec(f.vec) {}
		explicit GGE_inline float4(n128 vec) GGE_noexcept : vec(vec) {}
		explicit GGE_inline float4(const float1& f) GGE_noexcept : vec(_GGE_perm_xxxx_ps(f.vec)) {}

		template<typename T>
		float4(T f, GGE_enable_if_number(T)) GGE_noexcept : vec(_GGE_set1_ps(float(f))) {}

		template<typename T1, typename T2, typename T3, typename T4>
		GGE_inline float4(T1 f1, T2 f2, T3 f3, T4 f4, GGE_enable_if_number_4(T1, T2, T3, T4)) GGE_noexcept : vec(_GGE_set_ps(float(f1), float(f2), float(f3), float(f4))) {}

		GGE_inline float4(const float1& f1, const float1& f2, const float1& f3, const float1& f4) GGE_noexcept 
		{ vec = _GGE_blend_ps(_GGE_shuf_xxxx_ps(f1.vec, f3.vec), _GGE_shuf_xxxx_ps(f2.vec, f4.vec), GGE_BLEND_MASK(1, 0, 1, 0)); }

		GGE_inline float4(const float2& f1, const float1& f2, const float1& f3) GGE_noexcept
		{ vec = _GGE_blend_ps(_GGE_shuf_xyxx_ps(f1.vec, f2.vec), _GGE_perm_xxxx_ps(f3.vec), GGE_BLEND_MASK(1, 1, 1, 0)); }

		GGE_inline float4(const float1& f1, const float2& f2, const float1& f3) GGE_noexcept
		{ vec = _GGE_blend_ps(_GGE_shuf_xxxx_ps(f1.vec, f3.vec), _GGE_perm_xxyx_ps(f2.vec), GGE_BLEND_MASK(1, 0, 0, 1)); }

		GGE_inline float4(const float1& f1, const float1& f2, const float2& f3) GGE_noexcept
		{ vec = _GGE_blend_ps(_GGE_shuf_xxxy_ps(f1.vec, f3.vec), _GGE_perm_xxxx_ps(f2.vec), GGE_BLEND_MASK(1, 0, 1, 1)); }

		GGE_inline float4(const float2& f1, const float2& f2) GGE_noexcept { vec = _GGE_shuf_xyxy_ps(f1.vec, f2.vec); }

		GGE_inline float4(const float1& f1, const float3& f2) GGE_noexcept { vec = _GGE_blend_ps(f1.vec, _GGE_perm_xxyz_ps(f2.vec), GGE_BLEND_MASK(1, 0, 0, 0)); }
		GGE_inline float4(const float3& f1, const float1& f2) GGE_noexcept { vec = _GGE_blend_ps(f1.vec, _GGE_perm_xxxx_ps(f2.vec), GGE_BLEND_MASK(1, 1, 1, 0)); }

		template<int X, int Y, int Z, int W>
		GGE_inline float4(const swizzle4<X, Y, Z, W>& s) GGE_noexcept
			: vec(GGE_swizzle4_swizzle(X, Y, Z, W, 0, 1, 2, 3, s.vec)) {}

		GGE_inline float4(const int4& i) GGE_noexcept;

		GGE_inline float4(const uint4& i) GGE_noexcept;

		GGE_inline float4& operator = (const float4& f) GGE_noexcept { vec = f.vec; return *this; }

		GGE_inline float4(float4&& f) GGE_noexcept : vec(f.vec) {}
		GGE_inline float4& operator = (float4&& f) GGE_noexcept { vec = f.vec; return *this; }

		float& operator[](int N)
		{
			GGE_assert(N >= 0 && N <= 3);
			return f32[N];
		}

		const float& operator[](int N) const
		{
			GGE_assert(N >= 0 && N <= 3);
			return f32[N];
		}

		GGE_WARNING_ANONYMOUS_STRUCT_UNION_BEGIN
		union
		{
			n128 vec;
			float f32[4];
			#include "swizzle/vector_float_x.h"
			#include "swizzle/vector_float_y.h"
			#include "swizzle/vector_float_z.h"
			#include "swizzle/vector_float_w.h"
		};
		GGE_WARNING_ANONYMOUS_STRUCT_UNION_END
	};

	GGE_inline void store(float* dst, const float1& src)
	{
		_GGE_store1_ps(dst, src.vec);
	}

	GGE_inline void store(float* dst, const float2& src)
	{
		_GGE_store2_ps(dst, src.vec);
	}

	GGE_inline void store(float* dst, const float3& src)
	{
		_GGE_store3_ps(dst, src.vec);
	}

	GGE_inline void store(float* dst, const float4& src)
	{
		_GGE_store4_ps(dst, src.vec);
	}

	GGE_inline void load(float1& dst, const float* src)
	{
		_GGE_load1_ps(dst.vec, src);
	}

	GGE_inline void load(float2& dst, const float* src)
	{
		_GGE_load2_ps(dst.vec, src);
	}

	GGE_inline void load(float3& dst, const float* src)
	{
		_GGE_load3_ps(dst.vec, src);
	}

	GGE_inline void load(float4& dst, const float* src)
	{
		_GGE_load4_ps(dst.vec, src);
	}

	namespace interop
	{
		struct float4
		{
			float4() GGE_constructor_default;
			float4(const GGE::float4& f) { GGE::store(&x, f); }
			float x, y, z, w;
		};

		struct float3
		{
			float3() GGE_constructor_default;
			float3(const GGE::float3& f) { GGE::store(&x, f); }
			float x, y, z;
		};

		struct float2
		{
			float2() GGE_constructor_default;
			float2(const GGE::float2& f) { GGE::store(&x, f); }
			float x, y;
		};

		typedef float float1;
	};

	static_assert(GGE_alignof(float4) == 16, "Mismatched alignment");
};

GGE_WARNING_IMPLICIT_CONSTRUCTOR_END