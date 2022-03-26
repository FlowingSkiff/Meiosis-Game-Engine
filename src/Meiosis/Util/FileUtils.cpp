#include "Meiosis/Util/FileUtils.hpp"
#include <algorithm>
namespace Meiosis::Util
{
    std::string filenameFromPath(const std::string& file_path, bool remove_extension)
    {
        const auto last_slash = file_path.find_last_of('/');
        const auto last_period = [&]() -> size_t{ 
            if (!remove_extension) 
                return 0;
            return file_path.find_last_of('.');
        }();
        return (last_period) ? file_path.substr(last_slash, last_period) : file_path.substr(last_slash);
    }
}