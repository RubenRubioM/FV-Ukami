#ifndef NINJA1_H
#define NINJA1_H

#include "Ninja.h"
#include "AnimatedSprite.h"
#include "Animation.h"

class Ninja1 : public Ninja
{
    public:
        Ninja1(float posx, float posy, b2World* world);
        void updateMovement(View &view, float, sf::Clock);
        void drawNinja(RenderWindow &window);
        AnimatedSprite getSprite();

        // =======Metodos del dash=======
        void activarDash();
        void desactivarDash();
        void descargarDash(float);
        void cargarDash(float);
        // ==============================

        virtual ~Ninja1();
    private:

        //DASH
        Texture textureDash;
        Sprite spriteDash;
        Animation dashAnimationRight;
        b2PolygonShape shape2;
        bool enDash = false; //Booleano para saber si esta en Dash
        bool dashMax = true; //Booleano para saber si tiene el Dash cargado al maximo
        float duracionDash = 1; //Duracion del Dash
        float maxDash = 100; //Duracion maxima del Dash (se usa en los sliders tambien)
        float recargaDash = 3; //Tiempo para recargar el Dash
        sf::Clock tiempoDash; //Reloj para ver la duracion del Dash
        sf::RectangleShape sliderDash[2];



};

#endif // NINJA1_H
