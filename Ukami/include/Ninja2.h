#ifndef NINJA2_H
#define NINJA2_H

#include "Ninja.h"

class Ninja2
{
    public:
        Ninja2(float posx, float posy, b2World* world);
        void updateMovement(View &view, float);
        void drawNinja(RenderWindow &window);

        Sprite getSprite();
        virtual ~Ninja2();
    protected:

    private:
        Texture texture;
        Sprite sprite;
        b2Body *ninjaBody;
        float velocity = 1;
};

#endif // NINJA2_H
