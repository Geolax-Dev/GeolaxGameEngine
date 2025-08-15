#pragma once

#include <Core/Math/hlsl++/vector_float.h>
#include <Core/Math/hlsl++/vector_int.h>
#include <Core/Math/hlsl++/vector_uint.h>
#include <Core/Math/hlsl++/quaternion.h>
#include <Core/Math/hlsl++/matrix_float.h>

GGE_module_export namespace GGE
{
	float1::float1(const int1& i) GGE_noexcept : vec(_GGE_cvtepi32_ps(i.vec)) {}
	float2::float2(const int2& i) GGE_noexcept : vec(_GGE_cvtepi32_ps(i.vec)) {}
	float3::float3(const int3& i) GGE_noexcept : vec(_GGE_cvtepi32_ps(i.vec)) {}
	float4::float4(const int4& i) GGE_noexcept : vec(_GGE_cvtepi32_ps(i.vec)) {}

	float1::float1(const uint1& i) GGE_noexcept : vec(_GGE_cvtepu32_ps(i.vec)) {}
	float2::float2(const uint2& i) GGE_noexcept : vec(_GGE_cvtepu32_ps(i.vec)) {}
	float3::float3(const uint3& i) GGE_noexcept : vec(_GGE_cvtepu32_ps(i.vec)) {}
	float4::float4(const uint4& i) GGE_noexcept : vec(_GGE_cvtepu32_ps(i.vec)) {}

	int1::int1(const float1& f) GGE_noexcept : vec(_GGE_cvttps_epi32(f.vec)) {}
	int2::int2(const float2& f) GGE_noexcept : vec(_GGE_cvttps_epi32(f.vec)) {}
	int3::int3(const float3& f) GGE_noexcept : vec(_GGE_cvttps_epi32(f.vec)) {}
	int4::int4(const float4& f) GGE_noexcept : vec(_GGE_cvttps_epi32(f.vec)) {}

	uint1::uint1(const float1& f) GGE_noexcept : vec(_GGE_cvttps_epu32(f.vec)) {}
	uint2::uint2(const float2& f) GGE_noexcept : vec(_GGE_cvttps_epu32(f.vec)) {}
	uint3::uint3(const float3& f) GGE_noexcept : vec(_GGE_cvttps_epu32(f.vec)) {}
	uint4::uint4(const float4& f) GGE_noexcept : vec(_GGE_cvttps_epu32(f.vec)) {}

	GGE_inline float1x1::float1x1(const float2x2& m) GGE_noexcept
	{
		vec = m.vec;
	}

	GGE_inline float2x2::float2x2(const float3x3& m) GGE_noexcept
	{
		vec = _GGE_shuf_xyxy_ps(m.vec0, m.vec1);
	}

	GGE_inline float3x3::float3x3(const quaternion& q) GGE_noexcept
	{
		_GGE_quat_to_3x3_ps(q.vec, vec0, vec1, vec2);
	}

	GGE_inline float3x3::float3x3(const float4x4& m) GGE_noexcept
	{
#if defined(GGE_SIMD_REGISTER_512)

		vec0 = _GGE512_vec0_ps(m.vec);
		vec1 = _GGE512_vec1_ps(m.vec);
		vec2 = _GGE512_vec2_ps(m.vec);

#elif defined(GGE_SIMD_REGISTER_256)
		vec0 = _GGE256_low_ps(m.vec0);
		vec1 = _GGE256_high_ps(m.vec0);
		vec2 = _GGE256_low_ps(m.vec1);
#else
		vec0 = m.vec0;
		vec1 = m.vec1;
		vec2 = m.vec2;
#endif
	}

	GGE_inline float4x4::float4x4(const quaternion& q) GGE_noexcept
	{
#if defined(GGE_SIMD_REGISTER_512)

		n128 temp_vec0, temp_vec1, temp_vec2;
		_GGE_quat_to_3x3_ps(q.vec, temp_vec0, temp_vec1, temp_vec2);

		n512 row_0123_mask = _GGE512_castsi512_ps(_GGE512_set_epi32(0xffffffff, 0xffffffff, 0xffffffff, 0, 0xffffffff, 0xffffffff, 0xffffffff, 0, 0xffffffff, 0xffffffff, 0xffffffff, 0, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff));
		
		n512 row_0123 = _GGE512_set128_ps(temp_vec0, temp_vec1, temp_vec2, _GGE_set_ps(0.0f, 0.0f, 0.0f, 1.0f));
		
		vec = _GGE512_and_ps(row_0123, row_0123_mask);

#elif defined(GGE_SIMD_REGISTER_256)

		n128 temp_vec0, temp_vec1, temp_vec2;

		_GGE_quat_to_3x3_ps(q.vec, temp_vec0, temp_vec1, temp_vec2);
		
		n256 row01Mask = _GGE256_castsi256_ps(_GGE256_set_epi32(0xffffffff, 0xffffffff, 0xffffffff, 0, 0xffffffff, 0xffffffff, 0xffffffff, 0));
		n256 row23Mask = _GGE256_castsi256_ps(_GGE256_set_epi32(0xffffffff, 0xffffffff, 0xffffffff, 0, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff));

		n256 row01 = _GGE256_set128_ps(temp_vec0, temp_vec1);
		n256 row23 = _GGE256_set128_ps(temp_vec2, _GGE_set_ps(0.0f, 0.0f, 0.0f, 1.0f));

		vec0 = _GGE256_and_ps(row01, row01Mask);
		vec1 = _GGE256_and_ps(row23, row23Mask);

#else

		_GGE_quat_to_3x3_ps(q.vec, vec0, vec1, vec2);
		n128 zeroLast = _GGE_castsi128_ps(_GGE_set_epi32((int)0xffffffff, (int)0xffffffff, (int)0xffffffff, 0));
		vec0 = _GGE_and_ps(vec0, zeroLast);
		vec1 = _GGE_and_ps(vec1, zeroLast);
		vec2 = _GGE_and_ps(vec2, zeroLast);
		vec3 = _GGE_set_ps(0.0f, 0.0f, 0.0f, 1.0f);

#endif
	}

	GGE_inline quaternion::quaternion(const float3x3& m) GGE_noexcept
	{
		_GGE_3x3_to_quat_ps(m.vec0, m.vec1, m.vec2, vec);
	}

	GGE_inline float1 ldexp(const float1& f, const int1& e) { return float1(_GGE_ldexp_ps(f.vec, e.vec)); }
	GGE_inline float2 ldexp(const float2& f, const int2& e) { return float2(_GGE_ldexp_ps(f.vec, e.vec)); }
	GGE_inline float3 ldexp(const float3& f, const int3& e) { return float3(_GGE_ldexp_ps(f.vec, e.vec)); }
	GGE_inline float4 ldexp(const float4& f, const int4& e) { return float4(_GGE_ldexp_ps(f.vec, e.vec)); }

	//-----------------------
	// asfloat, asuint, asint
	//-----------------------

	GGE_inline float asfloat(const uint v) { return detail::packed_union(v)._f32; }
	GGE_inline float1 asfloat(const uint1& v) { return reinterpret_cast<const float1&>(v); }
	GGE_inline float2 asfloat(const uint2& v) { return reinterpret_cast<const float2&>(v); }
	GGE_inline float3 asfloat(const uint3& v) { return reinterpret_cast<const float3&>(v); }
	GGE_inline float4 asfloat(const uint4& v) { return reinterpret_cast<const float4&>(v); }

	GGE_inline float asfloat(const int v) { return detail::packed_union(v)._f32; }
	GGE_inline float1 asfloat(const int1& v) { return reinterpret_cast<const float1&>(v); }
	GGE_inline float2 asfloat(const int2& v) { return reinterpret_cast<const float2&>(v); }
	GGE_inline float3 asfloat(const int3& v) { return reinterpret_cast<const float3&>(v); }
	GGE_inline float4 asfloat(const int4& v) { return reinterpret_cast<const float4&>(v); }

	GGE_inline uint asuint(const int v) { return detail::packed_union(v)._u32; }
	GGE_inline uint1 asuint(const int1& v) { return reinterpret_cast<const uint1&>(v); }
	GGE_inline uint2 asuint(const int2& v) { return reinterpret_cast<const uint2&>(v); }
	GGE_inline uint3 asuint(const int3& v) { return reinterpret_cast<const uint3&>(v); }
	GGE_inline uint4 asuint(const int4& v) { return reinterpret_cast<const uint4&>(v); }

	GGE_inline uint asuint(const float v) { return detail::packed_union(v)._u32; }
	GGE_inline uint1 asuint(const float1& v) { return reinterpret_cast<const uint1&>(v); }
	GGE_inline uint2 asuint(const float2& v) { return reinterpret_cast<const uint2&>(v); }
	GGE_inline uint3 asuint(const float3& v) { return reinterpret_cast<const uint3&>(v); }
	GGE_inline uint4 asuint(const float4& v) { return reinterpret_cast<const uint4&>(v); }

	GGE_inline int asint(const uint v) { return detail::packed_union(v)._i32; }
	GGE_inline int1 asint(const uint1& v) { return reinterpret_cast<const int1&>(v); }
	GGE_inline int2 asint(const uint2& v) { return reinterpret_cast<const int2&>(v); }
	GGE_inline int3 asint(const uint3& v) { return reinterpret_cast<const int3&>(v); }
	GGE_inline int4 asint(const uint4& v) { return reinterpret_cast<const int4&>(v); }

	GGE_inline int asint(const float v) { return detail::packed_union(v)._i32; }
	GGE_inline int1 asint(const float1& v) { return reinterpret_cast<const int1&>(v); }
	GGE_inline int2 asint(const float2& v) { return reinterpret_cast<const int2&>(v); }
	GGE_inline int3 asint(const float3& v) { return reinterpret_cast<const int3&>(v); }
	GGE_inline int4 asint(const float4& v) { return reinterpret_cast<const int4&>(v); }
}