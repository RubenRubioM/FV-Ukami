#ifndef NINJA2_H
#define NINJA2_H

#include "Ninja.h"

class Ninja2 : public Ninja
{
    public:
        Ninja2(float posx, float posy, b2World* world);
        void updateMovement(View &view, float,sf::Clock);
        void drawNinja(RenderWindow &window);
        void setTrepando(bool);
        AnimatedSprite getSprite();
        bool trepando;
        virtual ~Ninja2();
    protected:


    private:
        sf::Texture texture3;
        sf::Clock cdTrepar;
        Animation treparAnimation;
};

#endif // NINJA2_H
