#ifndef OBJ_H
#define OBJ_H

#include "SFML/Graphics.hpp"
#include <iostream>

class Obj
{
    public:
        Obj();
        virtual ~Obj();

        //Getters
        sf::Sprite *getSprite();

    protected:
        sf::Texture *texture;
        sf::Sprite *sprite;

    private:
};

#endif // OBJ_H
