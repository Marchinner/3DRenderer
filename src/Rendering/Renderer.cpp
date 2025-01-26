#include "Rendering\Renderer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <iostream>

Renderer::Renderer(GLFWwindow* nativeWindow)
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize Glad!" << std::endl;
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

	std::cout << "OpenGL settings initialized." << std::endl;
}

void Renderer::setupImgui(GLFWwindow* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 460");

	std::cout << "ImGui initialized." << std::endl;
}
