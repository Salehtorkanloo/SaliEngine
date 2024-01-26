#include<GameOverState.h>
#include<TextureManager.h>
#include<AnimatedGraphic.h>
#include<MenuButton.h>
#include<Game.h>
const std::string GameOverState::g_stateID = "GAMEOVER";
void GameOverState::on_backToMain_clicked(){
    TheGame::instance()->getStateMachine()->changeState(Menu);
}
void GameOverState::on_restartPlay_clicked(){
    TheGame::instance()->getStateMachine()->changeState(Play);
}
void GameOverState::update() const{
    for(std::vector<SDLGameObject*>::size_type i = 0; i < g_gameObjects.size(); ++i){
        g_gameObjects[i]->update();
        if(TheGame::instance()->getStateMachine()->getCurrentState()->getID() != "GAMEOVER"){
            return;
        }
    }
}
void GameOverState::render() const{
    for(std::vector<SDLGameObject*>::size_type i = 0 ; i < g_gameObjects.size(); ++i){
        g_gameObjects[i]->draw();
    }
}
bool GameOverState::onEnter(){

    std::cout << "entering the GameOverState\n";
    return true;
}
bool GameOverState::onExit(){
    for(std::vector<SDLGameObject*>::size_type i = 0; i < g_gameObjects.size(); ++i){
        g_gameObjects[i]->clean();
    }
    g_gameObjects.clear();
    std::cout << "exiting the GameOverState\n";

    return true;
}
