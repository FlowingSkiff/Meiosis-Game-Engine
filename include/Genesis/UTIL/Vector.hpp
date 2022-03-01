#pragma once
#include <iterator>

namespace Util
{
namespace implemenation
{
    constexpr std::size_t getSizeInFour(std::size_t s)
    {
        return 4 * (s / 4 + (bool)(s % 4));
    }
    template<typename Type, std::size_t Size>
    struct vec_impl
    {
        explicit vec_impl()
        {
            for (auto& v : data)
                v = Type(0);
        }
        Type data[getSizeInFour(Size)];
    };
    template<typename Type>
    struct vec_impl<Type, 4>
    {
        explicit vec_impl()
        {
            for (auto& v : data)
                v = Type(0);
        }
        union {
            Type x, y, z, w;
            Type r, b, g, a;
            Type data[getSizeInFour(4)];
        };
    };
    template<typename Type>
    struct vec_impl<Type, 3>
    {
        explicit vec_impl()
        {
            for (auto& v : data)
                v = Type(0);
        }
        union {
            Type x, y, z;
            Type r, b, g;
            Type data[getSizeInFour(3)];
        };
    };
}// namespace implemenation
template<typename Type, std::size_t Size>
struct Vector : public implemenation::vec_impl<Type, Size>
{
  public:
    explicit Vector() : implemenation::vec_impl<Type, Size>() {}
    auto* begin() { return std::begin(this->data); }
    auto* end() { return std::end(this->data); }

  private:
};
}// namespace Util