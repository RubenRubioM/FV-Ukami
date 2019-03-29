#ifndef CAMARA_H
#define CAMARA_H

#include <SFML/Graphics.hpp>
#include "tinyxml2.h"
#include "TextureHolder.h"
#include "Map.h"
#include "Ninja1.h"
#include "Ninja2.h"
#include "Box2D/Box2D.h";
#include <iostream>
#include <vector>
#include <map>

using namespace tinyxml2;
using namespace std;
using namespace sf;

class Camara
{
    public:
        static Camara *getInstance(){
            if(unicaInstancia==0){
                unicaInstancia = new Camara();
            }
            return unicaInstancia;
        }
        virtual ~Camara();
        void bloquear();
        void desbloquear();
        void moverCamara(float);
        void setCoordenadas(int, int);
        void comprobarCamara(Ninja1 ninja1, Ninja2 ninja2, View &view);

        sf::View *getView();
        float getCamaraXSize();
        float getCamaraYSize();
        int getCamaraPosX();
        int getCamaraPosY();


    private:
        Camara();
        static Camara *unicaInstancia;
        bool bloqueada = false;
        int camaraPosX, camaraPosY = 0; //Para saber donde está la camara

        float camaraXSize = 800;
        float camaraYSize = 600;
        sf::View *camara;
};

#endif // CAMARA_H
