#pragma once
#include <vector>
#include <string>
#include <Rendering/Shader.h>

class Skybox
{
public:
    Skybox(Shader& shader);
    
    void Draw(Shader& shader);

private:
    unsigned int loadCubemap(std::vector<std::string> faces);
    unsigned int m_cubemapTexture{ 0 };
    unsigned int m_skyboxVAO{ 0 };
};

