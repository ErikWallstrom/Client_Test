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

size_t Texture_Handler::load(const char* file)
{
    SDL_Texture* texture = IMG_LoadTexture(renderer, file);
    if(!texture)
    {
        std::cout << SDL_GetError() << std::endl;
        return 0;
    }

    textures.push_back(texture);
	return textures.size();
}

SDL_Texture* Texture_Handler::get(size_t id)
{
	return textures.at(id - 1);
}
