#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

class OrbitCamera
{
public:
    OrbitCamera(glm::vec3 target = glm::vec3{ 0.0f }, float distance = 5.0f);
    glm::mat4 getViewMatrix() const;
    glm::vec3 getCameraPosition() const;

    void processMouseMovement(float deltaX, float deltaY);
    void processMouseScroll(float offset);
    void processPan(float deltaX, float deltaY);

    void mouseButtonCallback(int button, int action);
    void cursorPositionCallback(double xpos, double ypos);
    void scrollCallback(double yoffset);

private:
    glm::vec3 target;
    float distance;
    float yaw;
    float pitch;

    float sensitivity;
    float zoomSpeed;
    float panSpeed;

    bool rotating;
    bool panning;
    double lastX, lastY;
};

