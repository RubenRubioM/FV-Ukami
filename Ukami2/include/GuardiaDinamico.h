#ifndef GUARDIADINAMICO_H
#define GUARDIADINAMICO_H


#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class GuardiaDinamico
{
    public:
        GuardiaDinamico(float,float);
        virtual ~GuardiaDinamico();

        bool getMoviendose();
        sf::Sprite *getSprite();
        sf::ConvexShape* getVision();

        //Metodos
        void drawGuardiaDinamico(sf::RenderWindow &window);
        void updateGuardiaDinamico(float);

    private:
        sf::Texture *texture;
        sf::Sprite *sprite;
        sf::ConvexShape *triangle; //Vision
        float velocidad = 0.12;
        int metros = 0;
        int rango = 120; //Rango de distancia que anda
        sf::Clock relojFlotacion;
        bool subiendo =false;

};

#endif // GUARDIADINAMICO_H
