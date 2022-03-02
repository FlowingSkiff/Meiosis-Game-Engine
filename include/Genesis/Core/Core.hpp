#pragma once

#ifdef GN_BUILD_DLL
#define GN_API __declspec(dllexport)
#else
#define GN_API __declspec(dllimport)
#endif