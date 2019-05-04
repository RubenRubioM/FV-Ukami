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
#include "GuardiaEstatico.h"
#include "GuardiaDinamico.h"
#include "Hud.h"
#include "Puerta.h"
#include "Kanji.h"
#include "AnimatedSprite.h"
#include "Animation.h"
#include <iostream>
#include <vector>
#include <map>
#include "Box2D/Box2D.h"
#include "SFMLDebugDraw.h"
#include "menu.h"
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
        void setEstado(int state);


    protected:

    private:
        Game();
        static Game *unicaInstancia;

        Ninja1 *ninja1;
        Ninja2 *ninja2;

        Hud* hud;


        sf::Clock fpsClock;
        sf::Clock deltaClock;
        sf::Time deltaTime;
        sf::Clock frameClock;
        int contadorFPS = 0;
        bool mostrarFPS = true;
        int estado = 2; // Como sustitucion hasta que tengamos el patron State ||||  0 = juego normal   1 = minijuego Kanji"
        int numKanji = 0;
        int numGuardias = 0;
        int numKanjisResueltos = 0;
        int nivel = 1;

        vector<GuardiaEstatico*> guardiasEstaticos; //Array con todos los guardias (quiza luego se hace herencia en diferentes tipos de guardias)
        vector<GuardiaDinamico*> guardiasDinamicos;
        GuardiaEstatico* guardiaEstaticoCercano; //Me guardo que guardia es el mas cercano cuando silbo



        void calcularFPS();
        // Método para actualizar la vista cuando los ninjas se mueven por el mapa
        void updateView(Ninja1 ninja1, Ninja2 ninja2, View &view);
        //metodos
        GuardiaEstatico* guardiaEstaticoMasCercano();

};

#endif // GAME_H
