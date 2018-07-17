#include <xd/xd.hpp>
#include <Tmx.h>
#include <iostream>
#include <functional>
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
Animation *walkUp, *walkRight, *walkDown, *walkLeft;
Animation *lookUp, *lookRight, *lookDown, *lookLeft;
Character *character;
float cameraOffsetX, cameraOffsetY;
float mouseX = 0.0;
float mouseY = 0.0;
float clickX = 0.0;
float clickY = 0.0;
bool moveComplete = true;
bool showCollisionGrid = false;

// -------------- //
// Input Handlers //
// -------------- //

void onKeyPressed(int key) {
    // update camera position
    // as well as mouse position
    // (which otherwise wouldn't get updated until next onMouseMoved())
    const int& tileWidth = tmxmapwrapper->tileWidth;
    const int& tileHeight = tmxmapwrapper->tileHeight;
    switch(key) {
        case KEY_LEFT:
            camera->x -= tileWidth;
            mouseX -= tileWidth;
            break;
        case KEY_RIGHT:
            camera->x += tileWidth;
            mouseX += tileWidth;
            break;
        case KEY_UP:
            camera->y -= tileHeight;
            mouseY -= tileHeight;
            break;
        case KEY_DOWN:
            camera->y += tileHeight;
            mouseY += tileHeight;
            break;
        case 'C':
            showCollisionGrid = !showCollisionGrid;
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
    img = loadImage("./resources/characters/character.png");
    spritesheet = new Spritesheet(img, 10, 8);

    walkDown = new Animation({
        spritesheet->sprites[0],
        spritesheet->sprites[1],
        spritesheet->sprites[2],
        spritesheet->sprites[3],
        spritesheet->sprites[4],
        spritesheet->sprites[5],
        spritesheet->sprites[6],
        spritesheet->sprites[7],
        spritesheet->sprites[8],
        spritesheet->sprites[9]
    }, 50);
    walkUp= new Animation({
        spritesheet->sprites[10],
        spritesheet->sprites[11],
        spritesheet->sprites[12],
        spritesheet->sprites[13],
        spritesheet->sprites[14],
        spritesheet->sprites[15],
        spritesheet->sprites[16],
        spritesheet->sprites[17],
        spritesheet->sprites[18],
        spritesheet->sprites[19]
    }, 50);
    walkRight = new Animation({
        spritesheet->sprites[20],
        spritesheet->sprites[21],
        spritesheet->sprites[22],
        spritesheet->sprites[23],
        spritesheet->sprites[24],
        spritesheet->sprites[25],
        spritesheet->sprites[26],
        spritesheet->sprites[27],
        spritesheet->sprites[28],
        spritesheet->sprites[29]
    }, 50);
    walkLeft = new Animation({
        spritesheet->sprites[30],
        spritesheet->sprites[31],
        spritesheet->sprites[32],
        spritesheet->sprites[33],
        spritesheet->sprites[34],
        spritesheet->sprites[35],
        spritesheet->sprites[36],
        spritesheet->sprites[37],
        spritesheet->sprites[38],
        spritesheet->sprites[39]
    }, 50);
    lookDown = new Animation({
        spritesheet->sprites[40],
        spritesheet->sprites[41]
    }, 5000);
    lookUp = new Animation({
        spritesheet->sprites[50],
        spritesheet->sprites[51]
    }, 5000);
    lookRight = new Animation({
        spritesheet->sprites[60]
    }, 5000);
    lookLeft = new Animation({
        spritesheet->sprites[70]
    }, 5000);

    character = new Character(walkUp, walkRight, walkDown, walkLeft,
                              lookUp, lookRight, lookDown, lookLeft,
                              84.0, 60.0, 5.0);
}

void moveCharacter(){
    // move the character if it hasn't completed its movement yet
    if(!moveComplete){
        moveComplete = moveCharacter(character, clickX, clickY);
    }
}

void drawColissionGrid() {
    const int& tileWidth = tmxmapwrapper->tileWidth;
    const int& tileHeight = tmxmapwrapper->tileHeight;
    for (int row = 0; row < tmxmapwrapper->rows; row++) {
        for (int col = 0; col < tmxmapwrapper->cols; col++) {
            if (tmxmapwrapper->isCollisionAtTile(col, row)) {
                fill(vec4(1.0f, 0.0f, 0.0f, 0.5f));
                noStroke();
                rect(col * tileWidth, row * tileHeight, tileWidth, tileHeight);
            }
        }
    }
    if (tmxmapwrapper->isCollisionAtCoords(mouseX, mouseY)) {
        stroke(vec4(1.0f, 0.0f, 0.0f, 1.0f));
        strokeWeight(5.0f);
        line(mouseX - 10, mouseY - 10, mouseX + 10, mouseY + 10);
        line(mouseX + 10, mouseY - 10, mouseX - 10, mouseY + 10);
    }
}

void drawOutlined(std::function<void()> fnDraw) {
    tint(vec4(1.0f, 0.0, 0.0, 1.0), true);
    fnDraw();
    noTint();
    fnDraw();
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
    if (showCollisionGrid) {
        drawColissionGrid();
    }

    // move the character and draw it
    moveCharacter();
    if (character->getX() < mouseX && mouseX < character->getX() + character->getWidth()
        && character->getY() < mouseY && mouseY < character->getY() + character->getHeight()) {
        drawOutlined([]() { character->draw(); });
    } else {
        character->draw();
    }
}

void destroy() {
    delete camera;
    delete tmxmapwrapper;
    delete walkUp;
    delete walkRight;
    delete walkDown;
    delete walkLeft;
    delete img;
    delete spritesheet;
    delete character;
}
