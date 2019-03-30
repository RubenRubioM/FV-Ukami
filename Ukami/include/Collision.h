#ifndef COLLISION_H
#define COLLISION_H

#include <SFML/Graphics.hpp>
#include "tinyxml2.h"
#include <iostream>
#include <vector>
#include <map>

using namespace tinyxml2;
using namespace std;
using namespace sf;

class Collision
{
    public:
        Collision();
        virtual ~Collision();
        // Funcion para cargar las colisiones que llamaremos dentro del metodo del Map, initMap()
        void loadCollision(XMLElement* mapa);
        //bool checkCollision(Player player1/player2, Collision name_of_collision);
    protected:

    private:
        // mapa donde tendremos como clave el nombre de la colision y las coordenadas: x/y/width/height
        multimap<string, vector<float>> collisions;
};

#endif // COLLISION_H
