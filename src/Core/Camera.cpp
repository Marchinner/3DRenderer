#include "Core/Camera.h"
#include <Core/InputManager.h>
#include <GLFW/glfw3.h>

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : m_position{ position }
    , m_front{ glm::vec3{0.0f, 0.0f, -1.0f} }
    , m_up{ }
    , m_right{ }
    , m_worldUp{ up }
    , m_yaw{ yaw }
    , m_pitch{ pitch }
    , m_movementSpeed{ SPEED }
    , m_mouseSensitivity{ SENSITIVITY }
    , m_zoom{ ZOOM }
{
    updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
    : m_position{ glm::vec3{posX, posY, posZ} }
    , m_front{ glm::vec3{0.0f, 0.0f, -1.0f} }
    , m_up{ }
    , m_right{ }
    , m_worldUp{ glm::vec3{upX, upY, upZ} }
    , m_yaw{ yaw }
    , m_pitch{ pitch }
    , m_movementSpeed{ SPEED }
    , m_mouseSensitivity{ SENSITIVITY }
    , m_zoom{ ZOOM }
{
    updateCameraVectors();
}

void Camera::processKeyboard(CameraMovement direction, float deltaTime)
{
    float velocity = m_movementSpeed * deltaTime;

    if (direction == CameraMovement::FORWARD)
        m_position += m_front * velocity;

    if (direction == CameraMovement::BACKWARD)
        m_position -= m_front * velocity;

    if (direction == CameraMovement::LEFT)
        m_position -= m_right * velocity;

    if (direction == CameraMovement::RIGHT)
        m_position += m_right * velocity;
}

void Camera::processMouseMovement(float xOffset, float yOffset)
{
    if (InputManager::isMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT))
    {
        bool constrainPitch = true;
        xOffset *= m_mouseSensitivity;
        yOffset *= m_mouseSensitivity;

        m_yaw += xOffset;
        m_pitch += yOffset;

        // make sure that when pitch is out of bounts, screen doesn't get flipped
        if (constrainPitch)
        {
            if (m_pitch > 89.0f)
                m_pitch = 89.0f;

            if (m_pitch < -89.0f)
                m_pitch = -89.0f;
        }

        updateCameraVectors();
    }
}

void Camera::processMouseScroll(float yOffset)
{
    m_zoom -= yOffset;

    if (m_zoom < 1.0f)
        m_zoom = 1.0f;

    if (m_zoom > 45.0f)
        m_zoom = 45.0f;
}

void Camera::updateCameraVectors()
{
    // calculate the new front vector
    glm::vec3 front;
    front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    front.y = sin(glm::radians(m_pitch));
    front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_front = glm::normalize(front);
   
    // re-calculate the right and up vector
    m_right = glm::normalize(glm::cross(m_front, m_worldUp));
    m_up = glm::normalize(glm::cross(m_right, m_front));
}
