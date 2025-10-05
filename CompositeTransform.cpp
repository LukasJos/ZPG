#include "CompositeTransform.h"

void CompositeTransform::add(std::unique_ptr<Transform> transform) {
    // std::move pøesune vlastnictví z parametru 'transform' do našeho vektoru.
    children.push_back(std::move(transform));
}

glm::mat4 CompositeTransform::getMatrix() const {
    // Zaèneme s jednotkovou maticí. Jednotková matice v násobení
    // funguje jako jednièka - nic nemìní.
    glm::mat4 resultMatrix = glm::mat4(1.0f);

    // Projdeme všechny podøízené transformace v seznamu.
    for (const auto& child : children) {
        // Získáme matici podøízené transformace a vynásobíme ji
        // s naší dosavadní výslednou maticí.
        // POZOR: Poøadí násobení je dùležité!
        // Nová transformace se násobí zleva, aby se aplikovala "pozdìji".
        resultMatrix = child->getMatrix() * resultMatrix;
    }

    return resultMatrix;
}