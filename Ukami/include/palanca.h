#ifndef PALANCA_H
#define PALANCA_H

#include <SFML/Graphics.hpp>

using namespace std;

class palanca
{
    public:
        palanca();
        virtual ~palanca();
        void drawPalanca(sf::RenderWindow & window);
    protected:

    private:
        sf::Texture* texture;
        sf::Sprite* sprite;
        void loadTexture();
        void loadSprite();
        void colocarSprite();
};

#endif // PALANCA_H
