#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>

class Mesh {
public:
    Mesh(int slices = 32, int stacks = 32); // slices и stacks для UV-сферы
    ~Mesh();
    void draw() const;
private:
    GLuint VAO, VBO, EBO;
    std::vector<float> vertices; // Позиции, нормали, текстурные координаты
    std::vector<unsigned int> indices; // Индексы для EBO
    void generateSphere(int slices, int stacks);
};