#include "camera.hpp"
#include <xd/xd.hpp>

using namespace xd;

void Camera::update() {
    translate(width / 2 - x, height / 2 - y);
}