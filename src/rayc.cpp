#include <iostream>
#include "rayc.h"

Rayc::Rayc() {
    isRunning = true;
    window = NULL;
    renderer = NULL;

    frame_count = 0;
    
    window_width = 1536;
    window_height = 768;
    
    map_width = 10;
    map_height = 10;
    wall_w = window_width/(2*map_width);
    wall_h = window_height/map_height;

    camera_x = 100;
    camera_y = 100;
    camera_direction = 0.00;
    camera_fov = 1.00;

    framebuffer = new uint32_t[window_width*window_height];    
}

bool Rayc::OnInit() {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }

    window = SDL_CreateWindow("Application",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              window_width, window_height,
                              SDL_WINDOW_SHOWN);

    if(window != NULL) {
        renderer = SDL_CreateRenderer(window, -1, 0);
    } else {
        std::cout << "Failed to create window" << std::endl;
        return false;
    }

    texture = SDL_CreateTexture(renderer,
                                SDL_PIXELFORMAT_ARGB8888,
                                SDL_TEXTUREACCESS_STREAMING,
                                window_width, window_height);

    return true;
}

int Rayc::OnExecute() {
    SDL_Event event;

    if(OnInit() == false) {
        return -1;
    }

    frame_last = SDL_GetTicks();
    
    while(isRunning) {
        frame_count++;

        while(SDL_PollEvent(&event) != 0) {
            OnEvent(&event);
        }

        OnLoop();

        frame_end = SDL_GetTicks();
        if(frame_end - frame_last >= 1000) {
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

void Rayc::OnEvent(SDL_Event *event) {
    if(event->type == SDL_QUIT) {
        isRunning = false;
    } else if(event->type == SDL_KEYDOWN) {
        switch(event->key.keysym.sym) {
        case SDLK_w:
            camera_x += 3*cos(camera_direction);
            camera_y += 3*sin(camera_direction);
            break;
        case SDLK_a:
            camera_x += 2;
            break;
        case SDLK_s:
            camera_x -= 3*cos(camera_direction);
            camera_y -= 3*sin(camera_direction);
            break;
        case SDLK_d:
            camera_x -= 2;
            break;
        }
    } else if(event->type == SDL_MOUSEMOTION) {
        camera_direction += event->motion.xrel * 0.01;
    }
}

void Rayc::OnLoop() {}

void Rayc::OnRender() {
    for(size_t i=0; i<window_height; i++) {
        for(size_t j=0; j<window_width; j++) {
            framebuffer[j+i*window_width] = pack_rgb(41, 6, 40);
        }
    }

    for(size_t i=0; i<map_height; i++) {
        for(size_t j=0; j<map_width; j++) {
            if(map[j+i*map_width] == '0') {
                draw_rect(framebuffer, window_width, window_height,
                          j*wall_w, i*wall_h, wall_w, wall_h);
            } else if(map[j+i*map_width] == '1') {
                draw_rect(framebuffer, window_width, window_height,
                          j*wall_w, i*wall_h, wall_w, wall_h, pack_rgb(255, 255, 255));
            }
        }
    }

    draw_circle(framebuffer, window_width, window_height, camera_x, camera_y, 10);

    // cast a ray in the camera looking direction
    for(float v=camera_direction-camera_fov/2; v<camera_direction+camera_fov/2; v+=0.001) {
        for(float i=0; i<800; i+=1) {
            float x_pos = camera_x + i*cos(v);
            float y_pos = camera_y + i*sin(v);
            if(map[int(x_pos/wall_w)+int(y_pos/wall_h)*map_width] != ' ') {
                size_t height = window_height/(i*0.02);
                draw_rect(framebuffer, window_width, window_height,
                          window_width/2+(v-camera_direction+camera_fov/2)*(750),
                          window_height/2-height/2, 1.5, height,
                          pack_rgb((height/(window_height/1.5))*255, 60, 0));
                break;
            }
            //framebuffer[int(x_pos)+int(y_pos)*(window_width)] = pack_rgb(255, 255, 255);
        }
    }

    // draw reticle
    draw_rect(framebuffer, window_width, window_height,
              window_width*3/4, window_height/2-5, 1, 10);
    
    SDL_UpdateTexture(texture, NULL, framebuffer, window_width*sizeof(uint32_t));
    
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture , NULL, NULL);
    SDL_RenderPresent(renderer);

    SDL_Delay(10);
}

void Rayc::OnExit() {
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();
}
