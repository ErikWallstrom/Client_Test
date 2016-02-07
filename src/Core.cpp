#include "Core.h"
#include "../include/SDL2/SDL_net.h"
#include "../include/SDL2/SDL_ttf.h"
#include <iostream>
#include <cmath>

Core::Core(const char* title, int width, int height)
{
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
    {
        throw SDL_GetError();
    }

    if(SDLNet_Init())
    {
        throw SDLNet_GetError();
    }

    if(!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
    {
        throw IMG_GetError();
    }

    if(TTF_Init())
    {
        throw TTF_GetError();
    }

    window = new Window(title, width, height);
    event_handler = new Event_Handler;
    scene = new Scene(
        window->get_renderer(),
        window->get_width() / 2.0,
        window->get_height() / 2.0,
        window->get_width(),
        window->get_height()
    );
    texture_handler = new Texture_Handler(
        window->get_renderer()
    );
}

Core::~Core()
{
    delete texture_handler;
    delete scene;
    delete event_handler;
    delete window;

    TTF_Quit();
    IMG_Quit();
    SDLNet_Quit();
    SDL_Quit();
}

void Core::handle_events()
{
    while (event_handler->update())
    {
        if(event_handler->triggered(SDL_QUIT))
        {
            running = false;
            break;
        }
    }
}

void Core::update(int delta)
{
    scene->update(delta);
}

void Core::loop()
{
    int last_time = SDL_GetTicks();
    running = true;
    while(running)
    {
        int delta_time = SDL_GetTicks() - last_time;
        last_time = SDL_GetTicks();

        scene->draw();
        update(delta_time);
        handle_events();
    }
}
