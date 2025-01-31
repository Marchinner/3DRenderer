#include "Rendering/Renderer.h"
#include "Utils/Logger.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext/matrix_transform.hpp>

Renderer::Renderer(GLFWwindow* nativeWindow)
    : m_logger{ Logger::getInstance() }
{
    m_logger.log("Initializing renderer...", Logger::Level::Info);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        m_logger.log("Failed to initialize Glad", Logger::Level::Error);
        exit(EXIT_FAILURE);
    }

    // Setup OpenGL debug callback
    glDebugMessageCallback([](GLenum source, GLenum type, GLuint id,
        GLenum severity, GLsizei lenght, const GLchar* message, const void* userParam)
        {
            if (severity > GL_DEBUG_SEVERITY_NOTIFICATION)
            {
                std::cerr << "GL ERROR: " << message << std::endl;
            }
        }, nullptr);
    glEnable(GL_DEBUG_OUTPUT);

    // OpenGL settings
    Renderer::setupOpenGL();
    Renderer::setupImgui(nativeWindow);

    m_triangle = new Triangle();
    m_rectangle = new Rectangle();
    m_cube = new Cube();
}

Renderer::~Renderer() {}

void Renderer::clear() const
{
    // Clear the screen with a color
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::render() const
{
    //m_triangle->draw();
    //m_rectangle->draw();

    // Camera position
    glm::vec3 cameraPos = glm::vec3{ 0.0f, 0.0f, 3.0f };

    // Camera direction
    glm::vec3 cameraTarget = glm::vec3{ 0.0f, 0.0f, 0.0f }; // looking to origin
    glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget); // subtract and normalize

    // Right camera axis
    glm::vec3 up = glm::vec3{ 0.0f, 1.0f, 0.0f };
    glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));

    // Up camera vector
    glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);

    // Look At
    //glm::mat4 view;
    //view = glm::lookAt(glm::vec3{ 0.0f, 0.0f, 3.0f },	// camera position
    //    glm::vec3{ 0.0f, 0.0f, 0.0f },	// target position
    //    glm::vec3{ 0.0f, 1.0f, 0.0f });	// up vector

    const float radius = 10.0f;
    float camX = sin(glfwGetTime()) * radius;
    float camZ = cos(glfwGetTime()) * radius;
    glm::mat4 view = glm::lookAt(glm::vec3{ camX, 0.0f, camZ }, glm::vec3{ 0.0f, 0.0f, 0.0f }, glm::vec3{ 0.0f, 1.0f, 0.0f });
    m_cube->getViewMatrix() = view;

    ImGui::Begin("Camera");
    ImGui::InputFloat3("View", glm::value_ptr(view), "%.1f");
    ImGui::DragFloat3("Projection", glm::value_ptr(m_cube->getProjectionMatrix()), 0.001f, -100.0f, 100.0f, "%.1f");
    ImGui::End();

    m_cube->draw();
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
    glEnable(GL_DEPTH_TEST);
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