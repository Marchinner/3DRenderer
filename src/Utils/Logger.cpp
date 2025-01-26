#include "Utils\Logger.h"

Logger::Logger()
	: m_fileLogging{ false } {
}

Logger::~Logger()
{
	if (m_logFile.is_open())
	{
		m_logFile.close();
	}
}

Logger& Logger::getInstance()
{
	static Logger instance;
	return instance;
}

void Logger::log(const std::string& message, Level logLevel)
{
	std::lock_guard<std::mutex> lock(m_mutex); // Ensure thread safety

	std::string logMessage = "[" + levelToString(logLevel) + "] " + message;

	// Write to console
	std::cout << logMessage << std::endl;

	// Write to file
	if (m_logFile.is_open() && m_fileLogging)
	{
		m_logFile << logMessage << std::endl;
	}
}

void Logger::setLogFile(const std::string& filePath)
{
	std::lock_guard<std::mutex> lock(m_mutex);

	if (m_logFile.is_open())
	{
		m_logFile.close();
	}

	m_logFile.open(filePath, std::ios::out | std::ios::app);
	if (!m_logFile)
	{
		std::cerr << "[Logger Error] Failed to open log file: " << filePath;
	}
}

void Logger::enableFileLogging(bool enable)
{
	m_fileLogging = enable;
}

std::string Logger::levelToString(Level level)
{
	switch (level)
	{
	case Logger::Level::Info:
		return "INFO";
	case Logger::Level::Warning:
		return "WARNING";
	case Logger::Level::Error:
		return "ERROR";
	case Logger::Level::Debug:
		return "DEBUG";
	default:
		return "UNKNOWN";
	}
}
