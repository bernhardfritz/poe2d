#ifndef CAMERA_HPP
#define CAMERA_HPP

class Camera {
public:
    int x, y;

    Camera(int x, int y) : x(x), y(y) {
    }

    void update();
};

#endif /* CAMERA_HPP */