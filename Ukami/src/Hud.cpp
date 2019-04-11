#include "Hud.h"

Hud *Hud::unicaInstancia = 0;

Hud::Hud()
{
    vistaHUD = new sf::View();
    vistaHUD->setSize(1280,720);
    vistaHUD->setCenter(vistaHUD->getSize().x / 2, vistaHUD->getSize().y / 2);

    // ==== Sprites del sigilo ====
    sf::Texture* texturaBack = new sf::Texture();
    texturaBack->loadFromFile("tileset/kunai_back.png");
    sf::Sprite* spriteBack = new sf::Sprite(*texturaBack);
    spriteBack->setOrigin(texturaBack->getSize().x/2.f,texturaBack->getSize().y/2);
    spriteBack->setScale(0.3,0.3);
    spriteBack->setPosition(50,50);
    spritesSigilo[0] = spriteBack;

    sf::Texture* texturaFront = new sf::Texture();
    texturaFront->loadFromFile("tileset/kunai_front.png");
    sf::Sprite* spriteFront = new sf::Sprite(*texturaFront);
    spriteFront->setOrigin(texturaFront->getSize().x/2.f,texturaFront->getSize().y/2);
    spriteFront->setScale(0.3,0.3);
    spriteFront->setPosition(249,47);
    spritesSigilo[1] = spriteFront;

}

void Hud::drawHUD(sf::RenderWindow &window){
    window.setView(*vistaHUD);

    window.draw(*spritesSigilo[0]);
    window.draw(*spritesSigilo[1]);
}

void Hud::drawSigilo(sf::RenderWindow &window, sf::RectangleShape* sliderSigilo){
    window.setView(*vistaHUD);
    window.draw(sliderSigilo[0]);
    window.draw(sliderSigilo[1]);
}

Hud::~Hud()
{
    //dtor
}
