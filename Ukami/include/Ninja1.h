#ifndef NINJA1_H
#define NINJA1_H

#include <Ninja.h>
#include <Guardia.h>


class Ninja1 : public Ninja
{
    public:
        static Ninja1 *getInstance(){
            if(unicaInstancia==0){
                unicaInstancia = new Ninja1();
            }
            return unicaInstancia;
        }




        //Metodos

        virtual ~Ninja1();


    private:
        Ninja1();
        static Ninja1 *unicaInstancia;


    protected:



};

#endif // NINJA1_H
