#pragma once
#include "Window.h"
#include <Rendering/Renderer.h>
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
	Window* m_window;
	Renderer* m_renderer;
};

