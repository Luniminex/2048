    #pragma once

#include <SDL2/SDL_ttf.h>
#include <string>

class Text{

public:
    SDL_Rect destRect;
private:
    TTF_Font* mFont;
    SDL_Texture* mTexture;

public:
    Text(TTF_Font* font);

    ~Text();

    void setText(const std::string& text, SDL_Renderer* renderer, SDL_Color clr);

    void drawText(SDL_Renderer* renderer);
};