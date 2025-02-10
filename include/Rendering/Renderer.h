#pragma once
#include "Shader.h"
#include <Models/Triangle.h>
#include <Models/Rectangle.h>
#include <Models/Cube.h>
#include "Core/Camera.h"

class Logger;
struct GLFWwindow;
struct ImGuiIO;

class Renderer
{
public:
	Renderer(GLFWwindow* nativeWindow);
	~Renderer();

	void clear() const;
	void render() const;
	void beginImguiFrame() const;
	void endImguiFrame() const;

private:
	void setupOpenGL();
	void setupImgui(GLFWwindow* window);

private:
	Logger& m_logger;
	Triangle* m_triangle{ nullptr };
	Rectangle* m_rectangle{ nullptr };
	Cube* m_cube{ nullptr };
};

