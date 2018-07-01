#include <xd/xd.hpp>
#include <Tmx.h>
#include <iostream>
#include "spritesheet.hpp"
#include "camera.hpp"
#include "tmxmapwrapper.hpp"

using namespace xd;

Camera* camera;
TmxMapWrapper* tmxmapwrapper;

void onKeyPressed(int key) {
    switch(key) {
        case KEY_LEFT:
            camera->x -= 32;
            break;
        case KEY_RIGHT:
            camera->x += 32;
            break;
        case KEY_UP:
            camera->y -= 32;
            break;
        case KEY_DOWN:
            camera->y += 32;
            break;
    }
}

void setup() {
    size(640, 480);

    camera = new Camera(width / 2, height / 2);
    tmxmapwrapper = new TmxMapWrapper("./resources/dungeons/dungeon-01/dungeon-01.tmx");

    keyPressed(onKeyPressed);
}

void draw() {
    camera->update();
    tmxmapwrapper->draw();
}

void destroy() {
    delete camera;
    delete tmxmapwrapper;
}
