#pragma once

#include <GL/glew.h>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
private:
    GLuint programID;

    // Pomocné privátní metody
    GLuint compileShader(const char* source, GLenum type);
    bool checkCompileErrors(GLuint shader, const std::string& type);
    bool checkLinkErrors(GLuint program);

public:
    Shader(const char* vertexSource, const char* fragmentSource);
    ~Shader();
    void use();

    void setUniform(const std::string& name, bool value);
    void setUniform(const std::string& name, int value);
    void setUniform(const std::string& name, float value);
    void setUniform(const std::string& name, const glm::vec2& value);
    void setUniform(const std::string& name, const glm::vec3& value);
    void setUniform(const std::string& name, const glm::vec4& value);
    void setUniform(const std::string& name, const glm::mat4& value);
};
