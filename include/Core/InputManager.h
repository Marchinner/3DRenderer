#pragma once

#include <GLFW/glfw3.h>
#include <array>

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

private:
	inline static std::array<bool, 512> m_keysPressed{};
};

