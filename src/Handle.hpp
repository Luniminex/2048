#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class Handle {

    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
   
    SDL_Surface* mSurface;
    SDL_Texture* mTexture;

    TTF_Font* mFont;
   
    int mWindowHeight;
    int mWindowWidht;

public:
    Handle();

    //returns window
    SDL_Window* getWindow();

    //returns renderer
    SDL_Renderer* getRenderer();

    //returns texture
    SDL_Texture* getTexture();

    //returns font
    TTF_Font* getFont();

    int getWidht();

    int getHeight();

    //initializes SDL libraries
    int initLibs();

    //creates a window
    int createWindow(const std::string& title, int widht, int height);

    //creates a renderer
    int createRenderer();

    //loads resources (fonts, textures)
    int loadResources();

    //renders a line
    void drawLine(int x1, int y1, int x2, int y2);

    //renders a rectangle
    void drawRect(const SDL_Rect& rect);

    //frees resources and quits SDL libraries
    int quit();

};
