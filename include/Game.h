#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include<iostream>

#include<SDL.h>
#include<GameObject.h>
#include<vector>
#include<GameObjectFactory.h>
//#include<Player.h>
#include<Game.h>
class Game{
public:
    static Game* instance(){
        if(pInstance == NULL){
            pInstance = new Game;
        }
        return pInstance;
    }

    bool init(const char* title,int s_x, int s_y, int s_width, int s_height, bool fScreen);
    void update();
    void handleEvents();
    void render();
    void clean();

    int getScreenWidth(){return scr_width;}
    int getScreenHeight(){return scr_height;}

    GameObject* AddGameObject(std::string id);
    GameObject* AddGameObject(GameObject* GameObject);
    GameObject* RegisterAndAddGameObject(std::string id, BaseCreator* creator);
    bool isRegistered(std::string id);
    const bool& isGameRunning()const;
    SDL_Renderer* getRenderer()const{return g_pRenderer;}
    SDL_Window* getWindow()const{return g_pWindow;}
public:
    int scr_width;
    int scr_height;
    static Game* pInstance;
    bool g_beRunning;
    SDL_Window* g_pWindow;
    SDL_Renderer* g_pRenderer;
    std::vector<GameObject*> g_gameObjects;
};
typedef Game TheGame;


#endif // GAME_H_INCLUDED
