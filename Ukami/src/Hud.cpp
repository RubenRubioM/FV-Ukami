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
    spriteBack->setScale(0.1,0.1);
    spriteBack->setPosition(200,104);
    spritesSigilo[0] = spriteBack;

    sf::Texture* texturaFront = new sf::Texture();
    texturaFront->loadFromFile("tileset/kunai_front.png");
    sf::Sprite* spriteFront = new sf::Sprite(*texturaFront);
    spriteFront->setOrigin(texturaFront->getSize().x/2.f,texturaFront->getSize().y/2);
    spriteFront->setScale(0.1,0.1);
    spriteFront->setPosition(338,102);
    spritesSigilo[1] = spriteFront;

    // ==== FPS ====
    aldhesFont = new sf::Font();
    aldhesFont->loadFromFile("tileset/Aldhes.ttf");
    fpsText = new sf::Text();
    fpsText->setFont(*aldhesFont);
    fpsText->setCharacterSize(40);
    fpsText->setPosition(1200,20);
    fpsText->setColor(sf::Color::Red);

    // ==== HUD ninjas ====
    hudTextureNinja1 = new sf::Texture();
    hudTextureNinja1->loadFromFile("tileset/health_ninja1.png");
    hudSpriteNinja1 = new sf::Sprite(*hudTextureNinja1);
    hudSpriteNinja1->setOrigin(hudTextureNinja1->getSize().x/2.f,hudTextureNinja1->getSize().y/2);
    hudSpriteNinja1->setPosition(210,65);

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

void Hud::drawHUD(sf::RenderWindow &window){
    window.setView(*vistaHUD);
    window.draw(*hudSpriteNinja1);
}

void Hud::drawFPS(sf::RenderWindow &window){
    window.draw(*fpsText);
}

Hud::~Hud()
{
    //dtor
}
