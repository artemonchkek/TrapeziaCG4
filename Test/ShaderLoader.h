#ifndef SHADERLOADER_H
#define SHADERLOADER_H

#include <GL/glew.h>
#include <string>

class ShaderLoader {
public:
    ShaderLoader(const std::string& vertexPath, const std::string& fragmentPath);
    ~ShaderLoader();
    GLuint getProgram() const;
    void setUniform(const std::string& name, float v1, float v2, float v3, float v4);

private:
    GLuint program;
    GLuint loadShader(const std::string& path, GLenum type);
    std::string readFile(const std::string& filepath);
    void checkCompileErrors(GLuint shader, std::string type);
};

#endif
