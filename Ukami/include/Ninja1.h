#ifndef NINJA1_H
#define NINJA1_H

#include "Ninja.h"
#include "AnimatedSprite.h"
#include "Animation.h"

class Ninja1 : public Ninja
{
    public:
        Ninja1(float posx, float posy, b2World* world);
        void updateMovement(View &view, float, sf::Clock);
        void drawNinja(RenderWindow &window);
        AnimatedSprite getSprite();
        virtual ~Ninja1();
    protected:

    private:

};

#endif // NINJA1_H
