#pragma once
#include <glm/glm.hpp>
#include "Shader.h"
#include "Core/Camera.h"
#include <Models/Model.h>
#include <Models/Skybox.h>
#include <filesystem>

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
    std::vector<Model*> m_lightBulbModels;
    Shader* m_shader{ nullptr };
    Shader* m_skyboxShader{ nullptr };
    Shader* m_lightbulbShader{ nullptr };
    Skybox* m_skybox{ nullptr };
    float m_fHeightScale{ 0 };
    bool m_bInvertTextureOnLoad{ false };
    glm::vec3 m_ambientLightColor{ 1.0f, 1.0f, 1.0f };
    float m_ambientLightStrenght{ 1.0f };
    glm::vec3 m_directionalLightPosition{ 1.0f, 1.0f, 1.0f };
    std::filesystem::path m_path{ std::filesystem::current_path() };
};

