#pragma once

#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>

class RotateTransform : public Transform {
private:
    float angleRadians; // Úhel rotace v radiánech
    glm::vec3 axis;       // Osa, kolem které rotujeme

public:
    RotateTransform(float angle, const glm::vec3& rotationAxis);
    glm::mat4 getMatrix() const override;
};
