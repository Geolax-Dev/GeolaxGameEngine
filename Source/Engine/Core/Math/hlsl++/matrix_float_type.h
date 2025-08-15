#pragma once

#include <Core/Math/hlsl++/common.h>

#include <Core/Math/hlsl++/vector_float.h>

#include <Core/Math/hlsl++/transform/common.h>

//--------------//
// Float Matrix //
//--------------//

GGE_module_export namespace GGE
{
	struct GGE_nodiscard float1x1
	{
		GGE_inline float1x1() GGE_noexcept : vec(_GGE_setzero_ps()) {}
		GGE_inline float1x1(const float1x1& m) GGE_noexcept : vec(m.vec) {}

		explicit GGE_inline float1x1(n128 vec) GGE_noexcept : vec(vec) {}

		template<typename T>
		explicit GGE_inline float1x1(T f, GGE_enable_if_number(T)) GGE_noexcept : vec(_GGE_set_ps(float(f), 0.0f, 0.0f, 0.0f)) {}

		explicit GGE_inline float1x1(const float1& f) GGE_noexcept : vec(f.vec) {}

		explicit GGE_inline float1x1(const float2x2& m) GGE_noexcept;

		GGE_inline float1x1& operator = (const float1x1& m) GGE_noexcept { vec = m.vec; return *this; }

		GGE_inline float1x1(float1x1&& m) GGE_noexcept : vec(m.vec) {}
		GGE_inline float1x1& operator = (float1x1&& m) GGE_noexcept { vec = m.vec; return *this; }
    
		GGE_WARNING_ANONYMOUS_STRUCT_UNION_BEGIN
		union
		{
			n128 vec;
			float f32[4];
			#include "swizzle/matrix_row0_1.h"
		};
		GGE_WARNING_ANONYMOUS_STRUCT_UNION_END
	};

	struct GGE_nodiscard float1x2
	{
		GGE_inline float1x2() GGE_noexcept : vec(_GGE_setzero_ps()) {}
		GGE_inline float1x2(const float1x2& m) GGE_noexcept : vec(m.vec) {}

		explicit GGE_inline float1x2(n128 vec) GGE_noexcept : vec(vec) {}

		template<typename T>
		explicit GGE_inline float1x2(T f, GGE_enable_if_number(T)) GGE_noexcept : vec(_GGE_set_ps(float(f), float(f), 0.0f, 0.0f)) {}

		explicit GGE_inline float1x2(float f0, float f1) GGE_noexcept : vec(_GGE_set_ps(f0, f1, 0.0f, 0.0f)) {}

		GGE_inline float1x2(const float2& f) GGE_noexcept : vec(f.vec) {}

		GGE_inline float1x2& operator = (const float1x2& m) GGE_noexcept { vec = m.vec; return *this; }

		GGE_inline float1x2(float1x2&& m) GGE_noexcept : vec(m.vec) {}
		GGE_inline float1x2& operator = (float1x2&& m) GGE_noexcept { vec = m.vec; return *this; }

		GGE_WARNING_ANONYMOUS_STRUCT_UNION_BEGIN
		union
		{
			n128 vec;
			float f32[4];
			#include "swizzle/matrix_row0_2.h"
		};
		GGE_WARNING_ANONYMOUS_STRUCT_UNION_END
	};

	struct GGE_nodiscard float2x1
	{
		GGE_inline float2x1() GGE_noexcept : vec(_GGE_setzero_ps()) {}
		GGE_inline float2x1(const float2x1& m) GGE_noexcept : vec(m.vec) {}

		explicit GGE_inline float2x1(n128 vec) GGE_noexcept : vec(vec) {}

		template<typename T>
		explicit GGE_inline float2x1(T f, GGE_enable_if_number(T)) GGE_noexcept : vec(_GGE_set_ps(float(f), float(f), 0.0f, 0.0f)) {}

		explicit GGE_inline float2x1(float f0, float f1) GGE_noexcept : vec(_GGE_set_ps(f0, f1, 0.0f, 0.0f)) {}

		GGE_inline float2x1(const float2& f) GGE_noexcept : vec(f.vec) {}

		GGE_inline float2x1& operator = (const float2x1& m) GGE_noexcept { vec = m.vec; return *this; }

		GGE_inline float2x1(float2x1&& m) GGE_noexcept : vec(m.vec) {}
		GGE_inline float2x1& operator = (float2x1&& m) GGE_noexcept { vec = m.vec; return *this; }

		union
		{
			n128 vec;
			float f32[4];
		};
	};

	struct GGE_nodiscard float1x3
	{
		GGE_inline float1x3() GGE_noexcept : vec(_GGE_setzero_ps()) {}
		GGE_inline float1x3(const float1x3& m) GGE_noexcept : vec(m.vec) {}

		explicit GGE_inline float1x3(n128 vec) GGE_noexcept : vec(vec) {}

		template<typename T>
		explicit GGE_inline float1x3(T f, GGE_enable_if_number(T)) GGE_noexcept : vec(_GGE_set_ps(float(f), float(f), float(f), 0.0f)) {}

		explicit GGE_inline float1x3(float f0, float f1, float f2) GGE_noexcept : vec(_GGE_set_ps(f0, f1, f2, 0.0f)) {}

		GGE_inline float1x3(const float3& f) GGE_noexcept : vec(f.vec) {}

		GGE_inline float1x3& operator = (const float1x3& m) GGE_noexcept { vec = m.vec; return *this; }

		GGE_inline float1x3(float1x3&& m) GGE_noexcept : vec(m.vec) {}
		GGE_inline float1x3& operator = (float1x3&& m) GGE_noexcept { vec = m.vec; return *this; }

		union
		{
			n128 vec;
			float f32[4];
		};
	};

	struct GGE_nodiscard float3x1
	{
		GGE_inline float3x1() GGE_noexcept : vec(_GGE_setzero_ps()) {}
		GGE_inline float3x1(const float3x1& m) GGE_noexcept : vec(m.vec) {}

		explicit GGE_inline float3x1(n128 vec) GGE_noexcept : vec(vec) {}

		template<typename T>
		explicit GGE_inline float3x1(T f, GGE_enable_if_number(T)) GGE_noexcept : vec(_GGE_set_ps(float(f), float(f), float(f), 0.0f)) {}

		explicit GGE_inline float3x1(float f0, float f1, float f2) GGE_noexcept : vec(_GGE_set_ps(f0, f1, f2, 0.0f)) {}

		GGE_inline float3x1(const float3& f) GGE_noexcept : vec(f.vec) {}

		GGE_inline float3x1& operator = (const float3x1& m) GGE_noexcept { vec = m.vec; return *this; }

		GGE_inline float3x1(float3x1&& m) GGE_noexcept : vec(m.vec) {}
		GGE_inline float3x1& operator = (float3x1&& m) GGE_noexcept { vec = m.vec; return *this; }

		union
		{
			n128 vec;
			float f32[4];
		};
	};

	struct GGE_nodiscard float1x4
	{
		GGE_inline float1x4() GGE_noexcept : vec(_GGE_setzero_ps()) {}
		GGE_inline float1x4(const float1x4& m) GGE_noexcept : vec(m.vec) {}

		explicit GGE_inline float1x4(n128 vec) GGE_noexcept : vec(vec) {}

		template<typename T>
		explicit GGE_inline float1x4(T f, GGE_enable_if_number(T)) GGE_noexcept : vec(_GGE_set1_ps(float(f))) {}

		explicit GGE_inline float1x4(float f0, float f1, float f2, float f3) GGE_noexcept : vec(_GGE_set_ps(f0, f1, f2, f3)) {}

		GGE_inline float1x4(const float4& f) GGE_noexcept : vec(f.vec) {}

		GGE_inline float1x4& operator = (const float1x4& m) GGE_noexcept { vec = m.vec; return *this; }

		GGE_inline float1x4(float1x4&& m) GGE_noexcept : vec(m.vec) {}
		GGE_inline float1x4& operator = (float1x4&& m) GGE_noexcept { vec = m.vec; return *this; }

		union
		{
			n128 vec;
			float f32[4];
		};
	};

	struct GGE_nodiscard float4x1
	{
		GGE_inline float4x1() GGE_noexcept : vec(_GGE_setzero_ps()) {}
		GGE_inline float4x1(const float4x1& m) GGE_noexcept : vec(m.vec) {}

		explicit GGE_inline float4x1(n128 vec) GGE_noexcept : vec(vec) {}

		template<typename T>
		explicit GGE_inline float4x1(T f, GGE_enable_if_number(T)) GGE_noexcept : vec(_GGE_set1_ps(float(f))) {}

		explicit GGE_inline float4x1(float f0, float f1, float f2, float f3) GGE_noexcept : vec(_GGE_set_ps(f0, f1, f2, f3)) {}

		GGE_inline float4x1(const float4& f) GGE_noexcept : vec(f.vec) {}

		GGE_inline float4x1& operator = (const float4x1& m) GGE_noexcept { vec = m.vec; return *this; }

		GGE_inline float4x1(float4x1&& m) GGE_noexcept : vec(m.vec) {}
		GGE_inline float4x1& operator = (float4x1&& m) GGE_noexcept { vec = m.vec; return *this; }

		union
		{
			n128 vec;
			float f32[4];
		};
	};

	struct GGE_nodiscard float2x2
	{
		GGE_inline float2x2() GGE_noexcept : vec(_GGE_setzero_ps()) {}
		GGE_inline float2x2(const float2x2& m) GGE_noexcept : vec(m.vec) {}

		explicit GGE_inline float2x2(n128 vec) GGE_noexcept : vec(vec) {}

		explicit GGE_inline float2x2(
		    float f00, float f01,
		    float f10, float f11) GGE_noexcept : vec(_GGE_set_ps(f00, f01, f10, f11)) {}

		explicit GGE_inline float2x2(float f) GGE_noexcept : vec(_GGE_set1_ps(f)) {}

		explicit GGE_inline float2x2(const float3x3& m) GGE_noexcept;

		GGE_inline float2x2(const float2& f1, const float2& f2) GGE_noexcept : vec(_GGE_shuf_xyxy_ps(f1.vec, f2.vec)) {}

		GGE_inline float2x2& operator = (const float2x2& m) GGE_noexcept { vec = m.vec; return *this; }

		GGE_inline float2x2(float2x2&& m) GGE_noexcept : vec(m.vec) {}
		GGE_inline float2x2& operator = (float2x2&& m) GGE_noexcept { vec = m.vec; return *this; }

		#include <Core/Math/hlsl++/transform/float2x2.h>

		union
		{
			n128 vec; // Store it in a single vector to save memory
			float f32[4];
		};
	};

	struct GGE_nodiscard float2x3
	{
		GGE_inline float2x3() GGE_noexcept : vec0(_GGE_setzero_ps()), vec1(_GGE_setzero_ps()) {}
		GGE_inline float2x3(const float2x3& m) GGE_noexcept : vec0(m.vec0), vec1(m.vec1) {}

		explicit GGE_inline float2x3(n128 vec0, n128 vec1) GGE_noexcept : vec0(vec0), vec1(vec1) {}

		explicit GGE_inline float2x3(float f) GGE_noexcept : vec0(_GGE_set_ps(f, f, f, 0.0f)), vec1(_GGE_set_ps(f, f, f, 0.0f)) {}

		explicit GGE_inline float2x3(
		    float f00, float f01, float f02,
		    float f10, float f11, float f12)
		    GGE_noexcept : vec0(_GGE_set_ps(f00, f01, f02, 0.0f)), vec1(_GGE_set_ps(f10, f11, f12, 0.0f)) {}

		// Construct matrix with two float3 interpreted as rows
		GGE_inline float2x3(const float3& f1, const float3& f2) GGE_noexcept : vec0(f1.vec), vec1(f2.vec) {}

		GGE_inline float2x3& operator = (const float2x3& m) GGE_noexcept { vec0 = m.vec0; vec1 = m.vec1; return *this; }

		GGE_inline float2x3(float2x3&& m) GGE_noexcept : vec0(m.vec0), vec1(m.vec1) {}
		GGE_inline float2x3& operator = (float2x3&& m) GGE_noexcept { vec0 = m.vec0; vec1 = m.vec1; return *this; }

		union
		{
			n128 vec0;
			float f32_0[4];
		};

		union
		{
			n128 vec1;
			float f32_1[4];
		};
	};

	struct GGE_nodiscard float3x2
	{
		GGE_inline float3x2() GGE_noexcept : vec0(_GGE_setzero_ps()), vec1(_GGE_setzero_ps()) {}
		GGE_inline float3x2(const float3x2& m) GGE_noexcept : vec0(m.vec0), vec1(m.vec1) {}

		explicit GGE_inline float3x2(n128 vec0, n128 vec1) GGE_noexcept : vec0(vec0), vec1(vec1) {}

		explicit GGE_inline float3x2(float f) GGE_noexcept : vec0(_GGE_set_ps(f, f, f, 0.0f)), vec1(_GGE_set_ps(f, f, f, 0.0f)) {}

		explicit GGE_inline float3x2(
		    float f00, float f01,
		    float f10, float f11,
		    float f20, float f21)
		    GGE_noexcept : vec0(_GGE_set_ps(f00, f10, f20, 0.0f)), vec1(_GGE_set_ps(f01, f11, f21, 0.0f)) {}

		// Construct matrix with two float3 interpreted as columns
		GGE_inline float3x2(const float3& f1, const float3& f2) GGE_noexcept : vec0(f1.vec), vec1(f2.vec) {}

		GGE_inline float3x2& operator = (const float3x2& m) GGE_noexcept { vec0 = m.vec0; vec1 = m.vec1; return *this; }

		GGE_inline float3x2(float3x2&& m) GGE_noexcept : vec0(m.vec0), vec1(m.vec1) {}
		GGE_inline float3x2& operator = (float3x2&& m) GGE_noexcept { vec0 = m.vec0; vec1 = m.vec1; return *this; }

		union
		{
			n128 vec0;
			float f32_0[4];
		};

		union
		{
			n128 vec1;
			float f32_1[4];
		};
	};

	struct GGE_nodiscard float2x4
	{
		GGE_inline float2x4() GGE_noexcept : vec0(_GGE_setzero_ps()), vec1(_GGE_setzero_ps()) {}
		GGE_inline float2x4(const float2x4& m) GGE_noexcept : vec0(m.vec0), vec1(m.vec1) {}

		explicit GGE_inline float2x4(n128 vec0, n128 vec1) GGE_noexcept : vec0(vec0), vec1(vec1) {}

		explicit GGE_inline float2x4(
		    float f00, float f01, float f02, float f03,
		    float f10, float f11, float f12, float f13)
		    GGE_noexcept : vec0(_GGE_set_ps(f00, f01, f02, f03)), vec1(_GGE_set_ps(f10, f11, f12, f13)) {}

		explicit GGE_inline float2x4(float f) GGE_noexcept : vec0(_GGE_set_ps(f, f, f, f)), vec1(_GGE_set_ps(f, f, f, f)) {}

		// Construct matrix with two float3 interpreted as rows
		GGE_inline float2x4(const float4& f1, const float4& f2) GGE_noexcept : vec0(f1.vec), vec1(f2.vec) {}

		GGE_inline float2x4& operator = (const float2x4& m) GGE_noexcept { vec0 = m.vec0; vec1 = m.vec1; return *this; }

		GGE_inline float2x4(float2x4&& m) GGE_noexcept : vec0(m.vec0), vec1(m.vec1) {}
		GGE_inline float2x4& operator = (float2x4&& m) GGE_noexcept { vec0 = m.vec0; vec1 = m.vec1; return *this; }

		union
		{
			n128 vec0;
			float f32_0[4];
		};

		union
		{
			n128 vec1;
			float f32_1[4];
		};
	};

	struct GGE_nodiscard float4x2
	{
		GGE_inline float4x2() GGE_noexcept : vec0(_GGE_setzero_ps()), vec1(_GGE_setzero_ps()) {}
		GGE_inline float4x2(const float4x2& m) GGE_noexcept : vec0(m.vec0), vec1(m.vec1) {}

		explicit GGE_inline float4x2(n128 vec0, n128 vec1) GGE_noexcept : vec0(vec0), vec1(vec1) {}

		explicit GGE_inline float4x2(
		    float f00, float f01,
		    float f10, float f11,
		    float f20, float f21,
		    float f30, float f31) 
		    GGE_noexcept : vec0(_GGE_set_ps(f00, f10, f20, f30)), vec1(_GGE_set_ps(f01, f11, f21, f31)) {}

		explicit GGE_inline float4x2(float f) GGE_noexcept : vec0(_GGE_set_ps(f, f, f, f)), vec1(_GGE_set_ps(f, f, f, f)) {}

		// Construct matrix with two float3 interpreted as columns
		GGE_inline float4x2(const float4& f1, const float4& f2) GGE_noexcept : vec0(f1.vec), vec1(f2.vec) {}

		GGE_inline float4x2& operator = (const float4x2& m) GGE_noexcept { vec0 = m.vec0; vec1 = m.vec1; return *this; }

		GGE_inline float4x2(float4x2&& m) GGE_noexcept : vec0(m.vec0), vec1(m.vec1) {}
		GGE_inline float4x2& operator = (float4x2&& m) GGE_noexcept { vec0 = m.vec0; vec1 = m.vec1; return *this; }

		union
		{
			n128 vec0;
			float f32_0[4];
		};

		union
		{
			n128 vec1;
			float f32_1[4];
		};
	};

	struct quaternion;

	struct GGE_nodiscard float3x3
	{
		GGE_inline float3x3() GGE_noexcept : vec0(_GGE_setzero_ps()), vec1(_GGE_setzero_ps()), vec2(_GGE_setzero_ps()) {}
		GGE_inline float3x3(const float3x3& m) GGE_noexcept : vec0(m.vec0), vec1(m.vec1), vec2(m.vec2) {}

		explicit GGE_inline float3x3(const n128 vec0, const n128 vec1, const n128 vec2) GGE_noexcept : vec0(vec0), vec1(vec1), vec2(vec2) {}

		explicit GGE_inline float3x3(
		    float f00, float f01, float f02,
		    float f10, float f11, float f12,
		    float f20, float f21, float f22)
		    GGE_noexcept : vec0(_GGE_set_ps(f00, f01, f02, 0.0f)), vec1(_GGE_set_ps(f10, f11, f12, 0.0f)), vec2(_GGE_set_ps(f20, f21, f22, 0.0f)) {}

		explicit GGE_inline float3x3(const quaternion& q) GGE_noexcept;
		explicit GGE_inline float3x3(const float4x4& m) GGE_noexcept;

		explicit GGE_inline float3x3(float f) GGE_noexcept : vec0(_GGE_set1_ps(f)), vec1(_GGE_set1_ps(f)), vec2(_GGE_set1_ps(f)) {}

		GGE_inline float3x3(const float3& f1, const float3& f2, const float3& f3) GGE_noexcept : vec0(f1.vec), vec1(f2.vec), vec2(f3.vec) {}

		GGE_inline float3x3& operator = (const float3x3& m) GGE_noexcept { vec0 = m.vec0; vec1 = m.vec1; vec2 = m.vec2; return *this; }

		GGE_inline float3x3(float3x3&& m) GGE_noexcept : vec0(m.vec0), vec1(m.vec1), vec2(m.vec2) {}
		GGE_inline float3x3& operator = (float3x3&& m) GGE_noexcept { vec0 = m.vec0; vec1 = m.vec1; vec2 = m.vec2; return *this; }

		static const float3x3& identity() { static const float3x3 iden = float3x3(1, 0, 0, 0, 1, 0, 0, 0, 1); return iden; }

		#include <Core/Math/hlsl++/transform/float3x3.h>

		float3& operator[](int N)
		{
			GGE_assert(N >= 0 && N <= 2);
			return *(&reinterpret_cast<float3&>(vec0) + N);
		}

		const float3& operator[](int N) const
		{
			GGE_assert(N >= 0 && N <= 2);
			return *(&reinterpret_cast<const float3&>(vec0) + N);
		}

		GGE_WARNING_ANONYMOUS_STRUCT_UNION_BEGIN
		union
		{
			n128 vec0;
			float f32_0[3];
			#include "swizzle/matrix_row0_1.h"
			#include "swizzle/matrix_row0_2.h"
			#include "swizzle/matrix_row0_3.h"
		};

		union
		{
			n128 vec1;
			float f32_1[3];
			#include "swizzle/matrix_row1_1.h"
			#include "swizzle/matrix_row1_2.h"
			#include "swizzle/matrix_row1_3.h"
		};

		union
		{
			n128 vec2;
			float f32_2[3];
			#include "swizzle/matrix_row2_1.h"
			#include "swizzle/matrix_row2_2.h"
			#include "swizzle/matrix_row2_3.h"
		};
		GGE_WARNING_ANONYMOUS_STRUCT_UNION_END
	};

	struct GGE_nodiscard float3x4
	{
		GGE_inline float3x4() GGE_noexcept : vec0(_GGE_setzero_ps()), vec1(_GGE_setzero_ps()), vec2(_GGE_setzero_ps()) {}
		GGE_inline float3x4(const float3x4& m) GGE_noexcept : vec0(m.vec0), vec1(m.vec1), vec2(m.vec2) {}

		explicit GGE_inline float3x4(n128 vec0, n128 vec1, n128 vec2) GGE_noexcept : vec0(vec0), vec1(vec1), vec2(vec2) {}

		explicit GGE_inline float3x4(
		    float f00, float f01, float f02, float f03,
		    float f10, float f11, float f12, float f13,
		    float f20, float f21, float f22, float f23) 
		    GGE_noexcept : vec0(_GGE_set_ps(f00, f01, f02, f03)), vec1(_GGE_set_ps(f10, f11, f12, f13)), vec2(_GGE_set_ps(f20, f21, f22, f23)) {}

		explicit GGE_inline float3x4(float f) GGE_noexcept : vec0(_GGE_set1_ps(f)), vec1(_GGE_set1_ps(f)), vec2(_GGE_set1_ps(f)) {}

		// Construct matrix with two float3 interpreted as rows
		GGE_inline float3x4(const float4& f1, const float4& f2, const float4& f3) GGE_noexcept : vec0(f1.vec), vec1(f2.vec), vec2(f3.vec) {}

		GGE_inline float3x4& operator = (const float3x4& m) GGE_noexcept { vec0 = m.vec0; vec1 = m.vec1; vec2 = m.vec2; return *this; }

		GGE_inline float3x4(float3x4&& m) GGE_noexcept : vec0(m.vec0), vec1(m.vec1), vec2(m.vec2) {}
		GGE_inline float3x4& operator = (float3x4&& m) GGE_noexcept { vec0 = m.vec0; vec1 = m.vec1; vec2 = m.vec2; return *this; }

		union
		{
			n128 vec0;
			float f32_0[4];
		};

		union
		{
			n128 vec1;
			float f32_1[4];
		};

		union
		{
			n128 vec2;
			float f32_2[4];
		};
	};

	struct GGE_nodiscard float4x3
	{
		GGE_inline float4x3() GGE_noexcept : vec0(_GGE_setzero_ps()), vec1(_GGE_setzero_ps()), vec2(_GGE_setzero_ps()) {}
		GGE_inline float4x3(const float4x3& m) GGE_noexcept : vec0(m.vec0), vec1(m.vec1), vec2(m.vec2) {}

		explicit GGE_inline float4x3(n128 vec0, n128 vec1, n128 vec2) GGE_noexcept : vec0(vec0), vec1(vec1), vec2(vec2) {}

		explicit GGE_inline float4x3(
		    float f00, float f01, float f02,
		    float f10, float f11, float f12,
		    float f20, float f21, float f22,
		    float f30, float f31, float f32)
		    GGE_noexcept : vec0(_GGE_set_ps(f00, f10, f20, f30)), vec1(_GGE_set_ps(f01, f11, f21, f31)), vec2(_GGE_set_ps(f02, f12, f22, f32)) {}

		explicit GGE_inline float4x3(float f) GGE_noexcept : vec0(_GGE_set1_ps(f)), vec1(_GGE_set1_ps(f)), vec2(_GGE_set1_ps(f)) {}
		
		// Construct matrix with two float3 interpreted as columns
		GGE_inline float4x3(const float4& f1, const float4& f2, const float4& f3) GGE_noexcept : vec0(f1.vec), vec1(f2.vec), vec2(f3.vec) {}

		GGE_inline float4x3& operator = (const float4x3& m) GGE_noexcept { vec0 = m.vec0; vec1 = m.vec1; vec2 = m.vec2; return *this; }

		GGE_inline float4x3(float4x3&& m) GGE_noexcept : vec0(m.vec0), vec1(m.vec1), vec2(m.vec2) {}
		GGE_inline float4x3& operator = (float4x3&& m) GGE_noexcept { vec0 = m.vec0; vec1 = m.vec1; vec2 = m.vec2; return *this; }

		union
		{
			n128 vec0;
			float f32_0[4];
		};

		union
		{
			n128 vec1;
			float f32_1[4];
		};

		union
		{
			n128 vec2;
			float f32_2[4];
		};
	};

	float4x4 transpose(const float4x4& m);

	struct GGE_nodiscard float4x4
	{
#if defined(GGE_SIMD_REGISTER_512)

		GGE_inline float4x4() GGE_noexcept : vec(_GGE512_setzero_ps()) {}
		GGE_inline float4x4(const float4x4& m) GGE_noexcept : vec(m.vec) {}
		explicit GGE_inline float4x4(const n512& vec) GGE_noexcept : vec(vec) {}

		explicit GGE_inline float4x4(
			float f00, float f01, float f02, float f03,
			float f10, float f11, float f12, float f13,
			float f20, float f21, float f22, float f23,
			float f30, float f31, float f32, float f33)
			GGE_noexcept : vec(_GGE512_set_ps(f00, f01, f02, f03, f10, f11, f12, f13, f20, f21, f22, f23, f30, f31, f32, f33)) {}

		explicit GGE_inline float4x4(float f) GGE_noexcept : vec(_GGE512_set1_ps(f)) {}

		GGE_inline float4x4(const float4& f1, const float4& f2, const float4& f3, const float4& f4)
			GGE_noexcept : vec(_GGE512_set128_ps(f1.vec, f2.vec, f3.vec, f4.vec)) {}

		GGE_inline float4x4& operator = (const float4x4& m) GGE_noexcept { vec = m.vec; return *this; }

		GGE_inline float4x4(float4x4&& m) GGE_noexcept : vec(m.vec) {}
		GGE_inline float4x4& operator = (float4x4&& m) GGE_noexcept { vec = m.vec; return *this; }

		GGE_inline void build(const float3x3& m, const float4& v) GGE_noexcept
		{
			vec = _GGE512_and_ps(_GGE512_set128_ps(m.vec0, m.vec1, m.vec2, v.vec),
				_GGE512_set_ps(fffMask._f32, fffMask._f32, fffMask._f32, 0.0f, fffMask._f32, fffMask._f32, fffMask._f32, 0.0f, 
								  fffMask._f32, fffMask._f32, fffMask._f32, 0.0f, fffMask._f32, fffMask._f32, fffMask._f32, 0.0f));
		}

		GGE_inline void build(const float3x4& m, const float4& v) GGE_noexcept
		{
			vec = _GGE512_set128_ps(m.vec0, m.vec1, m.vec2, v.vec);
		}

		GGE_inline void build(const float4x3& m, const float4& v) GGE_noexcept
		{
			vec = _GGE512_set128_ps(m.vec0, m.vec1, m.vec2, v.vec);
			*this = transpose(*this); // Copy over as rows, then transpose
		}

		float4& operator[](int N)
		{
			GGE_assert(N >= 0 && N <= 3);
			return *(&row + N);
		}

		const float4& operator[](int N) const
		{
			GGE_assert(N >= 0 && N <= 3);
			return *(&row + N);
		}

		union
		{
			n512 vec;
			float f32_512[16];
			float4 row;

			GGE_WARNING_ANONYMOUS_STRUCT_UNION_BEGIN
			struct
			{
				union 
				{
					#include "swizzle/matrix_row0_1.h"
					#include "swizzle/matrix_row0_2.h"
					#include "swizzle/matrix_row0_3.h"
					#include "swizzle/matrix_row0_4.h"
				};
			
				union
				{
					#include "swizzle/matrix_row1_1.h"
					#include "swizzle/matrix_row1_2.h"
					#include "swizzle/matrix_row1_3.h"
					#include "swizzle/matrix_row1_4.h"
				};

				union
				{
					#include "swizzle/matrix_row2_1.h"
					#include "swizzle/matrix_row2_2.h"
					#include "swizzle/matrix_row2_3.h"
					#include "swizzle/matrix_row2_4.h"
				};

				union
				{
					#include "swizzle/matrix_row3_1.h"
					#include "swizzle/matrix_row3_2.h"
					#include "swizzle/matrix_row3_3.h"
					#include "swizzle/matrix_row3_4.h"
				};
			};
			GGE_WARNING_ANONYMOUS_STRUCT_UNION_END
		};

#elif defined(GGE_SIMD_REGISTER_256)

		GGE_inline float4x4() GGE_noexcept : vec0(_GGE256_setzero_ps()), vec1(_GGE256_setzero_ps()) {}
		GGE_inline float4x4(const float4x4& m) GGE_noexcept : vec0(m.vec0), vec1(m.vec1) {}

		explicit GGE_inline float4x4(const n256& vec0, const n256& vec1) GGE_noexcept : vec0(vec0), vec1(vec1) {}

		explicit GGE_inline float4x4(
		    float f00, float f01, float f02, float f03,
		    float f10, float f11, float f12, float f13,
		    float f20, float f21, float f22, float f23,
		    float f30, float f31, float f32, float f33)
		    GGE_noexcept : vec0(_GGE256_set_ps(f00, f01, f02, f03, f10, f11, f12, f13)), vec1(_GGE256_set_ps(f20, f21, f22, f23, f30, f31, f32, f33)) {}

		explicit GGE_inline float4x4(float f) GGE_noexcept : vec0(_GGE256_set1_ps(f)), vec1(_GGE256_set1_ps(f)) {}

		GGE_inline float4x4(const float4& f1, const float4& f2, const float4& f3, const float4& f4) 
			GGE_noexcept : vec0(_GGE256_set128_ps(f1.vec, f2.vec)), vec1(_GGE256_set128_ps(f3.vec, f4.vec)) {}

		GGE_inline float4x4& operator = (const float4x4& m) GGE_noexcept { vec0 = m.vec0; vec1 = m.vec1; return *this; }

		GGE_inline float4x4(float4x4&& m) GGE_noexcept : vec0(m.vec0), vec1(m.vec1) {}
		GGE_inline float4x4& operator = (float4x4&& m) GGE_noexcept { vec0 = m.vec0; vec1 = m.vec1; return *this; }

		GGE_inline void build(const float3x3& m, const float4& v) GGE_noexcept
		{
			vec0 = _GGE256_and_ps(
				_GGE256_set128_ps(m.vec0, m.vec1),
				_GGE256_set_ps(fffMask._f32, fffMask._f32, fffMask._f32, 0.0f, fffMask._f32, fffMask._f32, fffMask._f32, 0.0f));

			vec1 = _GGE256_and_ps(
				_GGE256_set128_ps(m.vec2, v.vec),
				_GGE256_set_ps(fffMask._f32, fffMask._f32, fffMask._f32, 0.0f, fffMask._f32, fffMask._f32, fffMask._f32, fffMask._f32));
		}

		GGE_inline void build(const float3x4& m, const float4& v) GGE_noexcept
		{
			vec0 = _GGE256_set128_ps(m.vec0, m.vec1);
			vec1 = _GGE256_set128_ps(m.vec2, v.vec);
		}

		GGE_inline void build(const float4x3& m, const float4& v) GGE_noexcept
		{
			vec0 = _GGE256_set128_ps(m.vec0, m.vec1);
			vec1 = _GGE256_set128_ps(m.vec2, v.vec);
			*this = transpose(*this); // Copy over as rows, then transpose
		}

		float4& operator[](int N)
		{
			GGE_assert(N >= 0 && N <= 3);
			return *(&row0 + N);
		}

		const float4& operator[](int N) const
		{
			GGE_assert(N >= 0 && N <= 3);
			return *(&row0 + N);
		}

		union
		{
			n256 vec0;
			float f32_256_0[8];
			float4 row0;

			GGE_WARNING_ANONYMOUS_STRUCT_UNION_BEGIN
			struct
			{
				union 
				{
					#include "swizzle/matrix_row0_1.h"
					#include "swizzle/matrix_row0_2.h"
					#include "swizzle/matrix_row0_3.h"
					#include "swizzle/matrix_row0_4.h"
				};
			
				union
				{
					#include "swizzle/matrix_row1_1.h"
					#include "swizzle/matrix_row1_2.h"
					#include "swizzle/matrix_row1_3.h"
					#include "swizzle/matrix_row1_4.h"
				};
			};
			GGE_WARNING_ANONYMOUS_STRUCT_UNION_END
		};

		union
		{
			n256 vec1;
			float f32_256_1[8];

			GGE_WARNING_ANONYMOUS_STRUCT_UNION_BEGIN
			struct
			{
				union
				{
					#include "swizzle/matrix_row2_1.h"
					#include "swizzle/matrix_row2_2.h"
					#include "swizzle/matrix_row2_3.h"
					#include "swizzle/matrix_row2_4.h"
				};

				union
				{
					#include "swizzle/matrix_row3_1.h"
					#include "swizzle/matrix_row3_2.h"
					#include "swizzle/matrix_row3_3.h"
					#include "swizzle/matrix_row3_4.h"
				};
			};
			GGE_WARNING_ANONYMOUS_STRUCT_UNION_END
		};
#else

		GGE_inline float4x4() GGE_noexcept 
			: vec0(_GGE_setzero_ps()), vec1(_GGE_setzero_ps()), vec2(_GGE_setzero_ps()), vec3(_GGE_setzero_ps()) {}

		GGE_inline float4x4(const float4x4& m) GGE_noexcept : vec0(m.vec0), vec1(m.vec1), vec2(m.vec2), vec3(m.vec3) {}

		explicit GGE_inline float4x4(const n128& vec0, const n128& vec1, const n128& vec2, const n128& vec3) GGE_noexcept 
			: vec0(vec0), vec1(vec1), vec2(vec2), vec3(vec3) {}

		explicit GGE_inline float4x4(
		    float f00, float f01, float f02, float f03,
		    float f10, float f11, float f12, float f13,
		    float f20, float f21, float f22, float f23,
		    float f30, float f31, float f32, float f33)
		    GGE_noexcept : vec0(_GGE_set_ps(f00, f01, f02, f03)), vec1(_GGE_set_ps(f10, f11, f12, f13)), 
			                  vec2(_GGE_set_ps(f20, f21, f22, f23)), vec3(_GGE_set_ps(f30, f31, f32, f33)) {}

		explicit GGE_inline float4x4(float f) GGE_noexcept 
			: vec0(_GGE_set1_ps(f)), vec1(_GGE_set1_ps(f)), vec2(_GGE_set1_ps(f)), vec3(_GGE_set1_ps(f)) {}

		GGE_inline float4x4(const float4& f1, const float4& f2, const float4& f3, const float4& f4) GGE_noexcept 
			: vec0(f1.vec), vec1(f2.vec), vec2(f3.vec), vec3(f4.vec) {}

		GGE_inline float4x4& operator = (const float4x4& m) GGE_noexcept 
		{ vec0 = m.vec0; vec1 = m.vec1; vec2 = m.vec2; vec3 = m.vec3; return *this; }

		GGE_inline float4x4(float4x4&& m) GGE_noexcept : vec0(m.vec0), vec1(m.vec1), vec2(m.vec2), vec3(m.vec3) {}
		GGE_inline float4x4& operator = (float4x4&& m) GGE_noexcept { vec0 = m.vec0; vec1 = m.vec1; vec2 = m.vec2; vec3 = m.vec3; return *this; }

		GGE_inline void build(const float3x3& m, const float4& v) GGE_noexcept
		{
			vec0 = _GGE_and_ps(m.vec0, _GGE_set_ps(fffMask._f32, fffMask._f32, fffMask._f32, 0.0f));
			vec1 = _GGE_and_ps(m.vec1, _GGE_set_ps(fffMask._f32, fffMask._f32, fffMask._f32, 0.0f));
			vec2 = _GGE_and_ps(m.vec2, _GGE_set_ps(fffMask._f32, fffMask._f32, fffMask._f32, 0.0f));
			vec3 = v.vec;
		}

		GGE_inline void build(const float3x4& m, const float4& v) GGE_noexcept
		{
			vec0 = m.vec0; vec1 = m.vec1; vec2 = m.vec2; vec3 = v.vec;
		}

		GGE_inline void build(const float4x3& m, const float4& v) GGE_noexcept
		{
			vec0 = m.vec0; vec1 = m.vec1; vec2 = m.vec2;
			*this = transpose(*this); // Copy over as rows, then transpose
			vec3 = v.vec;
		}

		float4& operator[](int N)
		{
			GGE_assert(N >= 0 && N <= 3);
			return *(&reinterpret_cast<float4&>(vec0) + N);
		}

		const float4& operator[](int N) const
		{
			GGE_assert(N >= 0 && N <= 3);
			return *(&reinterpret_cast<const float4&>(vec0) + N);
		}

		GGE_WARNING_ANONYMOUS_STRUCT_UNION_BEGIN
		union
		{
			n128 vec0;
			float f32_128_0[4];
			#include "swizzle/matrix_row0_1.h"
			#include "swizzle/matrix_row0_2.h"
			#include "swizzle/matrix_row0_3.h"
			#include "swizzle/matrix_row0_4.h"
		};

		union
		{
			n128 vec1;
			float f32_128_1[4];
			#include "swizzle/matrix_row1_1.h"
			#include "swizzle/matrix_row1_2.h"
			#include "swizzle/matrix_row1_3.h"
			#include "swizzle/matrix_row1_4.h"
		};

		union
		{
			n128 vec2;
			float f32_128_2[4];
			#include "swizzle/matrix_row2_1.h"
			#include "swizzle/matrix_row2_2.h"
			#include "swizzle/matrix_row2_3.h"
			#include "swizzle/matrix_row2_4.h"
		};

		union
		{
			n128 vec3;
			float f32_128_3[4];
			#include "swizzle/matrix_row3_1.h"
			#include "swizzle/matrix_row3_2.h"
			#include "swizzle/matrix_row3_3.h"
			#include "swizzle/matrix_row3_4.h"
		};
		GGE_WARNING_ANONYMOUS_STRUCT_UNION_END
#endif

		// Conversion from lower-dimension matrices
		explicit GGE_inline float4x4(const float3x3& m, const float4& v) GGE_noexcept { build(m, v); }
		explicit GGE_inline float4x4(const float3x3& m) GGE_noexcept { build(m, float4(_GGE_setzero_ps())); }
		
		explicit GGE_inline float4x4(const float3x4& m, const float4& v) GGE_noexcept { build(m, v); }
		explicit GGE_inline float4x4(const float3x4& m) GGE_noexcept { build(m, float4(_GGE_setzero_ps())); }

		explicit GGE_inline float4x4(const float4x3& m) GGE_noexcept { build(m, float4(_GGE_setzero_ps())); }

		explicit GGE_inline float4x4(const quaternion& q) GGE_noexcept;

		static const float4x4& identity() { static const float4x4 iden = float4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1); return iden; };

		#include <Core/Math/hlsl++/transform/float4x4.h>
	};

	GGE_inline void store(float* dst, const float1x1& src) { _GGE_store1_ps(dst, src.vec); }
	GGE_inline void store(float* dst, const float1x2& src) { _GGE_store2_ps(dst, src.vec); }
	GGE_inline void store(float* dst, const float2x1& src) { _GGE_store2_ps(dst, src.vec); }
	GGE_inline void store(float* dst, const float1x3& src) { _GGE_store3_ps(dst, src.vec); }
	GGE_inline void store(float* dst, const float3x1& src) { _GGE_store3_ps(dst, src.vec); }
	GGE_inline void store(float* dst, const float1x4& src) { _GGE_store4_ps(dst, src.vec); }
	GGE_inline void store(float* dst, const float4x1& src) { _GGE_store4_ps(dst, src.vec); }

	GGE_inline void store(float* dst, const float2x2& src) { _GGE_store4_ps(dst, src.vec); }
	GGE_inline void store(float* dst, const float2x3& src)
	{
		_GGE_store3_ps(dst + 0, src.vec0);
		_GGE_store3_ps(dst + 3, src.vec1);
	}

	GGE_inline void store(float* dst, const float2x4& src)
	{
		_GGE_store4_ps(dst + 0, src.vec0);
		_GGE_store4_ps(dst + 4, src.vec1);
	}

	GGE_inline void store(float* dst, const float3x2& src)
	{
		_GGE_store4_ps(dst, _GGE_unpacklo_ps(src.vec0, src.vec1));
		_GGE_store2_ps(dst, _GGE_unpackhi_ps(src.vec0, src.vec1));
	}

	GGE_inline void store(float* dst, const float4x2& src)
	{
		_GGE_store4_ps(dst, _GGE_unpacklo_ps(src.vec0, src.vec1));
		_GGE_store4_ps(dst, _GGE_unpackhi_ps(src.vec0, src.vec1));
	}

	GGE_inline void store(float* dst, const float3x3& src)
	{
		_GGE_store3x3_ps(dst, src.vec0, src.vec1, src.vec2);
	}

	GGE_inline void store(float* dst, const float3x4& src)
	{
		_GGE_store4_ps(dst, src.vec0);
		_GGE_store4_ps(dst + 4, src.vec1);
		_GGE_store4_ps(dst + 8, src.vec2);
	}

	GGE_inline void store(float* dst, const float4x3& src)
	{
		float tmp[12];
		_GGE_store4_ps(tmp + 0, src.vec0);
		_GGE_store4_ps(tmp + 4, src.vec1);
		_GGE_store4_ps(tmp + 8, src.vec2);
		dst[0] = tmp[0]; dst[ 1] = tmp[4]; dst[ 2] = tmp[8];
		dst[3] = tmp[1]; dst[ 4] = tmp[5]; dst[ 5] = tmp[9];
		dst[6] = tmp[2]; dst[ 7] = tmp[6]; dst[ 8] = tmp[10];
		dst[9] = tmp[3]; dst[10] = tmp[7]; dst[11] = tmp[11];
	}

	GGE_inline void store(float* dst, const float4x4& src)
	{
#if defined(GGE_SIMD_REGISTER_512)
		_GGE512_store4x4_ps(dst, src.vec);
#elif defined(GGE_SIMD_REGISTER_256)
		_GGE256_store4x4_ps(dst, src.vec0, src.vec1);
#else
		_GGE_store4x4_ps(dst, src.vec0, src.vec1, src.vec2, src.vec3);
#endif
	}

	GGE_inline void store_transposed(float* dst, const float4x4& src)
	{
		// TODO Create optimized functions for storing transposed matrix
		float4x4 tsrc = transpose(src);

#if defined(GGE_SIMD_REGISTER_512)
		_GGE512_store4x4_ps(dst, tsrc.vec);
#elif defined(GGE_SIMD_REGISTER_256)
		_GGE256_store4x4_ps(dst, tsrc.vec0, tsrc.vec1);
#else
		_GGE_store4x4_ps(dst, tsrc.vec0, tsrc.vec1, tsrc.vec2, tsrc.vec3);
#endif
	}

	GGE_inline void load(float3x3& dst, const float* src)
	{
		_GGE_load3x3_ps(dst.vec0, dst.vec1, dst.vec2, src);
	}

	GGE_inline void load(float4x4& dst, const float* src)
	{
#if defined(GGE_SIMD_REGISTER_512)
		_GGE512_load4x4_ps(dst.vec, src);
#elif defined(GGE_SIMD_REGISTER_256)
		_GGE256_load4x4_ps(dst.vec0, dst.vec1, src);
#else
		_GGE_load4x4_ps(dst.vec0, dst.vec1, dst.vec2, dst.vec3, src);
#endif
	}

	GGE_WARNING_ANONYMOUS_STRUCT_UNION_BEGIN
	GGE_WARNING_PADDING_BEGIN
	namespace interop
	{
		struct float4x3
		{
			float4x3() GGE_constructor_default;
#if defined(GGE_INTEROP_PHYSICAL_LAYOUT_COLUMN_MAJOR)
			float4x3(const GGE::float4x3& m) { GGE::store(&m00, m); }
#else
			// Function not available
			float4x3(const GGE::float4x3& m) GGE_constructor_delete;
#endif
			float m00, m01, m02, m03,
			      m10, m11, m12, m13,
			      m20, m21, m22, m23;
		};

		struct float3x4
		{
			float3x4() GGE_constructor_default;
#if defined(GGE_INTEROP_PHYSICAL_LAYOUT_COLUMN_MAJOR)
			// Function not available
			float3x4(const GGE::float3x4& m) GGE_constructor_delete;
#else
			float3x4(const GGE::float3x4& m) { GGE::store(&m00, m); }
#endif
			float m00, m01, m02, m03,
			      m10, m11, m12, m13,
			      m20, m21, m22, m23;
		};

		struct float4x4
		{
			float4x4() GGE_constructor_default;
#if defined(GGE_INTEROP_PHYSICAL_LAYOUT_COLUMN_MAJOR)
			float4x4(const GGE::float4x4& m) { GGE::store_transposed(&m00, m); }
#else
			float4x4(const GGE::float4x4& m) { GGE::store(&m00, m); }
#endif
			float m00, m01, m02, m03,
			      m10, m11, m12, m13,
			      m20, m21, m22, m23,
			      m30, m31, m32, m33;
		};
	}
	GGE_WARNING_PADDING_END
	GGE_WARNING_ANONYMOUS_STRUCT_UNION_END
};