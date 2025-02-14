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
    Model(std::string const& path, bool gamma = false);

    glm::vec3& getPosition() { return m_position; }
    glm::vec3& getRotation() { return m_rotation; }

    // draws the model, and thus all its meshes
    void Draw(Shader& shader, float heightScale, const glm::vec3& directionalLightPosition, const glm::vec3& ambientLightColor, const float ambientLightStrength);

private:
    void loadModel(std::string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
    glm::mat4 m_model{ 1.0f };
    glm::vec3 m_position{ glm::vec3{m_model[3]} };
    glm::vec3 m_rotation{ glm::vec3{m_model[2]} };
};