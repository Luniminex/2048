#include "Game.hpp"

Game::Game(Handle& handle) : handle(handle), texts(handle.getFont()){
    mGameState = GameState::running;
    mGrid.cellSize = handle.getWidht() / 6;
    mGrid.nx = 4;
    mGrid.ny = 4;
    input = Inputs::none;
    lost = false;
    score = 0;

}

void Game::gameLoop(){
    initGrid();

    while(mGameState != GameState::quit){
        while(SDL_PollEvent(&mEvent)){
           handleInput(mEvent);
        }
        
        update();

        draw();

    }
}

void Game::update(){

}

void Game::draw(){
    SDL_SetRenderDrawColor(handle.getRenderer(), 187, 173, 160, 255);
    SDL_RenderClear(handle.getRenderer());
    
    drawGrid();

    SDL_Color clr = {.r = 0, .g = 0, .b = 0, .a = 255};

    texts.setText("score: " + std::to_string(score), handle.getRenderer(), clr);
    texts.destRect.x = 0;
    texts.destRect.y = 10;
    texts.destRect.w = 175;
    texts.destRect.h = 85;

    texts.drawText(handle.getRenderer());
    SDL_RenderPresent(handle.getRenderer());

    SDL_DestroyTexture(handle.getTexture());
}

void Game::handleInput(SDL_Event& event){
    switch (event.type)
    {
    case SDL_QUIT:
        mGameState = GameState::quit;
        break;
    case SDL_KEYDOWN:
        handleKeyboardInput(event);
        break;
    default:
        break;
    }
}

void Game::handleKeyboardInput(SDL_Event& event){
    switch (event.key.keysym.sym)
    {
    case SDLK_LEFT:
        input = Inputs::left;
        moveLeft();
        spawnBox();
        break;
    case SDLK_UP:
        input = Inputs::up;
        moveUp();
        spawnBox();
        break;
    case SDLK_RIGHT:
        input = Inputs::right;
        moveRight();
        spawnBox();
        break;
    case SDLK_DOWN:
        input = Inputs::down;
        moveDown();
        spawnBox();
        break;
    default:
        break;
    }
}

void Game::drawGrid(){
    SDL_Color clr;
    
    SDL_Rect rect;
    rect.w = mGrid.cellSize;
    rect.h = mGrid.cellSize;

    int size = mGrid.nx * mGrid.cellSize;
    int startPointx = (handle.getWidht() - size) / 2;
    int startPointy = (handle.getHeight() - size) / 2;
    int offset = mGrid.cellSize / 10;

    SDL_SetRenderDrawColor(handle.getRenderer(), 172, 159, 147, 255);
    for(int i = 0; i < mGrid.ny; i++){
        for(int j = 0; j < mGrid.nx; j++){
            rect.x = startPointx + (j * mGrid.cellSize - offset) + j*10;
            rect.y = startPointy + (i * mGrid.cellSize - offset) + i *10; 
            handle.drawRect(rect);
        }
    }

    rect.w -= mGrid.cellSize / 6;
    rect.h -= mGrid.cellSize / 6;
    
    clr.r = 119;
    clr.g = 110;
    clr.b = 101;
    clr.a = 255;


    SDL_SetRenderDrawColor(handle.getRenderer(), 238, 228, 218, 255);
    for(int i = 0; i < mGrid.ny; i++){
        for(int j = 0; j < mGrid.nx; j++){
            if(boxes.at(i).at(j).value >= 2){
                rect.x = startPointx + ((j * mGrid.cellSize) - offset) + j*10 + (mGrid.cellSize / 6) / 2;
                rect.y = startPointy + ((i * mGrid.cellSize) - offset) + i*10 + (mGrid.cellSize / 6) / 2; 
                handle.drawRect(rect);
                texts.setText(std::to_string(boxes.at(i).at(j).value), handle.getRenderer(), clr);
                texts.destRect = rect;
                texts.drawText(handle.getRenderer());
            }
        }
    }

    if(lost == true){
    clr.r = 255;
    clr.g = 20;
    clr.b = 20;
    clr.a = 255;

    texts.destRect.x = 50;
    texts.destRect.y = 200;
    texts.destRect.w = 500;
    texts.destRect.h = 200;

    SDL_SetRenderDrawColor(handle.getRenderer(), 130, 130, 130, 255);
    handle.drawRect(texts.destRect);

    texts.setText("Game Over! Score:" + std::to_string(score), handle.getRenderer(), clr);
    texts.drawText(handle.getRenderer());
    }
}

void Game::initGrid(){  
    for(int i = 0; i < mGrid.ny; i++){
        boxes.push_back(std::vector<Box>(mGrid.ny, Box()));
        for(int j = 0; j < mGrid.nx; j++){
            boxes.at(i).at(j).x = j;
            boxes.at(i).at(j).y = i;
            boxes.at(i).at(j).value = 0;
        }
    }

    spawnBox();
    spawnBox();
}

void Game::moveLeft(){
    for(int row = 0; row < mGrid.ny; row++){
        bool ok = false;

        for(auto& box : boxes.at(row)){
            box.combined = false;
        }

        while(!ok){
            ok = true;
            for(int j = 0; j < mGrid.nx; j++){
                if(boxes.at(row).at(j).value == 0 || j == 0)
                    continue;
                else if(boxes.at(row).at(j-1).value == 0 && boxes.at(row).at(j).value >= 2){
                    std::iter_swap(boxes.at(row).begin() + j - 1, boxes.at(row).begin() + j);
                    ok = false;
                }
                if((boxes.at(row).at(j-1).value == boxes.at(row).at(j).value) && 
                boxes.at(row).at(j).value >= 2 && boxes.at(row).at(j).combined == false ){
                    boxes.at(row).at(j-1).value *= 2;
                    score += boxes.at(row).at(j-1).value;
                    boxes.at(row).at(j).value = 0;
                    boxes.at(row).at(j-1).combined = true;
                    ok = false;
                }
            }
        }
    }
}

void Game::moveUp(){
     for(int coll = 0; coll < mGrid.ny; coll++){
        bool ok = false;

        for(int i = 0; i < mGrid.ny; i++){
            boxes.at(i).at(coll).combined = false;
        }

        while(!ok){
            ok = true;
            for(int i = 0; i < mGrid.ny; i++){
                if(boxes.at(i).at(coll).value == 0 || i == 0)
                    continue;

                else if(boxes.at(i-1).at(coll).value == 0 && boxes.at(i).at(coll).value >= 2){
                    std::iter_swap(boxes.at(i).begin() + coll, boxes.at(i-1).begin() + coll);
                    ok = false;
                }
                if((boxes.at(i-1).at(coll).value == boxes.at(i).at(coll).value) && 
                boxes.at(i).at(coll).value >= 2 && boxes.at(i).at(coll).combined == false ){
                    boxes.at(i-1).at(coll).value *= 2;
                    score += boxes.at(i-1).at(coll).value;
                    boxes.at(i).at(coll).value = 0;
                    boxes.at(i-1).at(coll).combined = true;
                    ok = false;
                }
            }
        }
    }
}

void Game::moveRight(){
    for(int row = 0; row < mGrid.ny; row++){
        bool ok = false;

        for(auto& box : boxes.at(row)){
            box.combined = false;
        }

        while(!ok){
            ok = true;
            for(int j = mGrid.nx - 1; j >= 0; j--){
                if(boxes.at(row).at(j).value == 0 || j == (mGrid.nx - 1))
                    continue;

                else if(boxes.at(row).at(j+1).value == 0 && boxes.at(row).at(j).value >= 2){
                    std::iter_swap(boxes.at(row).begin() + j + 1, boxes.at(row).begin() + j);
                    ok = false;
                }
                if((boxes.at(row).at(j).value == boxes.at(row).at(j + 1).value) && 
                boxes.at(row).at(j).value >= 2 && boxes.at(row).at(j+1).combined == false ){
                    boxes.at(row).at(j+1).value *= 2;
                    score += boxes.at(row).at(j+1).value;
                    boxes.at(row).at(j).value = 0;
                    boxes.at(row).at(j+1).combined = true;
                    ok = false;
                }
            }
        }
    }
}

void Game::moveDown(){
    for(int coll = 0; coll < mGrid.ny; coll++){
        bool ok = false;

        for(int i = 0; i < mGrid.ny; i++){
            boxes.at(i).at(coll).combined = false;
        }

        while(!ok){
            ok = true;
            for(int i = mGrid.ny - 1; i >= 0; i--){
                if(boxes.at(i).at(coll).value == 0 || i == mGrid.ny - 1)
                    continue;

                else if(boxes.at(i+1).at(coll).value == 0 && boxes.at(i).at(coll).value >= 2){
                    std::iter_swap(boxes.at(i).begin() + coll, boxes.at(i+1).begin() + coll);
                    ok = false;
                }
                if((boxes.at(i+1).at(coll).value == boxes.at(i).at(coll).value) && 
                boxes.at(i).at(coll).value >= 2 && boxes.at(i+1).at(coll).combined == false ){
                    boxes.at(i+1).at(coll).value *= 2;
                    score += boxes.at(i+1).at(coll).value;
                    boxes.at(i).at(coll).value = 0;
                    boxes.at(i+1).at(coll).combined = true;
                    ok = false;
                }
            }
        }
    }
}

void Game::spawnBox(){
    bool ok = false;
    for(int i = 0; i < mGrid.ny; i++){
        for(int j = 0; j < mGrid.nx; j++){
            if(boxes.at(i).at(j).value < 2){
                ok = true;
            }
        }
    }
    if(ok == false){
        lost = true;
        return;
    }
    while(1){
        int x = rand() % 4;
        int y = rand() % 4;
        if(boxes.at(x).at(y).value == 0){
            boxes.at(x).at(y).value = 2;
            return;
        }
    }
}