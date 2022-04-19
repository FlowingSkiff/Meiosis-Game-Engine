#pragma once
#include <type_traits>
#include <utility>
#include <cstdint>
#ifdef ME_BUILD_DLL
#define ME_API __declspec(dllexport)
#elifdef ME_LINK_DLL
#define ME_API __declspec(dllimport)
#else
#define ME_API
#endif

inline constexpr auto bit(int n) { return 1 << n; }

template<typename TYPE, typename FUNC>
constexpr inline auto bindMemberFunction(TYPE* obj, FUNC func) -> decltype(auto)
{
    return [obj, func](auto&&... args) -> decltype(auto) {
        return (obj->*func)(std::forward<decltype(args)>(args)...);
    };
}