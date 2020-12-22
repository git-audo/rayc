#include <iostream>
#include <SDL2/SDL.h>

int main(){
    SDL_Window *window;
//    SDL_Renderer *renderer;
    SDL_Surface *window_surface;

    
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        return false;
    }
    
    window = SDL_CreateWindow("Application", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 400, 180, SDL_WINDOW_SHOWN);

    if(window != NULL)
    {
//        renderer = SDL_CreateRenderer(window, -1, 0);
    }
    else
    {
        std::cout << "Failed to create window" << std::endl;
        return false;
    }

    window_surface = SDL_GetWindowSurface(window);


    if(!window_surface)
    {
        std::cout << "Failed to get window surface" << std::endl;
        return false;
    }

    SDL_UpdateWindowSurface(window);
    
    SDL_Delay(5000);
    
    return true;
}
