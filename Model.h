#pragma once

#include <GL/glew.h>

class Model {
private:
    GLuint VAO, VBO;
    int vertexCount;

public:
    Model(float* vertices, int count);
    ~Model();
    void draw();
};
