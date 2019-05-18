#ifndef PALANCA_H
#define PALANCA_H

#include "SFML/Graphics.hpp"

using namespace sf;
using namespace std;

class Palanca
{
public:
    Palanca();
    virtual ~Palanca();
    void crearPalanca(int posx, int posy);
    void drawPalanca(RenderWindow &window);
    void hidePalanca();
    Sprite getSprite();

protected:
private:
    Sprite palancaS;
    Texture palancaT;
    Sprite bocadilloS;
};

#endif // PALANCA_H
