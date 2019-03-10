#ifndef NINJA_H
#define NINJA_H

#include "SFML/Graphics.hpp"
#include <iostream>
using namespace std;
class Ninja
{
    public:
        Ninja();
        virtual ~Ninja();


        //Getters
        int getDireccion();
        bool getMoviendose();
        float getVelocidad();
        bool getEnSigilo();
        bool getSigiloMax();
        float getDuracionSigilo();
        sf::Sprite *getSprite();
        sf::Clock getTiempoSigilo();
        sf::RectangleShape *getSliderSigilo();

        //Setters
        void setDireccion(int);
        void setMoviendose(bool);
        void setEnSigilo(bool);

        //Metodos
        void activarSigilo();
        void desactivarSigilo();
        void descargarSigilo(float);
        void cargarSigilo(float);
        void moverse(float); //Movemos al personaje mediante deltatime


    protected:

        //Varialbes
        int direccion = 1; //1-> derecha / -1-> izquierda
        bool moviendose = false; //Dice si se esta moviendo o no
        bool enSigilo = false; //Booleano para saber si esta en sigilo
        bool sigiloMax = true; //Booleano para saber si tiene el sigilo cargado al maximo
        float duracionSigilo = 5; //Duracion del sigilo
        float maxSigilo = 100; //Duracion maxima del sigilo (se usa en los sliders tambien)
        float recargaSigilo = 10; //Tiempo para recargar el sigilo
        float velocidad; //Velocidad del personaje
        sf::Clock tiempoSigilo; //Reloj para ver la duracion del sigilo
        sf::Texture *texture; //Textura del personaje
        sf::Sprite *sprite; //Sprite del personaje
        sf::RectangleShape sliderSigilo[2];


        //Metodos


};

#endif // NINJA_H
