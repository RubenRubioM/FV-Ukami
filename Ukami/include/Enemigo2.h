#ifndef ENEMIGO2_H
#define ENEMIGO2_H

#include <Enemigo.h>


class Enemigo2 : public Enemigo
{
    public:
        static Enemigo2 *getInstance(){
            if(unicaInstancia==0){
                unicaInstancia = new Enemigo2();
            }
            return unicaInstancia;
        }



        virtual ~Enemigo2();


        //Metodos
        void setDireccion(int);
        void moverse(float); //Funcion para moverse

    private:
        Enemigo2();
        static Enemigo2 *unicaInstancia;





    protected:



};

#endif // Enemigo2_H
