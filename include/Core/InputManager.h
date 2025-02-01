#pragma once

#include <GLFW/glfw3.h>
#include <array>
#include <Rendering/Camera.h>

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
	static void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);
	static Camera* getCamera();
private:
	inline static std::array<bool, 512> m_keysPressed{};
	inline static Camera* m_camera = new Camera();
	inline static bool m_firstMouse = true;
	inline static float m_lastX{ 1280.0f / 2.0f };
	inline static float m_lastY{ 720.0f / 2.0f };
};

