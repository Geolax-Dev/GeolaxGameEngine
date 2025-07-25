#pragma once

#define GUARD_EXTERNAL_INCLUDE_BEGIN \
__pragma(warning(push)) \
//__pragma(warning(disable: 4668))

#define GUARD_EXTERNAL_INCLUDE_END \
__pragma(warning(pop))

#pragma warning(disable: 4100 4127 4324 4514 4625 4626 4668 4710 4711 4820 5039 5045)

#define BIT(x) (1u << (x))

#ifndef DISTRIBUTION_READY
#define DISTRIBUTION_READY (0)
#endif 
