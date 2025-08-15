#pragma once

#ifdef _DEBUG
#pragma comment(lib, "bgfxDebug.lib")
#pragma comment(lib, "bimg_decodeDebug.lib")
#pragma comment(lib, "bimgDebug.lib")
#pragma comment(lib, "bxDebug.lib")
#else
#pragma comment(lib, "bgfxRelease.lib")
#pragma comment(lib, "bimg_decodeRelease.lib")
#pragma comment(lib, "bimgRelease.lib")
#pragma comment(lib, "bxRelease.lib")
#endif // !_DEBUG
