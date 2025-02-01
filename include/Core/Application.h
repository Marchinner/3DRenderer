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
	void processInput();
	void shutdown();

private:
	void showMetrics() const;

private:
	Logger& m_logger;
	Window* m_window;
	Renderer* m_renderer;
	float m_deltaTime{ 0.0f };
	float m_lastFrame{ 0.0f };
};

