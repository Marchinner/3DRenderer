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
	, m_tShader{ nullptr }
	, m_tVAO{ 0 }
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
	Renderer::setupTriangle();
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
	m_tShader->use();
	glBindVertexArray(m_tVAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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

void Renderer::setupTriangle()
{
	m_tShader = new Shader("assets/shaders/triangle.vert", "assets/shaders/triangle.frag");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};

	unsigned int VBO;
	unsigned int EBO;
	glGenVertexArrays(1, &m_tVAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(m_tVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);
}
