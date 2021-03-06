#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "animation.hpp"
#include "camera.hpp"
#include "lightpass.hpp"

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
              Animation *lookingUp,
              Animation *lookingRight,
              Animation *lookingDown,
              Animation *lookingLeft,
              float height,
              float width,
              float baseMoveSpeed,
              Camera& camera,
              Light& light) :
                    lookUp(lookingUp),
                    lookRight(lookingRight),
                    lookDown(lookingDown),
                    lookLeft(lookingLeft),
                    walkUp(walkingUp),
                    walkRight(walkingRight),
                    walkDown(walkingDown),
                    walkLeft(walkingLeft),
                    direction(Direction::down),
                    moveSpeed(baseMoveSpeed),
                    walking(false),
                    x(0.0f),
                    y(0.0f),
                    height(height),
                    width(width),
                    camera(camera),
                    light(light) {
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

    // getters, setters
    float getMoveSpeed();
    float getX();
    float getCenterX();
    float getY();
    float getCenterY();
    float getHeight();
    float getWidth();
    bool isWalking();
    void setWalking(bool walking);

private:
    Animation *lookUp;
    Animation *lookRight;
    Animation *lookDown;
    Animation *lookLeft;
    Animation *walkUp;
    Animation *walkRight;
    Animation *walkDown;
    Animation *walkLeft;
    Direction direction;
    bool walking;
    float moveSpeed; // character's base movement speed
    float x, y;
    float height, width;
    Camera& camera;
    Light& light;
};

#endif /* CHARACTER_HPP */