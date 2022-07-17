#ifndef CAMERA_H
#define CAMERA_H

#include "map.h"

class Camera {
public:
    Camera();
    ~Camera();

    enum Directions {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };

    void move(Directions dir, Map& map);
    void tilt(SDL_Event* event);

    float direction;
    float fov;
    float x;
    float y;


private:
    int speed;
    float mouse_sensitivity;
};

#endif
