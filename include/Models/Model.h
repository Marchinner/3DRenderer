#pragma once
#include <Rendering/Shader.h>
#include <vector>
#include <string>
#include "Mesh.h"
#include "Utils/Logger.h"
#include "assimp/scene.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Core/InputManager.h>

unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);

class Model
{
public:
    // model data 
    std::vector<Texture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    std::vector<Mesh>    meshes;
    std::string directory;
    bool gammaCorrection;

    // constructor, expects a filepath to a 3D model.
    Model(std::string const& path, bool gamma = false) : gammaCorrection(gamma)
    {
        loadModel(path);

        m_model = glm::translate(m_model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
        m_model = glm::scale(m_model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
    }

    glm::vec3& getPosition() { return m_position; }
    glm::vec3& getRotation() { return m_rotation; }

    // draws the model, and thus all its meshes
    void Draw(Shader& shader, float heightScale, const glm::vec3& directionalLightPosition, const glm::vec3& ambientLightColor, const float ambientLightStrength)
    {
        glm::mat4 proj = InputManager::getCamera()->getProjection();
        glm::mat4 view = InputManager::getOrbitCamera()->getViewMatrix();

        shader.use();
        shader.setMat4("projection", proj);
        shader.setMat4("view", view);

        m_model = glm::mat4(1.0f);
        m_model = glm::translate(m_model, getPosition());
        m_model = glm::rotate(m_model, glm::radians(getRotation().x), glm::vec3{ 1.0f, 0.0f, 0.0f });
        m_model = glm::rotate(m_model, glm::radians(getRotation().y), glm::vec3{ 0.0f, 1.0f, 0.0f });
        m_model = glm::rotate(m_model, glm::radians(getRotation().z), glm::vec3{ 0.0f, 0.0f, 1.0f });


        // render the loaded model
        shader.setMat4("model", m_model);
        shader.setFloat("heightScale", heightScale);
        shader.setVec3("lightPos", directionalLightPosition);
        shader.setVec3("ambientLightColor", ambientLightColor);
        shader.setFloat("ambientLightStrength", ambientLightStrength);
        //shader.setVec3("viewPos", InputManager::getOrbitCamera()->getCameraPosition());

        for (unsigned int i = 0; i < meshes.size(); i++)
            meshes[i].Draw(shader);
    }

private:
    void loadModel(std::string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
    glm::mat4 m_model{ 1.0f };
    glm::vec3 m_position{ glm::vec3{m_model[3]} };
    glm::vec3 m_rotation{ glm::vec3{m_model[2]} };
};