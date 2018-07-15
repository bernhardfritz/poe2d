#include <xd/xd.hpp>
#include <Tmx.h>
#include <iostream>
#include "spritesheet.hpp"
#include "camera.hpp"
#include "tmxmapwrapper.hpp"
#include "character.hpp"
#include "movement.hpp"

using namespace xd;

// --------- //
// Variables //
// --------- //

Camera* camera;
TmxMapWrapper* tmxmapwrapper;
Image *img;
Spritesheet *spritesheet;
Animation *upAnim, *rightAnim, *downAnim, *leftAnim;
Character *character;
float cameraOffsetX, cameraOffsetY;
float mouseX = 0.0;
float mouseY = 0.0;
float clickX = 0.0;
float clickY = 0.0;
bool moveComplete = true;

// -------------- //
// Input Handlers //
// -------------- //

void onKeyPressed(int key) {
    // update camera position
    // as well as mouse position
    // (which otherwise wouldn't get updated until next onMouseMoved())
    switch(key) {
        case KEY_LEFT:
            camera->x -= 32;
            mouseX -= 32;
            break;
        case KEY_RIGHT:
            camera->x += 32;
            mouseX += 32;
            break;
        case KEY_UP:
            camera->y -= 32;
            mouseY -= 32;
            break;
        case KEY_DOWN:
            camera->y += 32;
            mouseY += 32;
            break;
    }
}

void onMouseMoved(float x, float y){
    // save where the mouse currently is (taking into account camera offset)
    mouseX = x + (camera->x - cameraOffsetX);
    mouseY = y + (camera->y - cameraOffsetY);
}

void onMouseClicked(int mouseButton){
    switch(mouseButton){
        case MOUSE_BUTTON_RIGHT:
            // update the target x/y and set the character in motion
            clickX = mouseX;
            clickY = mouseY;
            moveComplete = false;
            break;
        case MOUSE_BUTTON_MIDDLE:
        case MOUSE_BUTTON_LEFT:
        default:
            break;
    }
}

// ---------------- //
// Helper functions //
// ---------------- //

void setupCharacter(){
    img = loadImage("./resources/character.png");
    spritesheet = new Spritesheet(img, 4, 4);
    upAnim = new Animation({
        spritesheet->sprites[0],
        spritesheet->sprites[1],
        spritesheet->sprites[2],
        spritesheet->sprites[3],
    }, 17);
    rightAnim = new Animation({
        spritesheet->sprites[4],
        spritesheet->sprites[5],
        spritesheet->sprites[6],
        spritesheet->sprites[7],
    }, 17);
    downAnim = new Animation({
        spritesheet->sprites[8],
        spritesheet->sprites[9],
        spritesheet->sprites[10],
        spritesheet->sprites[11],
    }, 17);
    leftAnim = new Animation({
        spritesheet->sprites[12],
        spritesheet->sprites[13],
        spritesheet->sprites[14],
        spritesheet->sprites[15],
    }, 17);

    character = new Character(upAnim, rightAnim, downAnim, leftAnim, 30.0, 30.0, 5.0);
}

void moveCharacter(){
    // move the character if it hasn't completed its movement yet
    if(!moveComplete){
        moveComplete = moveCharacter(character, clickX, clickY);
    }
}

// ------------------- //
// Framework Callbacks //
// ------------------- //

void setup() {
    size(640, 480);

    camera = new Camera(width / 2, height / 2);
    tmxmapwrapper = new TmxMapWrapper("./resources/dungeons/dungeon-01/dungeon-01.tmx");
    setupCharacter();
    character->moveAbsolute(width / 2, height / 2);

    cameraOffsetX = camera->x;
    cameraOffsetY = camera->y;

    keyPressed(onKeyPressed);
    mouseMoved(onMouseMoved);
    mousePressed(onMouseClicked);
}

void draw() {
    camera->update();
    tmxmapwrapper->draw();

    // move the character and draw it
    moveCharacter();
    character->draw();
}

void destroy() {
    delete camera;
    delete tmxmapwrapper;
    delete character;
}
