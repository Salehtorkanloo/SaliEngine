#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include<SDL.h>
#include<GameStateMachine.h>
class Game{
public:
    static Game* instance();

    bool init(const char* title, int x, int y, int w, int h, bool fullScreen);
    void handleEvents();
    void update();
    void renderer();
    void clean();
    bool running();
    GameStateMachine* getStateMachine(){return g_gameStateMachine;}
    SDL_Renderer* getRenderer() const;

private:
    Game(){};
    static Game* pInstance;
    SDL_Window* g_pWindow;
    SDL_Renderer* g_pRenderer;
    bool g_bRunning = false;
    GameStateMachine* g_gameStateMachine = 0;
};
typedef Game TheGame;

#endif // GAME_H_INCLUDED
