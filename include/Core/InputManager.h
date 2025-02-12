#pragma once

#include <GLFW/glfw3.h>
#include <array>
#include <Core/Camera.h>
#include "OrbitCamera.h"

class InputManager
{
public:
	static void keyCallback(GLFWwindow* window, int key, int scancode,
		int action, int mods)
	{
		if (action == GLFW_PRESS) m_keysPressed[key] = true;
		if (action == GLFW_RELEASE) m_keysPressed[key] = false;
	}

	static bool isKeyDown(int key) { return m_keysPressed[key]; }
	static void mouseCallback(GLFWwindow* window, double xPos, double yPos);
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static bool isMouseButtonDown(int button) { return m_mouseButtonsPressed[button]; }
	static void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);
	static Camera* getCamera();
	static OrbitCamera* getOrbitCamera();

	static void orbitMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void orbitCursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
	static void orbitScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
private:
	inline static std::array<bool, 512> m_keysPressed{};
	inline static std::array<bool, 512> m_mouseButtonsPressed{};
	inline static Camera* m_camera = new Camera();
	inline static OrbitCamera* m_orbitCamera = new OrbitCamera();
	inline static bool m_firstMouse = true;
	inline static float m_lastX{ 1280.0f / 2.0f };
	inline static float m_lastY{ 720.0f / 2.0f };
};

