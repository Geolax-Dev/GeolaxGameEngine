#pragma once

#include <Core/Math/hlsl++/common.h>

GGE_module_export namespace GGE
{
	struct GGE_nodiscard quaternion
	{
		quaternion() GGE_noexcept : vec(_GGE_setzero_ps()) {}
		quaternion(const quaternion& q) GGE_noexcept : vec(q.vec) {}
		explicit quaternion(n128 vec) GGE_noexcept : vec(vec) {}

		template<typename T1, typename T2, typename T3, typename T4>
		quaternion(T1 f1, T2 f2, T3 f3, T4 f4, GGE_enable_if_number_4(T1, T2, T3, T4)) 
			GGE_noexcept : vec(_GGE_set_ps(float(f1), float(f2), float(f3), float(f4))) {}

		quaternion(const float1& f1, const float1& f2, const float1& f3, const float1& f4) 
		GGE_noexcept { vec = _GGE_blend_ps(_GGE_shuf_xxxx_ps(f1.vec, f3.vec), _GGE_shuf_xxxx_ps(f2.vec, f4.vec), GGE_BLEND_MASK(1, 0, 1, 0)); }

		quaternion(const float2& f1, const float1& f2, const float1& f3) GGE_noexcept 
		{ vec = _GGE_blend_ps(_GGE_shuf_xyxx_ps(f1.vec, f2.vec), _GGE_perm_xxxx_ps(f3.vec), GGE_BLEND_MASK(1, 1, 1, 0)); }

		quaternion(const float1& f1, const float2& f2, const float1& f3) GGE_noexcept
		{ vec = _GGE_blend_ps(_GGE_shuf_xxxx_ps(f1.vec, f3.vec), _GGE_perm_xxyx_ps(f2.vec), GGE_BLEND_MASK(1, 0, 0, 1)); }

		quaternion(const float1& f1, const float1& f2, const float2& f3) GGE_noexcept
		{ vec = _GGE_blend_ps(_GGE_shuf_xxxy_ps(f1.vec, f3.vec), _GGE_perm_xxxx_ps(f2.vec), GGE_BLEND_MASK(1, 0, 1, 1)); }

		quaternion(const float2& f1, const float2& f2) GGE_noexcept { vec = _GGE_shuf_xyxy_ps(f1.vec, f2.vec); }

		quaternion(const float1& f1, const float3& f2) GGE_noexcept { vec = _GGE_blend_ps(f1.vec, _GGE_perm_xxyz_ps(f2.vec), GGE_BLEND_MASK(1, 0, 0, 0)); }
		quaternion(const float3& f1, const float1& f2) GGE_noexcept { vec = _GGE_blend_ps(f1.vec, _GGE_perm_xxxx_ps(f2.vec), GGE_BLEND_MASK(1, 1, 1, 0)); }

		explicit quaternion(const float3& f) GGE_noexcept { vec = _GGE_and_ps(f.vec, _GGE_castsi128_ps(_GGE_set_epi32((int)0xffffffff, (int)0xffffffff, (int)0xffffffff, 0))); }

		explicit quaternion(const float4& f) GGE_noexcept { vec = f.vec; }
		//quaternion(const float1x4& q) { vec = q.vec; }

		explicit quaternion(const float3x3& m) GGE_noexcept;

		GGE_inline quaternion& operator = (const quaternion& q) { vec = q.vec; return *this; }

		static const quaternion& identity() { static const quaternion identity = quaternion(0.0f, 0.0f, 0.0f, 1.0f); return identity; };

		static quaternion rotation_x(float angle);

		static quaternion rotation_y(float angle);

		static quaternion rotation_z(float angle);

		static quaternion rotation_axis(const float3& axis, float angle);

		static quaternion rotation_axis_cosangle(const float3& axis, float cosangle, float sign);

		static quaternion rotation_euler_zxy(const float3& angles);

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
};