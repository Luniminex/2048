#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <algorithm>
#include "Handle.hpp"
#include "Text.hpp"

enum class Inputs {
none, left, up, right, down
};

struct Grid {
    int nx;
    int ny;
    int cellSize;
};

struct Box {
    int x;
    int y;
    int value;
    //if it was combined this round
    bool combined;

    Box(){
      x = 0;
      y = 0;
      value = 0; 
      combined = false; 
    }
};

enum class GameState{
    quit, running
};

class Game{

private:
    Handle& handle;
    SDL_Event mEvent;
    Grid mGrid;

    GameState mGameState;
    Inputs input;
    Text texts;

    std::vector<std::vector<Box>> boxes;

    bool lost;
    int score;
public:
    Game(Handle& handle);

    void gameLoop();

private:
    void update();

    void draw();

    void handleInput(SDL_Event& event);

    void handleKeyboardInput(SDL_Event& event);

    void drawGrid();

    void initGrid();

    void moveLeft();

    void moveUp();
    
    void moveRight();

    void moveDown();

    void spawnBox();
};
