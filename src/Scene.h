#ifndef SCENE_H
#define SCENE_H

#include "Game_Object.h"
#include <string>
#include <map>
class Scene : Game_Object
{
private:
    std::map<std::string, Game_Object*> objects;
    SDL_Renderer* renderer;

public:
    Scene(SDL_Renderer* renderer, double x, double y, int width, int height);
    ~Scene();

    void draw();
    void add(Game_Object* object, std::string name);
    std::map<std::string, Game_Object*>* get_objects();
};

#endif
