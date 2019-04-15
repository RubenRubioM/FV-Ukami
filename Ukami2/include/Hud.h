<<<<<<< HEAD:Ukami2/include/Hud.h
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

        void drawSigilo(sf::RenderWindow &window, sf::RectangleShape*);
        void drawFPS(sf::RenderWindow &window);
        void drawHUD(sf::RenderWindow &window);
        void updateFPS(int);
        virtual ~Hud();


    private:
        Hud();
        static Hud *unicaInstancia;

        sf::View* vistaHUD;
        sf::Font* aldhesFont;
        sf::Text* fpsText;

        //HUD
        sf::Texture* hudTextureNinja1;
        sf::Sprite* hudSpriteNinja1;
        sf::Texture* hudTextureNinja2;
        sf::Sprite* hudSpriteNinja2;
        sf::Sprite* spritesSigilo[2];
};

#endif // HUD_H
=======
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

        void drawSigilo(sf::RenderWindow &window, sf::RectangleShape*);
        void drawFPS(sf::RenderWindow &window);
        void drawHUD(sf::RenderWindow &window);
        void updateFPS(int);
        virtual ~Hud();


    private:
        Hud();
        static Hud *unicaInstancia;

        sf::View* vistaHUD;
        sf::Font* aldhesFont;
        sf::Text* fpsText;

        //HUD
        sf::Texture* hudTextureNinja1;
        sf::Sprite* hudSpriteNinja1;
        sf::Texture* hudTextureNinja2;
        sf::Sprite* hudSpriteNinja2;
        sf::Sprite* spritesSigilo[2];
};

#endif // HUD_H
>>>>>>> 57f57d12db4eb9365f2d2aa12be8212bd48b0e7c:Ukami/include/Hud.h
