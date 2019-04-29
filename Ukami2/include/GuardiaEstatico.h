#ifndef GUARDIAESTATICO_H
#define GUARDIAESTATICO_H

#include <iostream>
#include <SFML/Graphics.hpp>

#define TIEMPO_DE_ESPERA 4

using namespace std;

class GuardiaEstatico
{
    public:
        GuardiaEstatico(float, float);
        virtual ~GuardiaEstatico();

        //Metodos
        void drawGuardiaEstatico(sf::RenderWindow &window);
        void moverse(float);
        void activarRelojDeEspera(); //Se llama cuando ha llegado al destino y tiene que esperar para volver


        //Getters
        float getVelocidad();
        float getxInicial();
        float getPosicionDestino();
        bool getMoviendose();
        bool getEsperando();
        bool getVolviendo();
        sf::Sprite *getSprite();
        sf::Clock getTiempoAntesDeVolver();
        sf::ConvexShape* getVision();

        //Setters
        void setPosicionDestino(float);
        void setEsperando(bool);
        void setVolviendo(bool);
        void setMoviendose(bool);
        void setHaRegresado(bool);

    private:
        bool moviendose = false; //Principalemnte se pone a true cuando le silbas (guardias estaticos)
        bool esperando = false; //Se pone a true cuando le silban, va al destino, y tiene que esperar
        bool volviendo = false; //Cuando esta volviendo a la posicion inicial
        bool haRegresado = false;
        float velocidad;
        float xInicial; //la posicion inicial para un guardia estatico para asi poder regresarlo despues de moverse
        float posicionDestino; //Posicion donde tiene que ir cuando le silban
        int direccionDestino; //Direccion donde le pilla el silbido 1 o -1
        sf::Texture *texture;
        sf::Sprite *sprite;
        sf::Clock tiempoAntesDeVolver; //Tiempo que pasa en el sitio hasta que vuelve al sitio donde estaba despues del silbido
        sf::ConvexShape *triangle; //Vision
};


#endif // GUARDIAESTATICO_H
