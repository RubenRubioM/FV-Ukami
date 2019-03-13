#ifndef ENEMIGO1_H
#define ENEMIGO1_H

#include <Enemigo.h>


class Enemigo1 : public Enemigo
{
    public:
        static Enemigo1 *getInstance(){
            if(unicaInstancia==0){
                unicaInstancia = new Enemigo1();
            }
            return unicaInstancia;
        }



        virtual ~Enemigo1();


    private:
        Enemigo1();
        static Enemigo1 *unicaInstancia;


        //Metodos
        void moverse(float); //Funcion para moverse
        void detectado(bool); //Funcion para detectar ninjas



    protected:



};

#endif // Enemigo1_H
