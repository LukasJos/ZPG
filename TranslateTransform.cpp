#include "TranslateTransform.h"

TranslateTransform::TranslateTransform(const glm::vec3& translation)
    : translationVector(translation) {
}

glm::mat4 TranslateTransform::getMatrix() const {
    // Pou�ijeme funkci z GLM, kter� vytvo�� matici posunu.
    // Prvn� parametr je matice, kterou transformujeme (zde jednotkov�),
    // druh� je vektor posunu.
    return glm::translate(glm::mat4(1.0f), translationVector);
}