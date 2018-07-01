#ifndef TMXMAPWRAPPER_HPP
#define TMXMAPWRAPPER_HPP

#include <xd/image.hpp>
#include <glm/vec4.hpp>
#include <Tmx.h>
#include "spritesheet.hpp"
#include "animation.hpp"

class TmxMapWrapper {
    public:
    Tmx::Map* tmxmap;
    glm::vec4 backgroundColor;
    std::vector<xd::Image*> images;
    std::vector<Spritesheet*> spritesheets;
    std::map<std::pair<int, int>, Animation*> animations;

    TmxMapWrapper(const std::string& filename);
    ~TmxMapWrapper();

    void draw();
};

#endif /* TMXMAPWRAPPER_HPP */