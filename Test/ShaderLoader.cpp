#include "ShaderLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>

ShaderLoader::ShaderLoader(const std::string& vertexPath, const std::string& fragmentPath) {
    GLuint vertex = loadShader(vertexPath, GL_VERTEX_SHADER);
    GLuint fragment = loadShader(fragmentPath, GL_FRAGMENT_SHADER);

    program = glCreateProgram();
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);
    glLinkProgram(program);

    checkCompileErrors(program, "PROGRAM");

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

ShaderLoader::~ShaderLoader() {
    glDeleteProgram(program);
}

GLuint ShaderLoader::getProgram() const {
    return program;
}

void ShaderLoader::setUniform(const std::string& name, float v1, float v2, float v3, float v4) {
    GLint location = glGetUniformLocation(program, name.c_str());
    glUniform4f(location, v1, v2, v3, v4);
}

GLuint ShaderLoader::loadShader(const std::string& path, GLenum type) {
    std::string code = readFile(path);
    const char* shaderCode = code.c_str();

    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &shaderCode, NULL);
    glCompileShader(shader);
    checkCompileErrors(shader, (type == GL_VERTEX_SHADER) ? "VERTEX" : "FRAGMENT");

    return shader;
}

std::string ShaderLoader::readFile(const std::string& filepath) {
    std::ifstream file(filepath);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void ShaderLoader::checkCompileErrors(GLuint shader, std::string type) {
    GLint success;
    GLchar infoLog[1024];

    if (type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cerr << "ќшибка компил€ции " << type << " шейдера:\n" << infoLog << std::endl;
        }
    }
    else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cerr << "ќшибка линковки программы:\n" << infoLog << std::endl;
        }
    }
}
