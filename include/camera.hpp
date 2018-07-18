#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/vec2.hpp>

class Camera {
public:
    glm::vec2 position;

    glm::vec2 screenToWorld(glm::vec2 screen);
    glm::vec2 worldToScreen(glm::vec2 world);
    void update();
};

#endif /* CAMERA_HPP */