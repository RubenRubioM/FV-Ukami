#ifndef NINJA2_H
#define NINJA2_H

#include "Ninja.h"

class Ninja2 : public Ninja
{
    public:
        Ninja2(float posx, float posy, b2World* world);
        void updateMovement(View &view, float,sf::Clock);
        void drawNinja(RenderWindow &window);

        AnimatedSprite getSprite();
        virtual ~Ninja2();
    protected:


    private:

};

#endif // NINJA2_H
