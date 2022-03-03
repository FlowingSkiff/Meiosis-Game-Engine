#pragma once

#ifdef GN_BUILD_DLL
#define GN_API __declspec(dllexport)
#elif GN_LINK_DLL
#define GN_API __declspec(dllimport)
#else
#define GN_API
#endif