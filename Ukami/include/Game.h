#ifndef GAME_H
#define GAME_H

#include "SFML/Graphics.hpp"
#include "Ninja1.h"
#include "Ninja2.h"
#include "Enemigo1.h"
#include "Enemigo2.h"
#include "Obj.h"

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
        Ninja *personaje1; //Personaje 1
        Ninja *personaje2; //Personaje 2
        Enemigo *enemigo1; //Personaje 1
        Enemigo *enemigo2; //Personaje 1

};

#endif // GAME_H
