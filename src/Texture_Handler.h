#ifndef TEXTURE_HANDLER_H
#define TEXTURE_HANDLER_H

#include "../include/SDL2/SDL_image.h"
#include <vector>
#include <string>

typedef size_t Texture_ID;

class Texture_Handler
{
private:
    SDL_Renderer* renderer;
    std::vector<SDL_Texture*> textures;

public:
    Texture_Handler(SDL_Renderer* renderer);
    ~Texture_Handler();

    Texture_ID load(const char* file);
    SDL_Texture* get(Texture_ID id);
};

#endif
