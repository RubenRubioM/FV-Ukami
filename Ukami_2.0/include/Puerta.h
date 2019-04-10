#ifndef PUERTA_H
#define PUERTA_H

#include <SFML/Graphics.hpp>
class Puerta
{
    public:
        Puerta();
        virtual ~Puerta();
        void drawPuerta(sf::RenderWindow & window);
    protected:

    private:
        sf::Texture* texture;
        sf::Sprite* sprite;
        void loadTexture();
        void loadSprite();
        void colocarSprite();
};

#endif // PUERTA_H
