#ifndef NINJA_H
#define NINJA_H

#include <SFML/Graphics.hpp>
#include "tinyxml2.h"
#include "TextureHolder.h"
#include "Map.h"
#include "Box2D/Box2D.h";
#include <iostream>
#include <vector>
#include <map>

using namespace tinyxml2;
using namespace std;
using namespace sf;

class Ninja
{
    public:
        Ninja();
        virtual ~Ninja();
        void updateMovement(View &view);
        void drawNinja(RenderWindow &window);
    protected:
        Texture texture;
        Sprite sprite;
        b2Body *ninjaBody;
    private:
};

#endif // NINJA_H
