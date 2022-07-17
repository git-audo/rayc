#include <iostream>
#include "rayc.h"

Rayc::Rayc() {
    renderer = NULL;
    window   = NULL;

    is_running         = true;
    show_map           = false;
    show_field_of_view = false;

    window_width      = 1236;
    window_height     = 768;
    camera_speed      = 5;
    camera_direction  = 1.00;
    camera_fov        = 1.00;
    camera_x          = 200;
    camera_y          = 200;
    draw_distance     = 800;
    mouse_sensitivity = 0.01;
    frame_count       = 0;

    band_width   = int(window_width/600);
    frame_buffer = new uint32_t[window_width*window_height];
}

bool Rayc::OnInit() {
    if(!map.load(window_width, window_height)) {
        std::cout << "Error opening map file." << std::endl;
        return false;
    }

    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }

    window = SDL_CreateWindow("RayCaster",
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

    SDL_SetRelativeMouseMode(SDL_bool::SDL_TRUE);

    return true;
}

void Rayc::HandleInput() {
        const uint8_t* state = SDL_GetKeyboardState(NULL);

        if (state[SDL_SCANCODE_W]) {
            camera_x += camera_speed * cos(camera_direction);
            camera_y += camera_speed * sin(camera_direction);

            if(map.is_wall_tile(camera_x, camera_y)) {
                camera_x -= camera_speed * cos(camera_direction);
                camera_y -= camera_speed * sin(camera_direction);
            }
        }

        if (state[SDL_SCANCODE_S]) {
            camera_x -= camera_speed * cos(camera_direction);
            camera_y -= camera_speed * sin(camera_direction);
        }

        if (state[SDL_SCANCODE_A]) {
            float delta_x = camera_speed * cos(camera_direction-30);
            float delta_y = camera_speed * sin(camera_direction-30);

            if(!map.is_wall_tile(camera_x-delta_x, camera_y-delta_y)) {
                camera_x -= delta_x;
                camera_y -= delta_y;
            }
        }

        if (state[SDL_SCANCODE_D]) {
            float delta_x = camera_speed * cos(camera_direction+30);
            float delta_y = camera_speed * sin(camera_direction+30);

            if(!map.is_wall_tile(camera_x-delta_x, camera_y-delta_y)) {
                camera_x -= delta_x;
                camera_y -= delta_y;
            }
        }
}

int Rayc::OnExecute() {
    SDL_Event event;

    if(OnInit() == false) {
        return -1;
    }

    frame_last = SDL_GetTicks();

    while(is_running) {
        frame_count++;

        HandleInput();

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
        is_running = false;
    } else if(event->type == SDL_KEYDOWN) {
        switch(event->key.keysym.sym) {
        case SDLK_m:
            show_map = !show_map;
            show_field_of_view = false;
            break;
        case SDLK_v:
            if(show_map)
                show_field_of_view = !show_field_of_view;
            break;
        }
    } else if(event->type == SDL_MOUSEMOTION) {
        camera_direction += event->motion.xrel * mouse_sensitivity;
    }
}

void Rayc::OnLoop() {
    // fill background
    for(size_t i=0; i<window_height/2; i++) {
        for(size_t j=0; j<window_width; j++) {
            frame_buffer[j+i*window_width] = pack_rgb(40, 6, 41);
            frame_buffer[j+(i+window_height/2)*window_width] = pack_rgb(31, 31, 31);
        }
    }

    // cast a ray in the camera looking direction
    for(float v=camera_direction-camera_fov/2; v<camera_direction+camera_fov/2; v+=0.001) {
        for(float i=0; i<draw_distance; i+=1) {
            float x_pos = camera_x + i*cos(v);
            float y_pos = camera_y + i*sin(v);

            if(map.is_wall_tile(x_pos, y_pos)) {
                size_t height = window_height/(i*0.016);
                if (height > window_height) height = window_height;

                float depth_color_intensity = (height/(window_height/1.5));
                draw_rect(frame_buffer, window_width, window_height,
                          (v-camera_direction+camera_fov/2)*(window_width),
                          window_height/2 - height/2,
                          band_width, height,
                          pack_rgb(depth_color_intensity*255, 33, 90));
                break;
            }

            if(show_field_of_view)
                frame_buffer[int(x_pos/3)+int(y_pos/3)*(window_width)] = pack_rgb(130, 196, 255);
        }
    }

    if(show_map) {
        map.draw(frame_buffer, window_width, window_height);
        draw_circle(frame_buffer, window_width, window_height, camera_x/3, camera_y/3, 4);
    }
}

void Rayc::OnRender() {
    SDL_UpdateTexture(texture, NULL, frame_buffer, window_width*sizeof(uint32_t));

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture , NULL, NULL);
    SDL_RenderPresent(renderer);

    SDL_Delay(10);
}

void Rayc::OnExit() {
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();

    delete frame_buffer;
}
