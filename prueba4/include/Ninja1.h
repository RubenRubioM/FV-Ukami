#ifndef NINJA1_H
#define NINJA1_H

#include "Ninja.h"

class Ninja1 : public Ninja
{
    public:
        Ninja1(float posx, float posy, b2World* world);
        virtual ~Ninja1();
        void updateMovement(View &view);
        void drawNinja(RenderWindow &window);
    protected:

    private:
        Texture texture;
        Sprite sprite;
        b2Body *ninjaBody;
};

#endif // NINJA1_H
