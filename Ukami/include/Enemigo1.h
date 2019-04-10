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

        //Metodos
        void setDireccion(int);
        void moverse(float); //Funcion para moverse

    private:
        Enemigo1();
        static Enemigo1 *unicaInstancia;





    protected:



};

#endif // Enemigo1_H
