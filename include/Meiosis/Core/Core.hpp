#pragma once
#include <type_traits>
#ifdef ME_BUILD_DLL
#define ME_API __declspec(dllexport)
#elif ME_LINK_DLL
#define ME_API __declspec(dllimport)
#else
#define ME_API
#endif

inline constexpr auto bit(int n) { return 1 << n; }