#ifndef PALANCA_H
#define PALANCA_H

#include <SFML/Graphics.hpp>

using namespace std;

class Palanca
{
    public:
        Palanca();
        virtual ~Palanca();
        void drawPalanca(sf::RenderWindow & window);
    protected:

    private:
        sf::Texture texture;
        sf::Sprite sprite;
};

#endif // PALANCA_H
