#ifndef RAYC_H
#define RAYC_H

#include <SDL2/SDL.h>
#include "utils.h"

class Rayc
{
public:
    Rayc();

    int OnExecute();
    bool OnInit();
    void OnEvent(SDL_Event *event);
    void OnLoop();
    void OnRender();
    void OnExit();

private:
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;

    int frame_count;
    Uint32 frame_last;
    Uint32 frame_end;

    size_t window_width, window_height;

    size_t map_width;
    size_t map_height;
    char map[101] = "0000000000"\
                    "0        0"\
                    "0        0"\
                    "0     0000"\
                    "0        0"\
                    "0  0     0"\
                    "0  0     0"\
                    "0  000   0"\
                    "0        0"\
                    "0000000000";

    size_t wall_w;
    size_t wall_h;
  
    float camera_x;
    float camera_y;
    float camera_direction;
    float camera_fov;

    uint32_t* framebuffer;
};

#endif
