#pragma once
#include <string>

struct GLFWwindow;
class Logger;

class Window
{
public:
	Window(const std::string& windowTitle, int windowWidth, int windowHeight);
	~Window();

	bool initialize();
	void pollEvents() const;
	void swapBuffers() const;
	bool shouldClose() const;

	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }
	GLFWwindow* getNativeWindow() const { return m_window; }

private:
	static void framebufferSizeCallback(GLFWwindow* window, int width, int height);

	Logger& m_logger;
	std::string m_title;
	int m_width;
	int m_height;
	GLFWwindow* m_window;
};

