#pragma once

#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>

// Dìdíme z veøejné tøídy Transform.
class TranslateTransform : public Transform {
private:
    glm::vec3 translationVector; // Vektor, o který se posouváme

public:
    // Konstruktor, kde specifikujeme posun
    TranslateTransform(const glm::vec3& translation);

    // Pøepisujeme (override) èistì virtuální metodu z Transform.
    // 'override' je klíèové slovo, které kompilátoru øekne,
    // že chceme pøepsat metodu z rodièovské tøídy. Pomáhá odhalit chyby.
    glm::mat4 getMatrix() const override;
};
