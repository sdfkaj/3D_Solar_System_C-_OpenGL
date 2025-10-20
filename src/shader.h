
#define SHADER_H

#pragma once
#include <string>
#include <glm/glm.hpp>
#include <GL/glew.h>  
#include <GLFW/glfw3.h> 

class Shader {
public:

    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    void use();
    void setMat4(const std::string& name, const glm::mat4& mat) const;
    void setInt(const std::string& name, int value) const;

private:
    GLuint programID;
    GLuint compileShader(GLenum type, const std::string& source);
    std::string readFile(const std::string& filePath);
};
