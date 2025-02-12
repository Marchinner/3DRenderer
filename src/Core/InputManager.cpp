#include "Core/InputManager.h"

void InputManager::mouseCallback(GLFWwindow* window, double xPos, double yPos)
{
    float xpos = static_cast<float>(xPos);
    float ypos = static_cast<float>(yPos);

    if (m_firstMouse)
    {
        m_lastX = xpos;
        m_lastY = ypos;
        m_firstMouse = false;
    }

    float xoffset = xpos - m_lastX;
    float yoffset = m_lastY - ypos; // reversed sinse y-coordinates go from bottom to top

    m_lastX = xpos;
    m_lastY = ypos;

    m_camera->processMouseMovement(xoffset, yoffset);
}

void InputManager::scrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
    m_camera->processMouseScroll(static_cast<float>(yOffset));
}

void InputManager::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (action == GLFW_PRESS) m_mouseButtonsPressed[button] = true;
    if (action == GLFW_RELEASE) m_mouseButtonsPressed[button] = false;
}

Camera* InputManager::getCamera()
{
    return m_camera;
}

OrbitCamera* InputManager::getOrbitCamera()
{
    return m_orbitCamera;
}

void InputManager::orbitMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    m_orbitCamera->mouseButtonCallback(button, action);
}

void InputManager::orbitCursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
    m_orbitCamera->cursorPositionCallback(xpos, ypos);
}

void InputManager::orbitScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    m_orbitCamera->processMouseScroll(yoffset);
}
