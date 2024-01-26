#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED
class GameObject{
public:
    virtual void draw() = 0;
    virtual void update() = 0;
    virtual void clean() = 0;
protected:
    GameObject(){};
};


#endif // GAMEOBJECT_H_INCLUDED
