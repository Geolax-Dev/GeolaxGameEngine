#pragma once

// C++ Version

#if defined(_MSVC_LANG)

	#define GGE_CPPVERSION _MSVC_LANG

#elif defined(__cplusplus)

	#define GGE_CPPVERSION __cplusplus

#endif

// Note: The GGE_WARNING_IMPLICIT_CONSTRUCTOR_BEGIN warning behaves differently
// between GCC and Clang. In GCC, we need to apply the warning to the call site, i.e.
// wherever we call the copy constructor. In Clang, we need to apply it to the class
// itself. This means we seem to add the same warning suppression to multiple places,
// where in reality it only applies once per compiler

#if defined(__clang__)

	#define GGE_inline inline __attribute__((always_inline))

	#define GGE_WARNING_ANONYMOUS_STRUCT_UNION_BEGIN
	#define GGE_WARNING_ANONYMOUS_STRUCT_UNION_END

	#define GGE_WARNING_POTENTIAL_DIVIDE_BY_0_BEGIN
	#define GGE_WARNING_POTENTIAL_DIVIDE_BY_0_END

	#define GGE_WARNING_IMPLICIT_CONSTRUCTOR_BEGIN \
		_Pragma("clang diagnostic push") \
		_Pragma("clang diagnostic ignored \"-Wdeprecated\"")

	#define GGE_WARNING_IMPLICIT_CONSTRUCTOR_END \
		_Pragma("clang diagnostic pop")

	#define GGE_WARNING_PADDING_BEGIN
	#define GGE_WARNING_PADDING_END

	#define GGE_WARNING_INVALID_SHUFFLE_BEGIN
	#define GGE_WARNING_INVALID_SHUFFLE_END

#elif defined(__GNUG__)

	#define GGE_inline inline __attribute__((always_inline))

	#define GGE_WARNING_ANONYMOUS_STRUCT_UNION_BEGIN
	#define GGE_WARNING_ANONYMOUS_STRUCT_UNION_END

	#define GGE_WARNING_POTENTIAL_DIVIDE_BY_0_BEGIN
	#define GGE_WARNING_POTENTIAL_DIVIDE_BY_0_END

	#define GGE_WARNING_IMPLICIT_CONSTRUCTOR_BEGIN \
	    _Pragma("GCC diagnostic push") \
		_Pragma("GCC diagnostic ignored \"-Wdeprecated-copy\"")

	#define GGE_WARNING_IMPLICIT_CONSTRUCTOR_END \
		_Pragma("GCC diagnostic pop")

	#define GGE_WARNING_PADDING_BEGIN
	#define GGE_WARNING_PADDING_END

	#define GGE_WARNING_INVALID_SHUFFLE_BEGIN
	#define GGE_WARNING_INVALID_SHUFFLE_END

#elif defined(_MSC_VER)

	#define GGE_inline __forceinline

	#define GGE_WARNING_ANONYMOUS_STRUCT_UNION_BEGIN \
	__pragma(warning(push)) \
	__pragma(warning(disable : 4201))

	#define GGE_WARNING_ANONYMOUS_STRUCT_UNION_END __pragma(warning(pop))

	#define GGE_WARNING_POTENTIAL_DIVIDE_BY_0_BEGIN \
	__pragma(warning(push)) \
	__pragma(warning(disable : 4723))

	#define GGE_WARNING_POTENTIAL_DIVIDE_BY_0_END __pragma(warning(pop))

	#define GGE_WARNING_IMPLICIT_CONSTRUCTOR_BEGIN
	#define GGE_WARNING_IMPLICIT_CONSTRUCTOR_END

	#define GGE_WARNING_PADDING_BEGIN  \
			__pragma(warning(push)) \
			__pragma(warning(disable : 4324))

	#define GGE_WARNING_PADDING_END __pragma(warning(pop))

	// If we have constexpr if the invalid condition won't be evaluated, so only disable it
	// in older versions where it gets compile time validated even though it won't ever run
	#if defined(__cpp_if_constexpr)

	#define GGE_WARNING_INVALID_SHUFFLE_BEGIN
	#define GGE_WARNING_INVALID_SHUFFLE_END

	#else

		#define GGE_WARNING_INVALID_SHUFFLE_BEGIN \
			__pragma(warning(push)) \
			__pragma(warning(disable : 4556))
		#define GGE_WARNING_INVALID_SHUFFLE_END __pragma(warning(pop))

	#endif

#else

	#error Unrecognized compiler

#endif

#if GGE_CPPVERSION >= 201702L
	#define GGE_nodiscard [[nodiscard]]
#else
	#define GGE_nodiscard
#endif

#if GGE_CPPVERSION >= 201103L
	#define GGE_constructor_delete = delete
	#define GGE_constructor_default = default
#else
	#define GGE_constructor_delete
	#define GGE_constructor_default {}
#endif

// Versions previous to VS2015 need special attention
#if defined(_MSC_VER) && _MSC_VER < 1900

	#define GGE_noexcept
	#define GGE_swizzle_start struct {
	#define GGE_swizzle_end };

	#define GGE_alignas(x) __declspec(align(x))
	#define GGE_alignof(T) __alignof(T)

#else

	#define GGE_noexcept noexcept
	#define GGE_swizzle_start
	#define GGE_swizzle_end

	#define GGE_alignas(x) alignas(x)
	#define GGE_alignof(T) alignof(T)
	
#endif

#if defined(__cpp_user_defined_literals)

	#define GGE_USER_DEFINED_LITERALS

#endif

#if defined(GGE_ASSERT)
#include <assert.h>
#define GGE_assert(x) assert(x)
#else
#define GGE_assert(x)
#endif

#if defined(GGE_MODULE_DECLARATION)

#define GGE_module_export export

#else

#define GGE_module_export

#endif

#define GGE_MASK_X 0
#define GGE_MASK_Y 1
#define GGE_MASK_Z 2
#define GGE_MASK_W 3

#define GGE_SHUFFLE_MASK(X, Y, Z, W)		(((W) << 6) | ((Z) << 4) | ((Y) << 2) | (X))
#define GGE_SHUFFLE_MASK_PD(X, Y)		(((Y) << 1) | (X))

// Create a mask where 1 selects from x, 0 selects from y
#define GGE_BLEND_MASK(X, Y, Z, W)		(~((X) | ((Y) << 1) | ((Z) << 2) | ((W) << 3)) & 0xf)
#define GGE_BLEND_MASK_PD(X, Y)			(~((X) | ((Y) << 1)) & 0x3)

#define GGE_COMPONENT_X(X)				(1 << X)
#define GGE_COMPONENT_XY(X, Y)			((1 << X) | (1 << Y))
#define GGE_COMPONENT_XYZ(X, Y, Z)		((1 << X) | (1 << Y) | (1 << Z))
#define GGE_COMPONENT_XYZW(X, Y, Z, W)	((1 << X) | (1 << Y) | (1 << Z) | (1 << W))

#if defined(__cpp_if_constexpr)

	#define GGE_constexpr_if(x) if constexpr(x)

#else

	#if defined(_MSC_VER)
		
		// warning C4127: conditional expression is constant
		// Disable because we always use these in a template context
		// Builds that don't support constexpr optimize them away
		#define GGE_constexpr_if(x) \
		__pragma(warning(push)) \
		__pragma(warning(disable : 4127)) \
		if(x) \
		__pragma(warning(pop))

	#else

		#define GGE_constexpr_if(x) if(x)

	#endif

#endif

// We try to auto detect any vector libraries available to the system.
// If we don't find any, fall back to scalar.

#if !defined(GGE_ARM) && (defined(_M_ARM) || defined(__arm__) || defined(_M_ARM64) || defined(__aarch64__) || defined(_M_ARM64EC))

	#define GGE_ARM

#elif !defined(GGE_360) && defined(_XBOX)

	#define GGE_360

#elif !defined(GGE_SSE) && (defined(__SSE__) || (defined(_M_IX86_FP) && _M_IX86_FP > 0) || defined(_M_AMD64) || defined(_M_X64))

	#define GGE_SSE

#elif !defined(GGE_WASM) && defined(__wasm_simd128__)

	#define GGE_WASM

#elif !defined(GGE_SCALAR)

	#define GGE_SCALAR

#endif

#if defined(GGE_MODULE_DECLARATION)
import "stdint.h";
#else
#include <stdint.h>
#endif

#include <Core/Math/hlsl++/type_traits.h>

#include <Core/Math/hlsl++/bitmask.h>

// Despite the process above, we can still force the library to behave as scalar by defining the
// implementation we want.

#if defined(GGE_SCALAR)

	#include "platforms/scalar.h"

#elif defined(GGE_WASM)

	#include "platforms/wasm.h"

#elif defined(GGE_SSE)

	#include "platforms/sse.h"

#elif defined(GGE_ARM)

	#include "platforms/neon.h"

#elif defined(GGE_360)

	#include "platforms/xbox360.h"

#endif

// There are two main matrix swizzle formats one where upper left is _m00 and the other where it's indicated as _11
// We enable _m00 by default and the other one is left as an option

#if !defined(GGE_ENABLE_MATRIX_SWIZZLE_M00)

	#define GGE_ENABLE_MATRIX_SWIZZLE_M00 1

#endif

#if !defined(GGE_ENABLE_MATRIX_SWIZZLE_11)

	#define GGE_ENABLE_MATRIX_SWIZZLE_11 0

#endif