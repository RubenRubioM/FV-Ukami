#ifndef CAMARA_H
#define CAMARA_H

#include "SFML/Graphics.hpp"

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
