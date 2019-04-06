#ifndef NINJA1_H
#define NINJA1_H

#include "Ninja.h"

class Ninja1 : public Ninja
{
    public:
        Ninja1(float posx, float posy, b2World* world);
        void updateMovement(View &view, float);
        void drawNinja(RenderWindow &window);
        Sprite getSprite();
        virtual ~Ninja1();
    protected:

    private:
        b2Body *ninjaBody;


};

#endif // NINJA1_H
