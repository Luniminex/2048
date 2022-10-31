#include "Text.hpp"

Text::Text(TTF_Font* font){
    this->mFont = font;
    destRect.x = 0;
    destRect.y = 0;
    destRect.w = 0;
    destRect.h = 0;
}

Text::~Text(){
    SDL_DestroyTexture(mTexture);
}

void Text::setText(const std::string& text, SDL_Renderer* renderer, SDL_Color clr){

    SDL_Surface* surf = TTF_RenderText_Solid(mFont, text.c_str(), clr);
    mTexture = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);
}

void Text::drawText(SDL_Renderer* renderer){
    SDL_RenderCopy(renderer, mTexture, nullptr, &destRect);
    SDL_DestroyTexture(mTexture);
}