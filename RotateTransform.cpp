#include "RotateTransform.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

RotateTransform::RotateTransform(float angle, const glm::vec3& rotationAxis)
    : angleRadians(angle), axis(rotationAxis) {
}

glm::mat4 RotateTransform::getMatrix() const {
    // Pou�ijeme funkci z GLM, kter� vytvo�� matici rotace.
    // 1. parametr: matice, kterou transformujeme (jednotkov�)
    // 2. parametr: �hel rotace (GLM o�ek�v� radi�ny)
    // 3. parametr: osa rotace
    return glm::rotate(glm::mat4(1.0f), angleRadians, axis);
}