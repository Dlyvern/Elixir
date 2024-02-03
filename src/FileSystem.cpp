#include "FileSystem.hpp"

std::string FileSystem::ReadTextFromFile(const std::string &filePath)
{
    if(filePath.empty()) return {};

    std::ifstream file(filePath);
    std::string str;
    std::string line;

    while (std::getline(file, line))
        str += line + "\n";

    return str;
}

