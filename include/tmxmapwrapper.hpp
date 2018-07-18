#ifndef TMXMAPWRAPPER_HPP
#define TMXMAPWRAPPER_HPP

#include <xd/image.hpp>
#include <glm/vec4.hpp>
#include <Tmx.h>
#include "spritesheet.hpp"
#include "animation.hpp"
#include "lightpass.hpp"

class TmxMapWrapper {
    public:
    Tmx::Map* tmxmap;
    int cols, rows, tileWidth, tileHeight;
    std::vector<bool> collisionGrid;
    glm::vec4 backgroundColor;
    std::vector<xd::Image*> images;
    std::vector<Spritesheet*> spritesheets;
    std::map<std::pair<int, int>, Animation*> animations;

    TmxMapWrapper(const std::string& filename, std::vector<Light>& lights);
    ~TmxMapWrapper();

    bool isCollisionAtTile(int col, int row);
    bool isCollisionAtCoords(int x, int y);

    void draw();
};

#endif /* TMXMAPWRAPPER_HPP */