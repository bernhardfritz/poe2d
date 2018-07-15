#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "animation.hpp"

enum Direction{
    up    = 0,
    right = 1,
    down  = 2,
    left  = 3
};

class Character {
public:
    Character(Animation *walkingUp,
              Animation *walkingRight,
              Animation *walkingDown,
              Animation *walkingLeft,
              float height,
              float width,
              float baseMoveSpeed) :
                    up(walkingUp),
                    right(walkingRight),
                    down(walkingDown),
                    left(walkingLeft),
                    direction(Direction::down),
                    moveSpeed(baseMoveSpeed),
                    x(0.0f),
                    y(0.0f),
                    height(height),
                    width(width) {
              }

    // draw the character, but choose its position, scale and mirroring
    void draw(float dx,
              float dy,
              float dWidth,
              float dHeight,
              bool flipHorizontally = false,
              bool flipVertically = false);

    // draw the character, but scale it
    void draw(float dWidth,
              float dHeight);

    // draw the character as it is
    void draw();

    // change the character's direction
    void setDirection(Direction direction);

    // make the character move (in its direction with its speed)
    void move();

    // move the character to the specified location (without altering its direction animation)
    void moveAbsolute(float newX, float newY);

    // move the character, relative to its current position (without altering its direction animation)
    void moveRelative(float dx, float dy);

    // getters
    float getMoveSpeed();
    float getX();
    float getCenterX();
    float getY();
    float getCenterY();

private:
    Animation *up;
    Animation *right;
    Animation *down;
    Animation *left;
    Direction direction;
    float moveSpeed; // character's base movement speed
    float x, y;
    float height, width;
};

#endif /* CHARACTER_HPP */