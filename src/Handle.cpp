#include "Handle.hpp"

Handle::Handle(){
    mTexture = nullptr;
    mSurface = nullptr;
    mWindow = nullptr;
    mRenderer = nullptr;
    mFont = nullptr;
}

SDL_Window* Handle::getWindow(){
    return mWindow;
}

SDL_Renderer* Handle::getRenderer(){
    return mRenderer;
}

SDL_Texture* Handle::getTexture(){
    return mTexture;
}

TTF_Font* Handle::getFont(){
    return mFont;
}

int Handle::getWidht(){
    return mWindowWidht;
} 

int Handle::getHeight(){
    return mWindowHeight;
}

int Handle::initLibs(){
    if(SDL_Init(SDL_INIT_EVERYTHING)){
        std::cout<< "SDL_Init Error: " << SDL_GetError() << std::endl;
    }

    if(TTF_Init() < 0){
        std::cout << "TTF_Init Error: " << TTF_GetError() << std::endl;
    }

    return 1;
}

int Handle::createWindow(const std::string& title, int widht, int height){
    mWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, widht, height, SDL_WINDOW_SHOWN);
    if(mWindow == nullptr){
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return 0;
    } 
    this->mWindowWidht = widht;
    this->mWindowHeight = height;
    return 1;
}

int Handle::createRenderer(){
    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
    if(mRenderer == nullptr){
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
        return 0;
    }
    return 1;
}

int Handle::loadResources(){
    mFont = TTF_OpenFont("resources/NixieOne.ttf", 100);
    if(mFont == nullptr){
        std::cout << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
        return 0;
    }
    return 1;
}

void Handle::drawLine(int x1, int y1, int x2, int y2){
    if(SDL_RenderDrawLine(mRenderer, x1, y1, x2, y2) != 0){
        std::cout << "SDL_RenderDrawLine Error " << SDL_GetError() << std::endl;
    }
}

void Handle::drawRect(const SDL_Rect& rect){
    if(SDL_RenderFillRect(mRenderer, &rect) != 0){
        std::cout << "SDL_RenderDrawRect Error " << SDL_GetError() << std::endl;
    }
}

int Handle::quit(){
    
    SDL_DestroyWindow(mWindow);
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyTexture(mTexture);

    TTF_CloseFont(mFont);
    
    TTF_Quit();
    SDL_Quit();
    
    mWindow = nullptr;
    mRenderer = nullptr;
    mFont = nullptr;

    return 1;
}