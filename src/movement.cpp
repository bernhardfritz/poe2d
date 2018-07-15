#include <math.h>
#include <algorithm>
#include "movement.hpp"
#include "character.hpp"

bool moveCharacter(Character *character, float mouseX, float mouseY){
    // distances between character and mouse
    double dx = mouseX - character->getCenterX();
    double dy = mouseY - character->getCenterY();
    double dz = sqrt(pow(dx, 2.0) + pow(dy, 2.0));
    
    // calculate how far (percentage of the way) we can go with the character's speed
    double m = std::min(character->getMoveSpeed() / dz, 1.0);

    // alpha is the angle between character and the mouse click
    // it is used for picking one of the four possible movement animations
    // as well as calculating movement
    // (atan: > 0 in quadrants 1 and 3; < 0 in quadrants 2 and 4)
    double alphaRad = atan(dy / dx);
    double alphaDeg = abs(alphaRad * 180 / M_PI);

    // for X and Y, calculate how far we really go
    double moveX = dx * m;
    double moveY = dy * m;

    // check in which direction we're going
    Direction dir = Direction::down;
    if(dx >= 0){
        if(dy <= 0){
            // top right (Q1)
            if(alphaDeg > 45){
                // animation: up
                dir = Direction::up;
            }
            else{
                // animation: right
                dir = Direction::right;
            }
        }
        else{
            // bottom right (Q4)
            if(alphaDeg > 45){
                // animation: down
                dir = Direction::down;
            }
            else{
                // animation: right
                dir = Direction::right;
            }
        }
    }
    else{
        if(dy <= 0){
            // top left (Q2)
            if(alphaDeg > 45){
                // animation: up
                dir = Direction::up;
            }
            else{
                // animation: left
                dir = Direction::left;
            }
        }
        else{
            // bottom left (Q3)
            if(alphaDeg > 45){
                // animation: down
                dir = Direction::down;
            }
            else{
                // animation: left
                dir = Direction::left;
            }
        }
    }

    // move the character and update its direction value
    character->moveRelative(moveX, moveY);
    character->setDirection(dir);

    // if the movement has been completed, return TRUE
    // otherwise, FALSE
    return m >= 1.0;
}