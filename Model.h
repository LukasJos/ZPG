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

    // NOVINKA: Metoda pro nastavení transformace zvenèí.
    // Pøebere vlastnictví ukazatele.
    void setTransform(std::unique_ptr<Transform> t);

    // NOVINKA: Metoda pro získání (nevlastnícího) ukazatele na transformaci.
    // 'const' zajišuje, e tato metoda nezmìní model.
    Transform* getTransform() const;
};
