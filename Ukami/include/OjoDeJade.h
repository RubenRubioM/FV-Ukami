#ifndef OJODEJADE_H
#define OJODEJADE_H

#include <iostream>
#include "SFML/Graphics.hpp"

class OjoDeJade
{
    public:
        OjoDeJade(float, float);
        virtual ~OjoDeJade();

        float pos_x;
        float pos_y;

        sf::Texture texture;
        sf::Sprite sprite;

        sf::Sprite getSprite();
        void dibujaOjoDeJade(sf::RenderWindow &window);

    protected:

    private:
};

#endif // OJODEJADE_H
