#include "Scene.h"
#include <iostream>
#include <cmath>

Scene::Scene(SDL_Renderer* renderer, double x, double y, int width, int height)
: Game_Object(x, y, width, height)
{
    texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        width, height
    );
    if(!texture)
    {
        throw SDL_GetError();
    }

    this->renderer = renderer;
}


Scene::~Scene()
{
    SDL_DestroyTexture(texture);
}

void Scene::draw()
{
    SDL_SetRenderTarget(renderer, texture);
    SDL_RenderClear(renderer);
    for(auto pair : objects)
    {
        pair.second->render(renderer);
    }
    SDL_SetRenderTarget(renderer, NULL);

    SDL_RenderClear(renderer);
    render(renderer);
    SDL_RenderPresent(renderer);
}

void Scene::add(Game_Object* object, std::string name)
{
    if(object)
    {
        objects[name] = object;
    }
}

std::map<std::string, Game_Object*>* Scene::get_objects()
{
    return &objects;
}