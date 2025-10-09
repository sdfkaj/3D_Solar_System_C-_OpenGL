#pragma once
#include <glm/glm.hpp>
#include "shader.h"
#include "mesh.h"

class Planet {
public:
    Planet(const std::string& name, float radius, float distance, float orbitSpeed, const std::string& texturePath);
    void update(float time);
    void draw(const Shader& shader);
private:
    std::string name;
    float radius;
    float distance; 
    float orbitSpeed; 
    float rotationSpeed;
    glm::mat4 modelMatrix; 
    Mesh mesh; 
    GLuint textureID; 
};