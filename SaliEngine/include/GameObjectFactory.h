#ifndef GAMEOBJECTFACTORY_H_INCLUDED
#define GAMEOBJECTFACTORY_H_INCLUDED
#include<map>
#include<SDLGameObject.h>
class BaseCreator{
public:
    virtual SDLGameObject* createGameObject() = 0;
};
class GameObjectFactory{
public:
    static GameObjectFactory* instance(){
        if(pInstance == NULL){
            pInstance = new GameObjectFactory();
        }
        return pInstance;
    }

    bool registerType(std::string ID, BaseCreator* pCreator){
        //check for existence of the Creator
        std::map<std::string, BaseCreator*>::iterator it =
        g_creators.find(ID);

        if(it != g_creators.end()){
            //the creator does already exists
            delete pCreator;
            return false;
        }
        //the creator is new!
        g_creators[ID] = pCreator;

        return true;
    }
    SDLGameObject* create(std::string ID){
        //check for existence of the creator
        std::map<std::string, BaseCreator*>::iterator it =
        g_creators.find(ID);

        if(it == g_creators.end()){
            std::cout << "GameObject creation failure - the creator doesn't exists in the map! \n";
            return NULL;
        }

        //the creator does exist in the map!
        //creates the gameObject and returns it...
        BaseCreator* pCreator = (*it).second;
        return pCreator->createGameObject();
    }
private:
    //ensure that the object will only construct by the singleton
    GameObjectFactory() = default;
    static GameObjectFactory* pInstance;
    std::map<std::string, BaseCreator*> g_creators;
};



#endif // GAMEOBJECTFACTORY_H_INCLUDED
