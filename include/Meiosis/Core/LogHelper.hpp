#pragma once
#include <fmt/format.h>
#include <glm/glm.hpp>
#include <glm/gtx/range.hpp>
// template<>
// struct fmt::formatter<TYPE>
// {
//     template<typename ParseContext>
//     constexpr auto parse(ParseContext& ctx);
//     template<typename FormatContext>
//     auto format(const TYPE& type, FormatContext& context);
// }


template<>
struct fmt::formatter<glm::vec2>
{
    template<typename ParseContext>
    constexpr auto parse(ParseContext& ctx)
    {
        return ctx.begin();
    }
    template<typename FormatContext>
    auto format(const glm::vec2& type, FormatContext& ctx)
    {
        return fmt::format_to(ctx.out(), "{}, {}", type.x, type.y);
    }
};
template<>
struct fmt::formatter<glm::vec3>
{
    template<typename ParseContext>
    constexpr auto parse(ParseContext& ctx)
    {
        return ctx.begin();
    }
    template<typename FormatContext>
    auto format(const glm::vec3& type, FormatContext& ctx)
    {
        return fmt::format_to(ctx.out(), "{}, {}, {}", type.x, type.y, type.z);
    }
};
template<>
struct fmt::formatter<glm::vec4>
{
    template<typename ParseContext>
    constexpr auto parse(ParseContext& ctx)
    {
        return ctx.begin();
    }
    template<typename FormatContext>
    auto format(const glm::vec4& type, FormatContext& ctx)
    {
        return fmt::format_to(ctx.out(), "{}, {}, {}, {}", type.x, type.y, type.z, type.w);
    }
};
template<>
struct fmt::formatter<glm::mat3>
{
    template<typename ParseContext>
    constexpr auto parse(ParseContext& ctx)
    {
        return ctx.begin();
    }
    template<typename FormatContext>
    auto format(const glm::mat3& type, FormatContext& ctx)
    {
        return fmt::format_to(ctx.out(), "({}), ({}), ({})", type[0], type[1], type[2]);
    }
};
template<>
struct fmt::formatter<glm::mat4>
{
    template<typename ParseContext>
    constexpr auto parse(ParseContext& ctx)
    {
        return ctx.begin();
    }
    template<typename FormatContext>
    auto format(const glm::mat4& type, FormatContext& ctx)
    {
        return fmt::format_to(ctx.out(), "({}), ({}), ({}), ({})", type[0], type[1], type[2], type[3]);
    }
};