#pragma once

#include <GL/glew.h>
#include <string>

class Shader {
private:
    GLuint programID;

    // Pomocn� priv�tn� metody
    GLuint compileShader(const char* source, GLenum type);
    bool checkCompileErrors(GLuint shader, const std::string& type);
    bool checkLinkErrors(GLuint program);

public:
    Shader(const char* vertexSource, const char* fragmentSource);
    ~Shader();
    void use();
};
