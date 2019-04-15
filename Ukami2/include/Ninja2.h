<<<<<<< HEAD:Ukami2/include/Ninja2.h
#ifndef NINJA2_H
#define NINJA2_H

#include "Ninja.h"

class Ninja2 : public Ninja
{
    public:
        Ninja2(float posx, float posy, b2World* world);
        void updateMovement(View &view, float,sf::Clock);
        void drawNinja(RenderWindow &window);

        Sprite getSprite();
        virtual ~Ninja2();
    protected:


    private:

};

#endif // NINJA2_H
=======
#ifndef NINJA2_H
#define NINJA2_H

#include "Ninja.h"

class Ninja2 : public Ninja
{
    public:
        Ninja2(float posx, float posy, b2World* world);
        void updateMovement(View &view, float,sf::Clock);
        void drawNinja(RenderWindow &window);

        Sprite getSprite();
        virtual ~Ninja2();
    protected:


    private:

};

#endif // NINJA2_H
>>>>>>> 57f57d12db4eb9365f2d2aa12be8212bd48b0e7c:Ukami/include/Ninja2.h
