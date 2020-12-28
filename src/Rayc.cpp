#include <iostream>
#include "Rayc.h"

Rayc::Rayc()
{
    isRunning = true;
    window = NULL;
    renderer = NULL;

    frame_count = 0;
    
    window_width = 600;
    window_height = 600;

    num_rows = 8;
    num_columns = 10;
    
    x = 100;
    y = 100;

    map_width = 10;
    map_height = 10;
}

bool Rayc::OnInit()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return false;
    }

    window = SDL_CreateWindow("Application",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              window_width, window_height,
                              SDL_WINDOW_SHOWN);

    if(window != NULL)
    {
        renderer = SDL_CreateRenderer(window, -1, 0);
    }
    else
    {
        std::cout << "Failed to create window" << std::endl;
        return false;
    }

    return true;
}

int Rayc::OnExecute()
{
    SDL_Event event;

    if(OnInit() == false)
    {
        return -1;
    }

    frame_last = SDL_GetTicks();
    
    while(isRunning)
    {
        frame_count++;

        while(SDL_PollEvent(&event) != 0)
        {
            OnEvent(&event);
        }

        OnLoop();

        frame_end = SDL_GetTicks();
        if(frame_end - frame_last >= 1000)
        {
            std::string title{"FPS: " + std::to_string(frame_count)};
            SDL_SetWindowTitle(window, title.c_str());
            frame_last = frame_end;            
            frame_count = 0;
        }
        
        OnRender();
    }

    OnExit();
    return 0;
}

void Rayc::OnEvent(SDL_Event *event)
{
    if(event->type == SDL_QUIT)
    {
        isRunning = false;
    }
}

void Rayc::OnLoop()
{
    x = (x + 1) % 300;
    y = (y + 1) % 300;


}

void Rayc::OnRender()
{
    /*
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 200);
    SDL_RenderClear(renderer);

    SDL_Rect fillRect = {100, 100, x, y};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &fillRect);

    float block_size = window_height / num_rows;
    float pos = 0;
    for(int i=0; i<num_rows; i++)
    {
        pos += block_size;
        SDL_RenderDrawLine(renderer,
                           0, static_cast<int>(round(pos)),
                           static_cast<int>(round(window_width)),
                           static_cast<int>(round(pos)));
    }
    */

    SDL_Texture* framebuffer = SDL_CreateTexture(renderer,
                                                 SDL_PIXELFORMAT_ARGB8888,
                                                 SDL_TEXTUREACCESS_STREAMING,
                                                 window_width, window_height);

    uint32_t* pixels = new uint32_t[window_width*window_height];
    for(size_t i=0; i<window_height; i++)
    {
        for(size_t j=0; j<window_width; j++)
        {
            pixels[j+i*window_width] = pack_rgb(100, 255, 0);
        }
    }

    const size_t wall_w = window_width/map_width;
    const size_t wall_h = window_height/map_height;
    for(size_t i=0; i<map_height; i++)
    {
        for(size_t j=0; j<map_width; j++)
        {
            if(map[j+i*map_width] == '0'){
                draw_rect(pixels, window_width, window_height, i*wall_h, j*wall_w, wall_w, wall_h);
            }
        }
    }

    SDL_UpdateTexture(framebuffer, NULL, pixels, window_width*sizeof(uint32_t));
    
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, framebuffer , NULL, NULL);
    SDL_RenderPresent(renderer);

    SDL_Delay(1000);
}

void Rayc::OnExit()
{
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();
}
