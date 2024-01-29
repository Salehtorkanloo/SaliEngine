#include<Game.h>
#include<iostream>
#include<SDL.h>
#include<TextureManager.h>
#include<InputHandler.h>
#include<GameObjectFactory.h>
//=====static pointer to instance======
Game* TheGame::pInstance = NULL;
bool TheGame::init(const char* title ,int s_x, int s_y, int s_width, int s_height, bool fScreen){
    scr_width = s_width;
    scr_height = s_height;
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        std::cerr << "SDL initialization failure - " << SDL_GetError() << "\n";
        return false;
    }
    int flags = fScreen? SDL_WINDOW_FULLSCREEN : SDL_WINDOW_SHOWN;
    g_pWindow = SDL_CreateWindow(title,s_x, s_y, s_width, s_height,flags);
    if(g_pWindow == NULL){
        std::cerr << "SDL window creation failure - " << SDL_GetError() << "\n";
        return false;
    }
    g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);
    if(g_pRenderer == NULL){
        std::cerr << "SDL renderer creation failure - " << SDL_GetError() << "\n";
        return false;
    }
    std::cout << "SDl int success \n";



    g_beRunning = true;
    return true;

}
void TheGame::update(){
    //The Input Update
    TheInput::instance()->update();
    //The gameObjects update
    for(GameObject* gameObject : g_gameObjects){
        gameObject->update();
    }
}
void TheGame::handleEvents(){
    SDL_Event e;
    if(SDL_PollEvent(&e)){
        if(e.type == SDL_QUIT){
            g_beRunning = false;
        }
    }
}
void TheGame::render(){
    SDL_RenderClear(g_pRenderer);

    for(GameObject* gameObject : g_gameObjects){
        gameObject->draw();

    }
    SDL_RenderPresent(g_pRenderer);
}
void TheGame::clean(){
    g_beRunning = false;
    SDL_DestroyWindow(g_pWindow);
    SDL_DestroyRenderer(g_pRenderer);
    SDL_Quit();
}
GameObject* TheGame::AddGameObject(std::string id){
    GameObject* gameObject = GameObjectFactory::instance()->create(id);
    if(gameObject == NULL){
        std::cerr << "please register the gameObject first \n";
        return NULL;
    }
    g_gameObjects.push_back(gameObject);
    return gameObject;
}
GameObject* TheGame::AddGameObject(GameObject* gameObject){
    g_gameObjects.push_back(gameObject);
    return gameObject;
}
GameObject* TheGame::RegisterAndAddGameObject(std::string id, BaseCreator* creator){
    std::cout << "1\n";
    GameObjectFactory::instance()->registerType(id, creator);
    std::cout << "2\n";
    return AddGameObject(id);
}
bool TheGame::isRegistered(std::string id){
    return GameObjectFactory::instance()->isRegistered(id);
}
const bool& TheGame::isGameRunning()const{
    return g_beRunning;
}
