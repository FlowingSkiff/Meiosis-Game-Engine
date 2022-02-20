#include "Util/Random.hpp"
#include <random>


namespace Util
{
float randF()
{
    return static_cast<float>(randD());
}
double randD()
{
    static std::random_device device;
    static std::mt19937 generator(device);
    static std::uniform_real_distribution<> distribution(0.0, 1.0);
    return distribution(generator);
}
}// namespace Util