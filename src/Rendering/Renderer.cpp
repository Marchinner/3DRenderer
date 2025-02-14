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
    m_lightbulbShader = new Shader("shaders/lightbulb.vert", "shaders/lightbulb.frag");
    m_skyboxShader = new Shader("shaders/skybox.vert", "shaders/skybox.frag");
    m_skybox = new Skybox(*m_skyboxShader);
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
    if (m_model)
        m_model->Draw(*m_shader, m_fHeightScale, m_directionalLightPosition, m_ambientLightColor, m_ambientLightStrenght);

    for (auto& lightBulb : m_lightBulbModels)
    {
        lightBulb->Draw(*m_lightbulbShader, m_fHeightScale, m_directionalLightPosition, m_ambientLightColor, m_ambientLightStrenght);
    }

    m_skyboxShader->use();
    glm::mat4 view{ glm::mat4{ glm::mat3{InputManager::getOrbitCamera()->getViewMatrix()} } };
    m_skyboxShader->setMat4("view", view);
    m_skyboxShader->setMat4("projection", InputManager::getCamera()->getProjection());

    m_skybox->Draw(*m_skyboxShader);

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

                    // restore working dir for other models
                    std::filesystem::current_path(m_path);
                }
            }
        }


        if (m_model)
        {
            if (ImGui::MenuItem("Close"))
            {
                m_model = nullptr;
            }

            if (m_model) {
                ImGui::Separator();

                ImGui::DragFloat3("Position", glm::value_ptr(m_model->getPosition()));
                ImGui::DragFloat3("Rotation", glm::value_ptr(m_model->getRotation()));
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

    if (ImGui::BeginMenu("Height Map"))
    {
        ImGui::DragFloat("Scale", &m_fHeightScale, 0.0005f, 0.0f, 1.0f);
        ImGui::EndMenu();
    }
    
    if (ImGui::BeginMenu("Point Lights", false))
    {
        for (size_t i = 0; i < m_lightBulbModels.size(); i++)
        {
            ImGui::PushID(i);
            ImGui::Text("Point Light %d", i);
            ImGui::DragFloat3("Position", glm::value_ptr(m_lightBulbModels[i]->getPosition()));
            //ImGui::ColorEdit3("Color", glm::value_ptr(m_lightBulbModels[i]->getColor()));
            //ImGui::DragFloat("Strength", &m_lightBulbModels[i]->getStrength(), 0.01f, 0.0f, 1.0f);
            ImGui::PopID();
        }
        if (ImGui::Button("Add Point Light"))
        {
            std::filesystem::path path = "assets/models/lightbulb/lightbulb.obj";
            m_lightBulbModels.push_back(new Model(path.string()));
        }
        ImGui::SameLine();
        if (m_lightBulbModels.size() > 0)
        {
            if (ImGui::Button("Remove Point Light"))
            {
                if (!m_lightBulbModels.empty())
                {
                    delete m_lightBulbModels.back();
                    m_lightBulbModels.pop_back();
                }
            }
        }

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
    glEnable(GL_MULTISAMPLE);
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
