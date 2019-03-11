
#ifndef GAME_H
#define GAME_H

#include "SFML/Graphics.hpp"
#include "Ninja1.h"
#include "Guardia.h"
#include <vector>

#define MAX_GUARDIAS    10
using namespace std;


class Game
{
    public:
        //Singleton
        static Game *getInstance(){
            if(unicaInstancia == 0)
                unicaInstancia = new Game(1280,720,"Ukami");

            return unicaInstancia;
        }
        //Fin del Singleton

        void gameLoop(); //Bucle mientras que la ventana este abierta
        void draw(); //Metodo para dibujar todo
        void eventsLoop(); //Metodo para detetar los eventos


        //Getters
        sf::RenderWindow* getWindow();
        virtual ~Game();

    protected:

    private:
        Game(int,int,string);
        static Game *unicaInstancia;


        sf::RenderWindow *window; //La ventana
        sf::Event *event; //Para manejar los eventos
        sf::Time deltaTime; //Tiempo trascurrido entre cada frame
        Ninja1 *personaje1; //Personaje 1
        vector<Guardia*> guardias; //Array con todos los guardias (quiza luego se hace herencia en diferentes tipos de guardias)
        Guardia* guardiaCercano; //Me guardo que guardia es el mas cercano cuando silbo

        //metodos
        Guardia* guardiaMasCercano();
};

#endif // GAME_H
