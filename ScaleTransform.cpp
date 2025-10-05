#include "ScaleTransform.h"

ScaleTransform::ScaleTransform(const glm::vec3& scale)
    : scaleVector(scale) {
}

glm::mat4 ScaleTransform::getMatrix() const {
    // Pou�ijeme funkci z GLM, kter� vytvo�� matici zm�ny m���tka.
    // 1. parametr: matice, kterou transformujeme (jednotkov�)
    // 2. parametr: vektor, kter� ur�uje zm�nu m���tka pro ka�dou osu
    return glm::scale(glm::mat4(1.0f), scaleVector);
}