#include "Model.h"
#include "CompositeTransform.h"

Model::Model(float* vertices, int count) : vertexCount(count) {
    // Vytvo�en� a nastaven� VBO a VAO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * count * 3, vertices, GL_STATIC_DRAW);

    // Nastaven� layoutu pro vertex atribut 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Odpojen� buffr�
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    transform = std::make_unique<CompositeTransform>();
}

Model::~Model() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Model::draw() {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
    glBindVertexArray(0); // Odpojen� VAO po pou�it�
}

void Model::setTransform(std::unique_ptr<Transform> t) {
    transform = std::move(t);
}

Transform* Model::getTransform() const {
    return transform.get();
}