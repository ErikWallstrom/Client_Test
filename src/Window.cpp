#include "Window.h"

Window::Window(const char* title, int width, int height)
{
    window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width, height, 0
    );
    if(!window)
    {
        throw SDL_GetError();
    }

    renderer = SDL_CreateRenderer(
        window, -1,
        SDL_RENDERER_ACCELERATED |
        SDL_RENDERER_PRESENTVSYNC |
        SDL_RENDERER_TARGETTEXTURE
    );
    if(!renderer)
    {
        throw SDL_GetError();
    }

    this->width = width;
    this->height = height;
}

Window::~Window()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}


void Window::set_title(const char* title)
{
    this->title = title;
    SDL_SetWindowTitle(window, title);
}

void Window::set_width(int width)
{
    this->width = width;
    SDL_SetWindowSize(window, width, height);
}

void Window::set_height(int height)
{
    this->height = height;
    SDL_SetWindowSize(window, width, height);
}

const char* Window::get_title()
{
    return title;
}

int Window::get_width()
{
    return width;
}

int Window::get_height()
{
    return height;
}

SDL_Renderer* Window::get_renderer()
{
    return renderer;
}
