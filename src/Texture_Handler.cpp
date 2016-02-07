#include "Texture_Handler.h"
#include <iostream>

Texture_Handler::Texture_Handler(SDL_Renderer* renderer)
{
    this->renderer = renderer;
}

Texture_Handler::~Texture_Handler()
{
    for(auto& texture : textures)
    {
        SDL_DestroyTexture(texture);
    }
}

Texture_ID Texture_Handler::load(const char* file)
{
    SDL_Texture* texture = IMG_LoadTexture(renderer, file);
    if(!texture)
    {
        throw IMG_GetError();
    }

    textures.push_back(texture);
	return textures.size();
}

SDL_Texture* Texture_Handler::get(Texture_ID id)
{
	return textures.at(id - 1);
}
