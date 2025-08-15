#pragma once

#include <Core/Math/hlsl++/common.h>

// Add GGE_FEATURE_TRANSFORM definition prior to including hlsl++.h to enable compilation of matrix transformations
#include <Core/Math/hlsl++/transform/common.h>

#include <Core/Math/hlsl++/vector_float.h>

#include <Core/Math/hlsl++/vector_float8.h>

#include <Core/Math/hlsl++/matrix_float.h>

#include <Core/Math/hlsl++/vector_int.h>

#include <Core/Math/hlsl++/vector_uint.h>

#include <Core/Math/hlsl++/vector_double.h>

#include <Core/Math/hlsl++/quaternion.h>

// Some functions depend on having the knowledge of types that have been defined before.
// In order to break the header dependencies they are all defined here.
#include <Core/Math/hlsl++/dependent.h>
