#pragma once

#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>

class RotateTransform : public Transform {
private:
    float angleRadians; // �hel rotace v radi�nech
    glm::vec3 axis;       // Osa, kolem kter� rotujeme

public:
    RotateTransform(float angle, const glm::vec3& rotationAxis);
    glm::mat4 getMatrix() const override;
};
