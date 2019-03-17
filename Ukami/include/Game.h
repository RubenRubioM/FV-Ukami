
#ifndef GAME_H
#define GAME_H

#include "SFML/Graphics.hpp"
#include "Ninja1.h"
#include "Ninja2.h"
#include "Camara.h"

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
        float comprobarDistanciaEntrePersonajes();

        //Getters
        sf::RenderWindow* getWindow();
        virtual ~Game();

    protected:

    private:
        Game(int,int,string);
        static Game *unicaInstancia;

        Camara *camara;
        sf::RenderWindow *window; //La ventana
        sf::Event *event; //Para manejar los eventos
        sf::Time deltaTime; //Tiempo trascurrido entre cada frame
        Ninja *personaje1; //Personaje 1
        Ninja *personaje2; //Personaje 2
        sf::Texture *bgTexture; //Textura del background
        sf::Sprite *background; //Imagen del background
};

#endif // GAME_H
