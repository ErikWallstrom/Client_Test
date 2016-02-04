#ifndef FONT_H
#define FONT_H

#include "../include/SDL2/SDL.h"
#include "../include/SDL2/SDL_ttf.h"
#include <map>
class Font
{
private:
    struct Font_Size
    {
        TTF_Font* font;
        std::map<char, SDL_Texture*> glyphs;
    };

    SDL_Renderer* renderer;
    std::map<int, Font_Size> font_sizes;
    int size;
    const char* file;

    bool size_exists();
    void load_size();

public:
    Font(SDL_Renderer* renderer, const char* file);
    ~Font();

    void set_size(int size);
    int get_size();

    void render_text(const char* text, int x, int y);
    SDL_Texture* get_text(const char* text);
};

#endif
