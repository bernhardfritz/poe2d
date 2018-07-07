#include "sprite.hpp"
#include <xd/xd.hpp>

using namespace xd;

void Sprite::draw(float dx, float dy, float dWidth, float dHeight, bool flipHorizontally, bool flipVertically, bool flipDiagonally) {
    if (flipDiagonally) {
        push();
        imageMode(CENTER);
        translate(dx + dWidth / 2.0f, dy + dHeight / 2.0f);
        rotate(HALF_PI);
        image(img, 0, 0, dWidth, dHeight, sx + (flipVertically ? sWidth : 0), sy + (!flipHorizontally ? sHeight : 0), sWidth * (flipVertically ? -1 : 1), sHeight * (!flipHorizontally ? -1 : 1));
        pop();
    } else {
        image(img, dx, dy, dWidth, dHeight, sx + (flipHorizontally ? sWidth : 0), sy + (flipVertically ? sHeight : 0), sWidth * (flipHorizontally ? -1 : 1), sHeight * (flipVertically ? -1 : 1));
    }
}
