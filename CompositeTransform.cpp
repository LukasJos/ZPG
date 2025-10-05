#include "CompositeTransform.h"

void CompositeTransform::add(std::unique_ptr<Transform> transform) {
    // std::move p�esune vlastnictv� z parametru 'transform' do na�eho vektoru.
    children.push_back(std::move(transform));
}

glm::mat4 CompositeTransform::getMatrix() const {
    // Za�neme s jednotkovou matic�. Jednotkov� matice v n�soben�
    // funguje jako jedni�ka - nic nem�n�.
    glm::mat4 resultMatrix = glm::mat4(1.0f);

    // Projdeme v�echny pod��zen� transformace v seznamu.
    for (const auto& child : children) {
        // Z�sk�me matici pod��zen� transformace a vyn�sob�me ji
        // s na�� dosavadn� v�slednou matic�.
        // POZOR: Po�ad� n�soben� je d�le�it�!
        // Nov� transformace se n�sob� zleva, aby se aplikovala "pozd�ji".
        resultMatrix = child->getMatrix() * resultMatrix;
    }

    return resultMatrix;
}