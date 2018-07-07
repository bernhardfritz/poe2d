#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include "sprite.hpp"

class Animation {
public:
    std::vector<Sprite> frames;
    int frameDuration; // in ms
    int frameIndex;
    int timestamp; // in ms

    Animation(std::vector<Sprite> frames, int frameDuration, int frameIndex, int timestamp)
        : frames(frames)
        , frameDuration(frameDuration)
        , frameIndex(frameIndex)
        , timestamp(timestamp) {
    }

    Animation(std::initializer_list<Sprite> frames, int frameDuration) : Animation(frames, frameDuration, 0, 0) {
    }

    void draw(float dx, float dy, float dWidth, float dHeight, bool flipHorizontally = false, bool flipVertically = false, bool flipDiagonally = false);
};


#endif /* ANIMATION_HPP */