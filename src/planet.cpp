#include "planet.h"

#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace {
GLenum channelsToFormat(int channels) {
    switch (channels) {
        case 1:
            return GL_RED;
        case 3:
            return GL_RGB;
        case 4:
            return GL_RGBA;
        default:
            return GL_RGB;
    }
}
}  // namespace

Planet::Planet(const std::string& name,
               float radius,
               float distance,
               float orbitSpeed,
               const std::string& texturePath)
    : name(name), radius(radius), distance(distance), orbitSpeed(orbitSpeed), rotationSpeed(0.1f) {
    mesh = Mesh(32, 32);

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    stbi_set_flip_vertically_on_load(true);

    int width = 0;
    int height = 0;
    int channels = 0;

    unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &channels, 0);
    if (!data) {
        std::cerr << "Failed to load texture: " << texturePath << std::endl;
        return;
    }

    GLenum format = channelsToFormat(channels);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
}

Planet::~Planet() {
    if (textureID != 0) {
        glDeleteTextures(1, &textureID);
    }
}

void Planet::update(float time) {
    float angle = orbitSpeed * time;
    glm::vec3 position(distance * cos(angle), 0.0f, distance * sin(angle));
    modelMatrix = glm::translate(glm::mat4(1.0f), position);
    modelMatrix = glm::scale(modelMatrix, glm::vec3(radius));
    modelMatrix = glm::rotate(modelMatrix, rotationSpeed * time, glm::vec3(0.0f, 1.0f, 0.0f));
}

void Planet::draw(const Shader& shader) {
    shader.setMat4("model", modelMatrix);
    shader.setInt("texture1", 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    mesh.draw();
}
