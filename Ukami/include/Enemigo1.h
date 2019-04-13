#ifndef ENEMIGO1_H
#define ENEMIGO1_H

#include "Enemigo.h"


class Enemigo1 : public Enemigo
{
    public:
        Enemigo1(float posx, float posy, b2World* world);
        virtual ~Enemigo1();

        //Metodos
        void setDireccion(int);
        void moverse(float); //Funcion para moverse
        void drawEnemigo(RenderWindow &window);
        void ia(float);

    private:


        int metros;
        int distanciaMaxima = 120;
};

#endif // ENEMIGO1_H
