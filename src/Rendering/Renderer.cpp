#include "Rendering/Renderer.h"
#include "Utils/Logger.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <iostream>

Renderer::Renderer(GLFWwindow* nativeWindow)
	: m_logger{ Logger::getInstance() }
{
	m_logger.log("Initializing renderer...", Logger::Level::Info);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		m_logger.log("Failed to initialize Glad", Logger::Level::Error);
		exit(EXIT_FAILURE);
	}

	// OpenGL settings
	Renderer::setupOpenGL();
	Renderer::setupImgui(nativeWindow);
}

Renderer::~Renderer() {}

void Renderer::clear() const
{
	// Clear the screen with a color
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::render() const
{
	// Rendering logic here
}

void Renderer::beginImguiFrame() const
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void Renderer::endImguiFrame() const
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

ImGuiIO& Renderer::getImguiIo() const
{
	return ImGui::GetIO();
}

void Renderer::setupOpenGL()
{
	glEnable(GL_DEPTH_TEST);  // Enable depth testing
	glDepthFunc(GL_LESS);    // Depth testing function
	glEnable(GL_CULL_FACE);  // Enable backface culling
	glCullFace(GL_BACK);     // Cull back faces
	glFrontFace(GL_CCW);     // Counter-clockwise front faces

	m_logger.log("Setting OpenGL settings...", Logger::Level::Info);
}

void Renderer::setupImgui(GLFWwindow* window)
{
	m_logger.log("Initializing ImGui...", Logger::Level::Info);
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 460");
}
