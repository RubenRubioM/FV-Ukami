#ifndef NINJA2_H
#define NINJA2_H

#include "Ninja.h"

class Ninja2 : public Ninja
{
    public:
        Ninja2(float posx, float posy, b2World* world);
        virtual ~Ninja2();
        void updateMovement(View &view);
        void drawNinja(RenderWindow &window);
    protected:

    private:
        Texture texture;
        Sprite sprite;
        b2Body *ninjaBody;
};

#endif // NINJA2_H
