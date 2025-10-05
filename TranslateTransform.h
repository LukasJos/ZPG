#pragma once

#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>

// D�d�me z ve�ejn� t��dy Transform.
class TranslateTransform : public Transform {
private:
    glm::vec3 translationVector; // Vektor, o kter� se posouv�me

public:
    // Konstruktor, kde specifikujeme posun
    TranslateTransform(const glm::vec3& translation);

    // P�episujeme (override) �ist� virtu�ln� metodu z Transform.
    // 'override' je kl��ov� slovo, kter� kompil�toru �ekne,
    // �e chceme p�epsat metodu z rodi�ovsk� t��dy. Pom�h� odhalit chyby.
    glm::mat4 getMatrix() const override;
};
