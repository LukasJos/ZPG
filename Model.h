#pragma once

#include <GL/glew.h>
#include <memory>
#include "Shader.h"
#include "Transform.h"

class Model {
private:
    GLuint VAO, VBO;
    int vertexCount;

    std::unique_ptr<Transform> transform;
public:
    Model(float* vertices, int count);
    ~Model();
    void draw();
    void draw(Shader* shader);

    // NOVINKA: Metoda pro nastaven� transformace zven��.
    // P�ebere vlastnictv� ukazatele.
    void setTransform(std::unique_ptr<Transform> t);

    // NOVINKA: Metoda pro z�sk�n� (nevlastn�c�ho) ukazatele na transformaci.
    // 'const' zaji��uje, �e tato metoda nezm�n� model.
    Transform* getTransform() const;
};
