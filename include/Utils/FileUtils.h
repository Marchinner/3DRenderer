#pragma once

#include <string>
#include <vector>

class FileUtils
{
public:
	static std::string readAsString(const std::string& filePath);
	static std::vector<char> readAsBinary(const std::string& filePath);
	static bool fileExists(const std::string& filePath);

private:
	static void logError(const std::string& message);
};

