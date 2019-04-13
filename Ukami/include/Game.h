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
#include "Enemigo.h"
#include "Enemigo1.h"
#include "Hud.h"
#include "Puerta.h"
#include "Kanji.h"
#include <iostream>
#include <vector>
#include <map>
#include "Box2D/Box2D.h"
#include "SFMLDebugDraw.h"
#include <stddef.h>

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


    protected:

    private:
        Game();
        static Game *unicaInstancia;

        Ninja1 *ninja1;
        Ninja2 *ninja2;

        Hud* hud;

        vector<Enemigo*> enemigos;
        Enemigo* enemigoCercano;

        sf::Clock fpsClock;
        sf::Clock deltaClock;
        sf::Time deltaTime;
        sf::Clock frameClock;
        int contadorFPS = 0;
        bool mostrarFPS = true;
        int estado = 0; // Como sustitucion hasta que tengamos el patron State ||||  0 = juego normal   1 = minijuego Kanji"

        void calcularFPS();
        // Método para actualizar la vista cuando los ninjas se mueven por el mapa
        void updateView(Ninja1 ninja1, Ninja2 ninja2, View &view);
        Enemigo* enemigoMasCercano();
};

#endif // GAME_H
