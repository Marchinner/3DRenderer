#include "Utils\FileUtils.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>
#include <Utils/Logger.h>

std::string FileUtils::readAsString(const std::string& filePath)
{
    Logger& logger = logger.getInstance();

    if (!fileExists(filePath))
    {
        logger.log("[FileLoader][ReadAsString] File not found: " + filePath, Logger::Level::Error);
        return "";
    }

    std::ifstream file(filePath, std::ios::in);
    if (!file.is_open())
    {
        logger.log("[FileLoader][ReadAsString] Failed to open file: " + filePath, Logger::Level::Error);
        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    return buffer.str();
}

std::vector<char> FileUtils::readAsBinary(const std::string& filePath)
{
    Logger& logger = logger.getInstance();

    if (!fileExists(filePath))
    {
        logger.log("[FileLoader][ReadAsBinary] File not found: " + filePath, Logger::Level::Error);
        return {};
    }

    std::ifstream file(filePath, std::ios::ate | std::ios::binary);
    if (!file.is_open())
    {
        logger.log("[FileLoader][ReadAsBinary] Failed to read file: " + filePath, Logger::Level::Error);
        return {};
    }

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<char> buffer(size);
    if (!file.read(buffer.data(), size))
    {
        logger.log("[FileLoader][ReadAsBinary] Failed to read file: " + filePath, Logger::Level::Error);
        return {};
    }

    file.close();
    return buffer;
}

bool FileUtils::fileExists(const std::string& filePath)
{
    return std::filesystem::exists(filePath);
}

void FileUtils::logError(const std::string& message)
{
    std::cerr << "[FileLoader Error] " << message << std::endl;
}
