#include "Core/OrbitCamera.h"
#include <algorithm>

OrbitCamera::OrbitCamera(glm::vec3 target, float distance)
    : target{target}
    , distance{ distance }
    , yaw{ 0.0f }
    , pitch{0.0f}
    , sensitivity{0.005f}
    , zoomSpeed{1.2f}
    , panSpeed{0.01f}
    , rotating{false}
    , panning{false}
    , lastX{ 0 }
    , lastY{ 0 }
{
}

glm::mat4 OrbitCamera::getViewMatrix() const
{
    glm::vec3 position = getCameraPosition();
    return glm::lookAt(position, target, glm::vec3{ 0.0f, 1.0f, 0.0f });
}

glm::vec3 OrbitCamera::getCameraPosition() const
{
    return glm::vec3{
        distance * cos(pitch) * yaw,
        distance * sin(pitch),
        distance * cos(pitch) * cos(yaw)
    } + target;
}

void OrbitCamera::processMouseMovement(float deltaX, float deltaY)
{
    yaw += deltaX * sensitivity;
    pitch -= deltaY * sensitivity;

    pitch = std::clamp(pitch, -glm::half_pi<float>() + 0.1f, glm::half_pi<float>() - 0.1f);
}

void OrbitCamera::processMouseScroll(float offset)
{
    distance *= (offset > 0) ? (1.0f / zoomSpeed) : zoomSpeed;
    distance = std::clamp(distance, 1.0f, 50.f);
}

void OrbitCamera::processPan(float deltaX, float deltaY)
{
    glm::vec3 right = glm::normalize(glm::cross(getCameraPosition() - target, glm::vec3{ 0, 1, 0 }));
    glm::vec3 up = glm::vec3(0, 1, 0);

    target -= right * deltaX * panSpeed;
    target += up * deltaY * panSpeed;
}

void OrbitCamera::mouseButtonCallback(int button, int action)
{
    if (button == GLFW_MOUSE_BUTTON_MIDDLE)
    {
        if (action == GLFW_PRESS)
        {
            rotating = true;
        }
        else if (action == GLFW_RELEASE)
        {
            rotating = false;
        }
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT)
    {
        if (action == GLFW_PRESS)
        {
            panning = true;
        }
        else if (action == GLFW_RELEASE)
        {
            panning = false;
        }
    }
}

void OrbitCamera::cursorPositionCallback(double xpos, double ypos)
{
    if (rotating || panning)
    {
        float deltaX = static_cast<float>(xpos - lastX);
        float deltaY = static_cast<float>(ypos - lastY);

        if (rotating)
        {
            processMouseMovement(deltaX, deltaY);
        }

        if (panning)
        {
            processPan(deltaX, deltaY);
        }
    }

    lastX = xpos;
    lastY = ypos;
}

void OrbitCamera::scrollCallback(double yoffset)
{
    processMouseScroll(static_cast<float>(yoffset));
}
