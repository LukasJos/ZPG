#include "TranslateTransform.h"

TranslateTransform::TranslateTransform(const glm::vec3& translation)
    : translationVector(translation) {
}

glm::mat4 TranslateTransform::getMatrix() const {
    // Použijeme funkci z GLM, která vytvoøí matici posunu.
    // První parametr je matice, kterou transformujeme (zde jednotková),
    // druhý je vektor posunu.
    return glm::translate(glm::mat4(1.0f), translationVector);
}