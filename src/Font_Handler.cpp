#include "Font_Handler.h"
#include <cmath>
#define ATLAS_WIDTH 25

Font_Handler::Font_Handler(SDL_Renderer* renderer)
{
    this->renderer = renderer;
}

Font_Handler::~Font_Handler()
{
    for(auto& font : fonts)
    {
        SDL_DestroyTexture(font->atlas);
        TTF_CloseFont(font->raw);

        delete font;
    }
}

Font_ID Font_Handler::load(const char* file, int size)
{
    Font* font = new Font;
    font->raw = TTF_OpenFont(file, size);
    if(!font->raw)
    {
        throw TTF_GetError();
    }

    int max_width = 0;
    int height = TTF_FontHeight(font->raw);
    for(char c = 0; c < 127; c++)
    {
        if(TTF_GlyphIsProvided(font->raw, c))
        {
            char buffer[2] = {c, '\0'};
            int buff_w;

            TTF_SizeText(font->raw, buffer, &buff_w, nullptr);
            if(buff_w > max_width)
            {
                max_width = buff_w;
            }

            font->glyphs[c] = {0, 0, 0, 0};
        }
    }

    font->atlas_width = ATLAS_WIDTH * max_width;
    font->atlas_height = static_cast<int>(
        std::ceil(
            static_cast<double>(font->glyphs.size()) / static_cast<double>(ATLAS_WIDTH)
        ) * height
    );
    font->atlas = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_TARGET,
        font->atlas_width,
        font->atlas_height
    );
    if(!font->atlas)
    {
        throw SDL_GetError();
    }

    SDL_SetRenderTarget(renderer, font->atlas);
    SDL_RenderClear(renderer);

    int current_x = 0;
    int current_y = 0;
    for(auto& p : font->glyphs)
    {
        SDL_Color color = {255, 255, 255, 255};
        SDL_Surface* surface = TTF_RenderGlyph_Blended(
            font->raw,
            p.first,
            color
        );
        if(current_x + surface->w > ATLAS_WIDTH * max_width)
        {
            current_y += height;
            current_x = 0;
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface(
            renderer, surface
        );
        SDL_SetRenderTarget(renderer, font->atlas);

        p.second.x = current_x;
        p.second.y = current_y;
        p.second.w = surface->w;
        p.second.h = height;

        current_x += p.second.w;

        SDL_RenderCopy(renderer, texture, nullptr, &p.second);
        SDL_SetRenderTarget(renderer, nullptr);

        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }

    SDL_SetTextureBlendMode(font->atlas, SDL_BLENDMODE_BLEND);
    fonts.push_back(font);
    return fonts.size();
}

void Font_Handler::render(Font_ID font_id, const char* text, int x, int y)
{
    Font* font = fonts[font_id - 1];
    int total_width = 0;
    int total_height = 0;
    char c;
    for(int i = 0; (c = text[i]); i++)
    {
        SDL_Rect s_rect = font->glyphs[c];
        total_width += s_rect.w;
        total_height = s_rect.h;
    }

    int current_x = x - total_width / 2;
    int current_y = y - total_height / 2;
    for(int i = 0; (c = text[i]); i++)
    {
        SDL_Rect s_rect = font->glyphs[c];
        SDL_Rect d_rect = {current_x, current_y, s_rect.w, s_rect.h};
        current_x += s_rect.w;
        SDL_RenderCopy(renderer, font->atlas, &s_rect, &d_rect);
    }
}

void Font_Handler::set_color(Font_ID font_id, int r, int g, int b)
{
    Font* font = fonts[font_id - 1];
    SDL_SetTextureColorMod(font->atlas, r, g, b);
}
