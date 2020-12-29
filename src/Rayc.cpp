#include <iostream>
#include "Rayc.h"

Rayc::Rayc()
{
    isRunning = true;
    window = NULL;
    renderer = NULL;

    frame_count = 0;
    
    window_width = 1024;
    window_height = 512;
    
    map_width = 10;
    map_height = 10;
    wall_w = window_width/(2*map_width);
    wall_h = window_height/map_height;

    camera_x = 100;
    camera_y = 100;
    camera_direction = 7.00;
    camera_fov = 1.00;

    framebuffer = new uint32_t[window_width*window_height];    
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
    
    camera_direction -= 0.01;
    if(camera_direction < 5.0)
        camera_direction = 8.00;
}

void Rayc::OnRender()
{
    SDL_Texture* texture = SDL_CreateTexture(renderer,
                                             SDL_PIXELFORMAT_ARGB8888,
                                             SDL_TEXTUREACCESS_STREAMING,
                                             window_width, window_height);

    for(size_t i=0; i<window_height; i++)
    {
        for(size_t j=0; j<window_width; j++)
        {
            framebuffer[j+i*window_width] = pack_rgb(41, 6, 40);
        }
    }

    for(size_t i=0; i<map_height; i++)
    {
        for(size_t j=0; j<map_width; j++)
        {
            if(map[j+i*map_width] == '0'){
                draw_rect(framebuffer, window_width, window_height, j*wall_w, i*wall_h, wall_w, wall_h);
            }
        }
    }

    draw_circle(framebuffer, window_width, window_height, camera_x, camera_y, 10);

    // cast a ray in the camera looking direction
    for(float v=camera_direction; v<camera_direction+camera_fov; v+=0.002)
    {
        for(float i=0; i<700; i+=5)
        {
            float x_pos = camera_x + i*cos(v);
            float y_pos = camera_y + i*sin(v);
            if(map[int(x_pos/wall_w)+int(y_pos/wall_h)*map_width] == '0')
            {
                size_t height = window_height/(i*0.02);
                draw_rect(framebuffer, window_width, window_height,
                          window_width/2+(v-camera_direction)*(500), window_height/2-height/2, 1, height);
                break;
            }
            framebuffer[int(x_pos)+int(y_pos)*window_width] = pack_rgb(255, 255, 255);
        }
    }
    
    SDL_UpdateTexture(texture, NULL, framebuffer, window_width*sizeof(uint32_t));
    
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture , NULL, NULL);
    SDL_RenderPresent(renderer);

    SDL_Delay(50);
}

void Rayc::OnExit()
{
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();
}
