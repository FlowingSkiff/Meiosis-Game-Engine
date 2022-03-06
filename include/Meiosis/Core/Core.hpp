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

#define ME_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { \
    return this->fn(std::forward<decltype(args)>(args)...);             \
}
