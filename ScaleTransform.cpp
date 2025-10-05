#include "ScaleTransform.h"

ScaleTransform::ScaleTransform(const glm::vec3& scale)
    : scaleVector(scale) {
}

glm::mat4 ScaleTransform::getMatrix() const {
    // Použijeme funkci z GLM, která vytvoøí matici zmìny mìøítka.
    // 1. parametr: matice, kterou transformujeme (jednotková)
    // 2. parametr: vektor, který urèuje zmìnu mìøítka pro každou osu
    return glm::scale(glm::mat4(1.0f), scaleVector);
}