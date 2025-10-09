#include "planet.h"
#include <stb_image.h>
#include <iostream>

Planet::Planet(const std::string& name, float radius, float distance, float orbitSpeed, const std::string& texturePath)
    : name(name), radius(radius), distance(distance), orbitSpeed(orbitSpeed), rotationSpeed(0.1f) {
    // Генерация сферы (упрощённо, можно использовать icosphere)
    mesh = Mesh(/* вершины и индексы сферы, сгенерированные заранее */);

    // Загрузка текстуры
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
    } else {
        std::cerr << "Failed to load texture: " << texturePath << std::endl;
    }
}

void Planet::update(float time) {
    // Обновление позиции (орбита) и вращения
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