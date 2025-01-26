#pragma once

class Window;
class Renderer;
class Logger;

class Application
{
public:
	Application();
	~Application();

	bool initialize();
	void run();
	void shutdown();

private:
	void showMetrics() const;

private:
	Logger& m_logger;
	Window* m_window;
	Renderer* m_renderer;
};

