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

    // ==== FPS ====
    aldhesFont = new sf::Font();
    aldhesFont->loadFromFile("tileset/Aldhes.ttf");
    fpsText = new sf::Text();
    fpsText->setFont(*aldhesFont);
    fpsText->setCharacterSize(40);
    fpsText->setPosition(1200,20);
    fpsText->setColor(sf::Color::Red);

}

void Hud::updateFPS(int _fps){
    string fps = to_string(_fps);

    fpsText->setString(fps);

}

void Hud::drawSigilo(sf::RenderWindow &window, sf::RectangleShape* sliderSigilo){
    window.setView(*vistaHUD);
    // ==== Ninja 2 ====
    window.draw(sliderSigilo[0]);
    window.draw(sliderSigilo[1]);
    window.draw(*spritesSigilo[0]);
    window.draw(*spritesSigilo[1]);
}

void Hud::drawFPS(sf::RenderWindow &window){
    window.draw(*fpsText);
}

Hud::~Hud()
{
    //dtor
}
