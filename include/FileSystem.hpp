#ifndef FILE_SYSTEM_HPP
#define FILE_SYSTEM_HPP

#include <iostream>
#include <fstream>

class FileSystem
{
public:
    static std::string ReadTextFromFile(const std::string&filePath);
};

#endif //FILE_SYSTEM_HPP
