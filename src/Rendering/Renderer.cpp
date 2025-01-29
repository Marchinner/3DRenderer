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
	, m_triangle{ nullptr }
{
	m_logger.log("Initializing renderer...", Logger::Level::Info);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		m_logger.log("Failed to initialize Glad", Logger::Level::Error);
		exit(EXIT_FAILURE);
	}

	// Setup OpenGL debug callback
	glEnable(GL_DEBUG_OUTPUT);
	glDebugMessageCallback([](GLenum source, GLenum type, GLuint id,
		GLenum severity, GLsizei lenght, const GLchar* message, const void* userParam)
		{
			if (severity > GL_DEBUG_SEVERITY_NOTIFICATION)
			{
				std::cerr << "GL ERROR: " << message << std::endl;
			}
		}, nullptr);

	// OpenGL settings
	Renderer::setupOpenGL();
	Renderer::setupImgui(nativeWindow);

	m_triangle = new Triangle();
}

Renderer::~Renderer() {}

void Renderer::clear() const
{
	// Clear the screen with a color
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::render() const
{
	m_triangle->draw();
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

void Renderer::setupOpenGL()
{
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