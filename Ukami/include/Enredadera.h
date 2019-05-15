#ifndef ENREDADERA_H
#define ENREDADERA_H


#include "SFML/Graphics.hpp"

using namespace sf;
using namespace std;

class Enredadera
{
    public:
        Enredadera();
        virtual ~Enredadera();
        void crearEnredadera(int posx, int posy);
        void drawEnredadera(RenderWindow &window);
        void hideEnredadera();
        Sprite getSprite();

    protected:

    private:
        Sprite enredaderaS;
        Texture enredaderaT;
        Sprite bocadilloS;
};

#endif // ENREDADERA_H
