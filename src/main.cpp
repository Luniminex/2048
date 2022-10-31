#include "Handle.hpp"
#include "Game.hpp"

#define WINDOW_WIDHT 600
#define WINDOW_HEIGHT 600

int main(){

    Handle handle;

    if(handle.initLibs() != 1){
        std::cout << "Failed to initialize SDL libraries" << std::endl;
        return 1;
    }
    if(handle.createWindow("2048", WINDOW_WIDHT, WINDOW_HEIGHT)!= 1){
        std::cout << "Could not create a window" << std::endl;
        return 1;
    }
    if(handle.createRenderer() != 1){
        std::cout << "Could not create a renderer" << std::endl;
        return 1;
    }
    if(handle.loadResources() != 1){
        std::cout << "Could not load all resources" << std::endl;
        return 1;
    }

    Game game(handle);
    game.gameLoop();
    
    handle.quit();

    return 0;
}

