#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Rendering/Renderer.h"
#include "Utils/Logger.h"
#include "Core/InputManager.h"
#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <stb/stb_image.h>
#include <stdlib.h>
#include <Windows.h>
#include <commdlg.h>

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

    m_shader = new Shader("shaders/default.vert", "shaders/default.frag");
}

Renderer::~Renderer() {}

void Renderer::clear() const
{
    // Clear the screen with a color
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::render()
{
    glm::mat4 proj = InputManager::getCamera()->getProjection();
    glm::mat4 view = InputManager::getOrbitCamera()->getViewMatrix();

    m_shader->use();
    m_shader->setMat4("projection", proj);
    m_shader->setMat4("view", view);

    // render the loaded model
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
    m_shader->setMat4("model", model);
    m_shader->setVec3("directionalLightPosition", m_directionalLightPosition);
    m_shader->setFloat("ambientLightStrenght", m_ambientLightStrenght);
    m_shader->setVec3("lightColor", m_ambientLightColor);
    m_shader->setVec3("viewPos", InputManager::getOrbitCamera()->getCameraPosition());

    if (m_model)
        m_model->Draw(*m_shader);

    ImGui::BeginMainMenuBar();
    if (ImGui::BeginMenu("Model"))
    {
        ImGui::MenuItem("Invert Texture on Load", "", &m_bInvertTextureOnLoad);
        if (ImGui::MenuItem("Open"))
        {
            std::wstring filename = OpenFileDialog();

            if (!filename.empty())
            {
                size_t required_size = 0;
                errno_t err = wcstombs_s(&required_size, nullptr, 0, filename.c_str(), 0);
                if (err == 0 || required_size != 0)
                {
                    std::string str(required_size, '\0');
                    wcstombs_s(&required_size, &str[0], required_size, filename.c_str(), required_size - 1);

                    str.pop_back();

                    if (m_bInvertTextureOnLoad)
                    {
                        stbi_set_flip_vertically_on_load(true);
                    }
                    else
                    {
                        stbi_set_flip_vertically_on_load(false);
                    }
                    m_model = new Model(str);
                }
            }
        }

        if (m_model)
        {
            if (ImGui::MenuItem("Close"))
            {
                m_model = nullptr;
            }
        }

        ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Ambient Light"))
    {
        ImGui::DragFloat("Strength", &m_ambientLightStrenght, 0.01f, 0.0f, 1.0f);
        ImGui::ColorEdit3("Color", glm::value_ptr(m_ambientLightColor));
        ImGui::EndMenu();
    }

    if (ImGui::BeginMenu("Directional Light"))
    {
        ImGui::DragFloat("Strength", &m_ambientLightStrenght, 0.01f, 0.0f, 1.0f);
        ImGui::DragFloat3("Position", glm::value_ptr(m_directionalLightPosition));
        ImGui::EndMenu();
    }

    ImGui::EndMainMenuBar();
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
    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    //stbi_set_flip_vertically_on_load(true);
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

std::wstring Renderer::OpenFileDialog()
{
    OPENFILENAME ofn;
    wchar_t szFile[MAX_PATH] = { 0 };
    ZeroMemory(&ofn, sizeof(ofn));

    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFilter = L"Models\0*.obj\0All Files\0*.*\0";
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;

    if (GetOpenFileNameW(&ofn))
        return std::wstring(szFile);

    return L"";
}
