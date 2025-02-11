#pragma once
#include "Shader.h"
#include "Core/Camera.h"
#include <Models/Model.h>

class Logger;
struct GLFWwindow;
struct ImGuiIO;

class Renderer
{
public:
	Renderer(GLFWwindow* nativeWindow);
	~Renderer();

	void clear() const;
	void render();
	void beginImguiFrame() const;
	void endImguiFrame() const;

private:
	void setupOpenGL();
	void setupImgui(GLFWwindow* window);
	std::wstring OpenFileDialog();

private:
	Logger& m_logger;
	Model* m_model{ nullptr };
	Shader* m_shader{ nullptr };
};

