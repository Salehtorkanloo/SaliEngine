#include<iostream>
#include<Game.h>
#include<TextureManager.h>
#include<LoaderParameters.h>
#include<Player.h>
#include<vector>
#include<InputHandler.h>
#include<MenuButton.h>
#include<GameObjectFactory.h>
TheGame* TheGame::instance(){
    if(pInstance == NULL){
        pInstance = new Game();
    }
    return pInstance;
}
TheGame* TheGame::pInstance = 0;
bool TheGame::init(const char* title, int x, int y, int w, int h, bool fullScreen){
    GameObjectFactory::instance()->registerType("MenuButton", new MenuButtonCreator());
    std::cout << "SDL init attempt...\n";
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0){
        std::cout << "SDL init failure - " << SDL_GetError() << "\n";
        return false;
    }


    //sdl init success
    std::cout << "SDL init success\n";
    g_pWindow = SDL_CreateWindow(title, x ,y, w, h, fullScreen? SDL_WINDOW_FULLSCREEN : 0);
    //sdl window creation failure
    if(g_pWindow == NULL){
        std::cout << "SDL window creation failure - " << SDL_GetError() << "\n";
        return false;
    }
    //SDl window creation success
    g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);

    if(g_pRenderer == NULL){
        std::cout << "SDL renderer creation failure - " << SDL_GetError() << "\n";
        return false;
    }

    //SDL renderer creation success
    //Everything went correctly
    //Initialize the game core loop
    g_bRunning = true;
    //create the game finite state machine
    g_gameStateMachine = new GameStateMachine();
    g_gameStateMachine->changeState(Menu);
    SDL_SetRenderDrawColor(g_pRenderer, 0, 0, 0, 255);




}
void TheGame::handleEvents(){
    TheInput::instance()->update();

}
void TheGame::update(){
    //update
    g_gameStateMachine->update();
}
void TheGame::renderer(){
    SDL_RenderClear(g_pRenderer);
    g_gameStateMachine->render();
    SDL_RenderPresent(g_pRenderer);
}
void TheGame::clean(){
   g_bRunning = false;
   SDL_DestroyWindow(g_pWindow);
   SDL_DestroyRenderer(g_pRenderer);
   SDL_Quit();
}
bool TheGame::running() {return g_bRunning;}
SDL_Renderer* TheGame::getRenderer() const {return g_pRenderer;}

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, char** argv){

    TheGame::instance()->init("SaliEngine", 200, 200 ,640, 480, false);

    Uint32 frameStart, frameTime;
    while(TheGame::instance()->running()){
        frameStart = SDL_GetTicks();

        if(TheInput::instance()->isKeyDown(EnterKey)){
            TheGame::instance()->getStateMachine()->changeState(Play);
        }

        TheGame::instance()->handleEvents();


        TheGame::instance()->update();
        TheGame::instance()->renderer();

        frameTime = SDL_GetTicks() - frameStart;

        if(frameTime < DELAY_TIME){
            SDL_Delay(int(DELAY_TIME - frameTime));
        }
}

    std::cout << "end of the game...";
    TheGame::instance()->clean();

}
