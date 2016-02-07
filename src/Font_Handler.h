#ifndef FONT_HANDLER_H
#define FONT_HANDLER_H

#include "../include/SDL2/SDL.h"
#include "../include/SDL2/SDL_ttf.h"
#include <vector>
#include <map>

typedef size_t Font_ID;
class Font_Handler
{
private:
    struct Font
    {
        TTF_Font* raw;
        SDL_Texture* atlas;
        int atlas_width, atlas_height;
        std::map<char, SDL_Rect> glyphs;
    };

    SDL_Renderer* renderer;
    std::vector<Font*> fonts;

public:
    Font_Handler(SDL_Renderer* renderer);
    ~Font_Handler();

    Font_ID load(const char* file, int size);
    void render(Font_ID font_id, const char* text, int x, int y);
    void set_color(Font_ID font_id, int r, int g, int b);
};

#endif
