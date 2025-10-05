#include "RotateTransform.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

RotateTransform::RotateTransform(float angle, const glm::vec3& rotationAxis)
    : angleRadians(angle), axis(rotationAxis) {
}

glm::mat4 RotateTransform::getMatrix() const {
    // Použijeme funkci z GLM, která vytvoøí matici rotace.
    // 1. parametr: matice, kterou transformujeme (jednotková)
    // 2. parametr: úhel rotace (GLM oèekává radiány)
    // 3. parametr: osa rotace
    return glm::rotate(glm::mat4(1.0f), angleRadians, axis);
}