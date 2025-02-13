#include "Core/Window.h"
#include "Utils/Logger.h"
#include "Core/InputManager.h"

#include <GLFW/glfw3.h>
#include <iostream>

#define ORBIT_CAMERA

Window::Window(const std::string& windowTitle, int windowWidth, int windowHeight)
    : m_logger{ Logger::getInstance() }
    , m_title{ windowTitle }
    , m_width{ windowWidth }
    , m_height{ windowHeight }
    , m_window{ nullptr }
{
}

Window::~Window()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

bool Window::initialize()
{
    m_logger.log("Initializing GLFW...", Logger::Level::Info);
    if (!glfwInit())
    {
        m_logger.log("Failed to initialize GLFW", Logger::Level::Error);
        return false;
    }

    // Set GLFW window hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
    glfwWindowHint(GLFW_SAMPLES, 4);

    m_logger.log("Creating application window...", Logger::Level::Info);
    m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
    if (!m_window)
    {
        m_logger.log("Failed to create application window", Logger::Level::Error);
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(m_window);

    // Register callback for resizing
    m_logger.log("Registering window's callbacks...", Logger::Level::Info);
    glfwSetFramebufferSizeCallback(m_window, framebufferSizeCallback);

    // Enable V-Sync
    glfwSwapInterval(1);

    glfwSetKeyCallback(m_window, InputManager::keyCallback);
    // Camera
#ifndef ORBIT_CAMERA
    glfwSetCursorPosCallback(m_window, InputManager::mouseCallback);
    glfwSetScrollCallback(m_window, InputManager::scrollCallback);
    glfwSetMouseButtonCallback(m_window, InputManager::mouseButtonCallback);
#endif // !ORBIT_CAMERA

#ifdef ORBIT_CAMERA
    glfwSetCursorPosCallback(m_window, InputManager::orbitCursorPositionCallback);
    glfwSetScrollCallback(m_window, InputManager::orbitScrollCallback);
    glfwSetMouseButtonCallback(m_window, InputManager::orbitMouseButtonCallback);
#endif // ORBIT_CAMERA


    return true;
}

void Window::pollEvents() const
{
    glfwPollEvents();

    if (InputManager::isKeyDown(GLFW_KEY_ESCAPE))
    {
        glfwSetWindowShouldClose(m_window, GL_TRUE);
    }
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
