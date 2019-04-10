#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "tinyxml2.h"
#include "TextureHolder.h"
#include "Map.h"
#include "Ninja.h"
#include "Ninja1.h"
#include "Ninja2.h"
#include <iostream>
#include <vector>
#include <map>
#include "Box2D/Box2D.h"
#include "SFMLDebugDraw.h"

using namespace tinyxml2;
using namespace std;
using namespace sf;

class Game
{
    public:
        static Game *getInstance(){
            if(unicaInstancia == 0)
                    unicaInstancia = new Game();
            return unicaInstancia;
        }
        virtual ~Game();
        // Método para actualizar la vista cuando los ninjas se mueven por el mapa
        void updateView(Ninja1 ninja1, Ninja2 ninja2, View &view);

    protected:

    private:
        Game();
        static Game *unicaInstancia;
};

#endif // GAME_H
