#include "Font.h"
#include <iostream>

Font::Font(SDL_Renderer* renderer, const char* file)
{
    this->renderer = renderer;
    this->file = file;

    set_size(16);
}

Font::~Font()
{
    for(auto& p : font_sizes)
    {
        for(auto& p1 : p.second.glyphs)
        {
            SDL_DestroyTexture(p1.second);
        }
        TTF_CloseFont(p.second.font);
    }
}

bool Font::size_exists()
{
    if(font_sizes.find(size) != font_sizes.end())
        return true;

    return false;
}

void Font::load_size()
{
    TTF_Font* font = TTF_OpenFont(file, size);
    if(!font)
    {
        throw TTF_GetError();
    }

    Font_Size fsize;
    fsize.font = font;
    for(char c = ' '; c <= '~'; c++) //Basically all english characters
    {
        if(TTF_GlyphIsProvided(font, c))
        {

        }
    }
}
