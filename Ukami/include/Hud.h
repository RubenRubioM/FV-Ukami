#ifndef HUD_H
#define HUD_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;
class Hud
{
    public:
        static Hud* getInstance(){
            if(unicaInstancia==0){
                unicaInstancia = new Hud();
            }
            return unicaInstancia;
        }

        void drawSigilo(sf::RenderWindow &window, sf::RectangleShape*, sf::RectangleShape*);
        void drawFPS(sf::RenderWindow &window);
        void drawHUD(sf::RenderWindow &window);
        void updateFPS(int);
        void drawVida(sf::RenderWindow &window, sf::RectangleShape*, sf::RectangleShape*, float, float);
        sf::Text getTextGameOver();
        sf::Text getTextGanado();
        virtual ~Hud();


    private:
        Hud();
        static Hud *unicaInstancia;

        sf::View* vistaHUD;
        sf::Font* aldhesFont;
        sf::Text* fpsText;
        sf::Text gameOver;
        sf::Text victory;

        //HUD
        sf::Texture* hudTextureNinja1;
        sf::Sprite* hudSpriteNinja1;
        sf::Texture* hudTextureNinja2;
        sf::Sprite* hudSpriteNinja2;
        sf::Sprite* spritesSigilo[2];
        sf::Sprite* spritesSigilo2[2];
        sf::Sprite* spriteVidaHud;
};

#endif // HUD_H
