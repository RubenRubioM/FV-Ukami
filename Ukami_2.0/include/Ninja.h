#ifndef NINJA_H
#define NINJA_H

#include <SFML/Graphics.hpp>
#include "tinyxml2.h"
#include "TextureHolder.h"
#include "Map.h"
#include "Box2D/Box2D.h";
#include <iostream>
#include <vector>
#include <map>
#include "AnimatedSprite.h"
#include "Animation.h"

using namespace tinyxml2;
using namespace std;
using namespace sf;

class Ninja
{
    public:
        Ninja();

        void activarSigilo();
        void desactivarSigilo();
        void descargarSigilo(float);
        void cargarSigilo(float);
        virtual ~Ninja();

    protected:
         bool saltando = false;
        float impulsoSalto = 500.f;
        float velocity = .5f;
        bool enSigilo = false; //Booleano para saber si esta en sigilo
        bool sigiloMax = true; //Booleano para saber si tiene el sigilo cargado al maximo
        float duracionSigilo = 5; //Duracion del sigilo
        float maxSigilo = 100; //Duracion maxima del sigilo (se usa en los sliders tambien)
        float recargaSigilo = 10; //Tiempo para recargar el sigilo
        sf::Clock tiempoSigilo; //Reloj para ver la duracion del sigilo
        sf::Clock cdSalto;
        sf::RectangleShape sliderSigilo[2];
        //sf::Texture texture;
        sf::Sprite sprite;

        Texture texture;
        Texture texture2;

        b2Body *ninjaBody;
        Animation walkingAnimationRight;
        Animation walkingAnimationLeft;
        Animation* currentAnimation;
        AnimatedSprite animatedSprite;
        bool noKeyWasPressed;
        b2PolygonShape shape;
        b2FixtureDef fixtureDef;

    private:
};

#endif // NINJA_H