#include "character.hpp"
#include <xd/xd.hpp>

using namespace xd;

void Character::draw(float dx,
                     float dy,
                     float dWidth,
                     float dHeight,
                     bool flipHorizontally,
                     bool flipVertically){

    Animation *toUse = down;
    switch(direction){
        case Direction::up:
            toUse = up;
            break;
        case Direction::right:
            toUse = right;
            break;
        case Direction::down:
            toUse = down;
            break;
        case Direction::left:
            toUse = left;
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
}

void Character::moveAbsolute(float newX, float newY){
    x = newX;
    y = newY;
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
    return x + (height / 2);
}

float Character::getY(){
    return y;
}

float Character::getCenterY(){
    return y + (width / 2);
}