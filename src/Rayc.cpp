#include <iostream>
#include "Rayc.h"

Rayc::Rayc()
{
    isRunning = true;
    window = NULL;
    renderer = NULL;
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
                              400, 180,
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

    while(isRunning)
    {
        while(SDL_PollEvent(&event) != 0)
        {
            OnEvent(&event);
        }

        OnLoop();
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

}

void Rayc::OnRender()
{
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 200);
    SDL_RenderClear(renderer);

    SDL_Rect fillRect = {100, 100, 300, 200};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &fillRect);

    SDL_RenderPresent(renderer);
}

void Rayc::OnExit()
{
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();
}
