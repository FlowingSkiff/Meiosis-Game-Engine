#pragma once
#include <string>
namespace Meiosis::Util
{
    std::string filenameFromPath(const std::string& file_path, bool remove_extension = false);
}