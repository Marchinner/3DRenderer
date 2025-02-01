#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum class CameraMovement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

const float YAW = -90.f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera
{
public:
    Camera(glm::vec3 position = glm::vec3{ 0.0f, 0.0f, 0.0f },
        glm::vec3 up = glm::vec3{ 0.0f, 1.0f, 0.0f }, float yaw = YAW, float pitch = PITCH);
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ,
        float yaw, float pitch);

    glm::mat4 getViewMatrix() { return glm::lookAt(m_position, m_position + m_front, m_up); }
    glm::mat4 getProjection() { return glm::perspective(glm::radians(m_zoom), 1280.0f / 720.0f, 0.1f, 100.0f); }
    void processKeyboard(CameraMovement direction, float deltaTime);
    void processMouseMovement(float xOffset, float yOffset);
    void processMouseScroll(float yOffset);

public:
    // Attributes
    glm::vec3 m_position;
    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::vec3 m_right;
    glm::vec3 m_worldUp;

    // euler angles
    float m_yaw;
    float m_pitch;
    
    // camera options
    float m_movementSpeed;
    float m_mouseSensitivity;
    float m_zoom;

private:
    void updateCameraVectors();
};

