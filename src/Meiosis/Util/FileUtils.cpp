#include "Meiosis/Util/FileUtils.hpp"
#include <algorithm>
namespace Meiosis::Util
{
std::string filenameFromPath(const std::string& file_path, bool remove_extension)
{
    std::string cpy = file_path;
    std::replace(cpy.begin(), cpy.end(), '\\', '/');
    const auto last_slash = [&]() -> size_t {
        const auto lst = cpy.find_last_of('/');
        return (lst != std::string::npos) ? lst + 1 : 0;
    }();
    const auto last_period = [&]() -> size_t {
        const auto lst = cpy.find_last_of('.');
        if (!remove_extension || lst == std::string::npos)
            return cpy.size();
        return lst;
    }();
    // const auto length = cpy.size() - last_slash - (cpy.size() - last_period);
    const auto length = last_period - last_slash;
    return cpy.substr(last_slash, length);
}
}// namespace Meiosis::Util