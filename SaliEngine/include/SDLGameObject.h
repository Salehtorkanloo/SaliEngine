#ifndef SDLGAMEOBJECT_H_INCLUDED
#define SDLGAMEOBJECT_H_INCLUDED
#include<GameObject.h>
#include<Vector2D.h>
#include<LoaderParameters.h>
class SDLGameObject: public GameObject{
public:
     SDLGameObject():GameObject::GameObject()
     {};
     virtual void draw() = 0;
     virtual void update() = 0;
     virtual void clean() = 0;

     virtual void load(const LoaderParameters* laoderParameters) = 0;

    const Vector2D& getPosition() {return g_position;}
    const int& getWidth() {return g_width;}
    const int& getHeight() {return g_height;}
protected:
    Vector2D g_position = Vector2D(0,0);
    Vector2D g_velocity = Vector2D(0,0);
    Vector2D g_acceleration = Vector2D(0,0);
    int g_width;
    int g_height;
    int g_currentFrame;
    int g_currentRow;
    std::string g_textureID;
};


#endif // SDLGAMEOBJECT_H_INCLUDED
