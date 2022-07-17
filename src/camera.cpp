#include <SDL2/SDL.h>
#include "camera.h"

Camera::Camera() {
    speed      = 5;
    direction  = 1.00;
    fov        = 1.00;
    x          = 200;
    y          = 200;

    mouse_sensitivity = 0.01;
};

Camera::~Camera() {};

void Camera::move(Directions dir, Map& map) {
    float delta_x = 0;
    float delta_y = 0;

    switch (dir) {
    case FORWARD:
        delta_x = speed * cos(direction);
        delta_y = speed * sin(direction);
        break;
    case BACKWARD:
        delta_x = - speed * cos(direction);
        delta_y = - speed * sin(direction);
        break;
    case LEFT:
        // Todo: fix magic numbers
        delta_x = - speed * cos(direction - 30);
        delta_y = - speed * sin(direction - 30);
        break;
    case RIGHT:
        delta_x = speed * cos(direction - 30);
        delta_y = speed * sin(direction - 30);
        break;
    default: break;
    }

    if(!map.is_wall_tile(x + delta_x, y + delta_y)) {
        x += delta_x;
        y += delta_y;
    }
};

void Camera::tilt(SDL_Event* event) {
    direction += event->motion.xrel * mouse_sensitivity;
};
