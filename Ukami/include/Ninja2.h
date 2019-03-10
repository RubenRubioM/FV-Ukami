#ifndef NINJA2_H
#define NINJA2_H

#include <Ninja.h>


class Ninja2 : public Ninja
{
    public:
        static Ninja2 *getInstance(){
            if(unicaInstancia==0){
                unicaInstancia = new Ninja2();
            }
            return unicaInstancia;
        }
        virtual ~Ninja2();



    private:
        Ninja2();
        static Ninja2 *unicaInstancia;

    protected:
};

#endif // NINJA2_H
