#include "Core\Window.h"
#include <iostream>

Window::Window(const std::string& windowTitle, int windowWidth, int windowHeight)
	: m_title{ windowTitle }, m_width{ windowWidth }, m_height{ windowHeight }, m_window{ nullptr }
{
}

Window::~Window()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

bool Window::initialize()
{
	if (!glfwInit())
	{
		std::cerr << "Failed to initialize GLFW!" << std::endl;
		return false;
	}

	// Set GLFW window hints
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
	if (!m_window)
	{
		std::cerr << "Failed to create GLFW window!" << std::endl;
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(m_window);

	// Register callback for resizing
	glfwSetFramebufferSizeCallback(m_window, framebufferSizeCallback);

	// Enable V-Sync
	glfwSwapInterval(1);

	return true;
}

void Window::pollEvents() const
{
	glfwPollEvents();
}

void Window::swapBuffers() const
{
	glfwSwapBuffers(m_window);
}

bool Window::shouldClose() const
{
	return glfwWindowShouldClose(m_window);
}

void Window::framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}
