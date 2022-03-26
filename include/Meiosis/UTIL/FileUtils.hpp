#pragma once
#include "Meiosis/Core/Core.hpp"
#include <string>
namespace Meiosis::Util
{
    std::string ME_API filenameFromPath(const std::string& file_path, bool remove_extension = false);
}