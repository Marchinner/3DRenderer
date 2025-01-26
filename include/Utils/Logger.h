#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <mutex>
#include <memory>

class Logger
{
public:
	// Log levels
	enum class Level
	{
		Info,
		Warning,
		Error,
		Debug
	};

	// Singleton instance
	static Logger& getInstance();

	// Log messages
	void log(const std::string& message, Level logLevel = Level::Info);

	// Set log file
	void setLogFile(const std::string& filePath);

	// Enable or disable logging to file
	void enableFileLogging(bool enable);

private:
	Logger();
	~Logger();
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;

	std::ofstream m_logFile;
	bool m_fileLogging;
	std::mutex m_mutex;

	// Helper to convert Level to string
	std::string levelToString(Level level);
};

