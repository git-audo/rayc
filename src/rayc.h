#ifndef RAYC_H
#define RAYC_H

#include <SDL2/SDL.h>
#include "utils.h"
#include "map.h"

class Rayc {
public:
    Rayc();

    int OnExecute();
    bool OnInit();
    void OnEvent(SDL_Event *event);
    void OnLoop();
    void OnRender();
    void OnExit();

private:
    bool is_running;
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;
  
    int frame_count;
    Uint32 frame_last;
    Uint32 frame_end;

    size_t window_width;
    size_t window_height;

    float mouse_sensitivity;
    float camera_x;
    float camera_y;
    float camera_direction;
    float camera_fov;
    int draw_distance;
    int band_width;

    bool show_field_of_view; 
    bool show_map;   

    Map map;
    uint32_t *frame_buffer;
};

#endif
