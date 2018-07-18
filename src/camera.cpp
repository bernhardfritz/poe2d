#include "camera.hpp"
#include <xd/xd.hpp>

using namespace xd;
using namespace glm;

void Camera::update() {
    translate(width / 2 - position.x, height / 2 - position.y);
}

vec2 Camera::screenToWorld(vec2 screen) {
    vec2 world = position - vec2(width / 2, height / 2) + screen;
    return world;
}

vec2 Camera::worldToScreen(vec2 world) {
    vec2 screen = world - (position - vec2(width / 2, height / 2));
    return screen;
}
