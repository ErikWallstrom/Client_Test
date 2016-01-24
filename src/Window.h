#ifndef WINDOW_H
#define WINDOW_H

#include "../include/SDL2/SDL.h"
class Window
{
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    const char* title;
    int width, height;

public:
    Window(const char* title, int width, int height);
    ~Window();

    void set_title(const char* title);
    void set_width(int width);
    void set_height(int height);

    const char* get_title();
    int get_width();
    int get_height();

    SDL_Renderer* get_renderer();
};

#endif
