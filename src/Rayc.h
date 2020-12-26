#ifndef RAYC_H
#define RAYC_H

#include <SDL2/SDL.h>

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
    int num_rows, num_columns;
    int x, y;
};

#endif
