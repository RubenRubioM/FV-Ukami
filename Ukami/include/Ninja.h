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
        sf::Texture *texture;
        sf::Sprite *sprite;

        //Getters
        int getDireccion();
        int getVisto();
        bool getMoviendose();
        float getVelocidad();
        bool getEnSigilo();
        bool getSigiloMax();
        sf::RectangleShape sliderVisto[2];
        float getDuracionSigilo();
        sf::Sprite *getSprite();
        sf::Clock getTiempoSigilo();
        sf::RectangleShape *getSliderSigilo();
        sf::RectangleShape *getSliderVisto();


        //Setters
        void setDireccion(int);
        void setMoviendose(bool);
        void restaVisto(int); //Resta variable Visto para veces que es detectado
        void setEnSigilo(bool);

        //Metodos
        virtual void moverse(float) = 0; //Metodo abstracto que definen las sublcases
        void activarSigilo();
        void desactivarSigilo();
        void descargarSigilo(float);
        void cargarSigilo(float);
        virtual void detectado(sf::FloatRect, sf::FloatRect, sf::FloatRect) = 0; //Metodo abstracto que definen las sublcases


    protected:

        //Varialbes
        int direccion = 1; //1-> derecha / -1-> izquierda
        bool moviendose =false; //Dice si se esta moviendo o no
        bool enSigilo = false; //Booleano para saber si esta en sigilo
        bool sigiloMax = true; //Booleano para saber si tiene el sigilo cargado al maximo
        float duracionSigilo = 5; //Duracion del sigilo
        float maxSigilo = 100; //Duracion maxima del sigilo (se usa en los sliders tambien)
        float recargaSigilo = 10; //Tiempo para recargar el sigilo
        float velocidad;
        int visto = 1000; //Veces que es visto, va disminuyendo
        sf::Clock tiempoSigilo; //Reloj para ver la duracion del sigilo
        sf::RectangleShape sliderSigilo[2];



        //Metodos


};

#endif // NINJA_H
