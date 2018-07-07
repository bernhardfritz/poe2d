#include "animation.hpp"
#include <xd/xd.hpp>

using namespace xd;

void Animation::draw(float dx, float dy, float dWidth, float dHeight, bool flipHorizontally, bool flipVertically, bool flipDiagonally) {
    if (frames.empty()) {
        return;
    }
    frames[frameIndex].draw(dx, dy, dWidth, dHeight, flipHorizontally, flipVertically, flipDiagonally);
    if (millis() - timestamp > frameDuration) {
        frameIndex = (frameIndex + 1) % frames.size();
        timestamp = millis();
    }
}