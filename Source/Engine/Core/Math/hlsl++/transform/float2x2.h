#pragma once

#if defined(GGE_FEATURE_TRANSFORM)

//-------//
// Scale //
//-------//

static GGE_inline float2x2 scale(float sx, float sy)
{
	return float2x2(
		sx,   0.0f,
		0.0f, sy
	);
}

static GGE_inline float2x2 scale(const float2& s)
{
	return scale(s.x, s.y);
}

static GGE_inline float2x2 scale(float su)
{
	return scale(su, su);
}

//----------//
// Rotation //
//----------//

static GGE_inline float2x2 rotation(float angle_rad)
{
#if defined(GGE_LAYOUT_COORDINATES_FLIP_SIGN)
	angle_rad = -angle_rad;
#endif

	const float s = sinf(angle_rad);
	const float c = cosf(angle_rad);

	return float2x2(
		c,  s,
		-s, c
	);
}

#endif
