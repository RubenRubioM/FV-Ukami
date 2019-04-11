#ifndef HUD_H
#define HUD_H

#include <SFML/Graphics.hpp>

class Hud
{
    public:
        static Hud* getInstance(){
            if(unicaInstancia==0){
                unicaInstancia = new Hud();
            }
            return unicaInstancia;
        }


        void drawHUD(sf::RenderWindow &window);
        void drawSigilo(sf::RenderWindow &window, sf::RectangleShape*);
        virtual ~Hud();


    private:
        Hud();
        static Hud *unicaInstancia;

        sf::View* vistaHUD;

        sf::Sprite* spritesSigilo[2];
};

#endif // HUD_H
