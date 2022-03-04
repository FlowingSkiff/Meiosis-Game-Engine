#pragma once
#include <type_traits>
#ifdef GN_BUILD_DLL
#define GN_API __declspec(dllexport)
#elif GN_LINK_DLL
#define GN_API __declspec(dllimport)
#else
#define GN_API
#endif

inline constexpr auto bit(int n) { return 1 << n; }