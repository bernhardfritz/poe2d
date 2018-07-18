#include "character.hpp"
#include <xd/xd.hpp>

using namespace xd;

void Character::draw(float dx,
                     float dy,
                     float dWidth,
                     float dHeight,
                     bool flipHorizontally,
                     bool flipVertically){

    Animation *toUse = lookDown;
    switch(direction){
        case Direction::up:
            toUse = walking ? walkUp : lookUp;
            break;
        case Direction::right:
            toUse = walking ? walkRight : lookRight;
            break;
        case Direction::down:
            toUse = walking ? walkDown : lookDown;
            break;
        case Direction::left:
            toUse = walking ? walkLeft : lookLeft;
            break;
        default:
            break;
    }

    toUse->draw(dx, dy, dWidth, dHeight, flipHorizontally, flipVertically);
}

void Character::draw(float dWidth, float dHeight){
    draw(x, y, dWidth, dHeight, false, false);
}

void Character::draw(){
    draw(x, y, width, height, false, false);
}

void Character::setDirection(Direction dir){
    direction = dir;
}

void Character::moveRelative(float dx, float dy){
    x += dx;
    y += dy;
    camera.position = vec2(getCenterX(), getCenterY());
    light.lightPos = vec2(getCenterX(), getCenterY());
}

void Character::moveAbsolute(float newX, float newY){
    x = newX;
    y = newY;
    camera.position = vec2(getCenterX(), getCenterY());
    light.lightPos = vec2(getCenterX(), getCenterY());
}

void Character::move(){
    switch(direction){
        case Direction::up:
            y -= getMoveSpeed();
            break;
        case Direction::right:
            x += getMoveSpeed();
            break;
        case Direction::down:
            y += getMoveSpeed();
            break;
        case Direction::left:
            x -= getMoveSpeed();
            break;
        default:
            break;
    }
}

float Character::getMoveSpeed(){
    return moveSpeed;
}

float Character::getX(){
    return x;
}

float Character::getCenterX(){
    return x + (width / 2);
}

float Character::getY(){
    return y;
}

float Character::getCenterY(){
    return y + (height / 2);
}

float Character::getHeight(){
    return height;
}

float Character::getWidth(){
    return width;
}

bool Character::isWalking(){
    return walking;
}

void Character::setWalking(bool walking){
    Character::walking = walking;
}