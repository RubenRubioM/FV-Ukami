#include "Hud.h"

Hud *Hud::unicaInstancia = 0;

Hud::Hud()
{
    vistaHUD = new sf::View();
    vistaHUD->setSize(1280,720);
    vistaHUD->setCenter(vistaHUD->getSize().x / 2, vistaHUD->getSize().y / 2);

    // ==== Sprites del sigilo ====

    // Ninja1
    sf::Texture* texturaBack = new sf::Texture();
    texturaBack->loadFromFile("tileset/kunai_back.png");
    sf::Sprite* spriteBack = new sf::Sprite(*texturaBack);
    spriteBack->setOrigin(texturaBack->getSize().x/2.f,texturaBack->getSize().y/2);
    spriteBack->setScale(0.1,0.1);
    spriteBack->setPosition(100,103);
    spritesSigilo[0] = spriteBack;

    sf::Texture* texturaFront = new sf::Texture();
    texturaFront->loadFromFile("tileset/kunai_front.png");
    sf::Sprite* spriteFront = new sf::Sprite(*texturaFront);
    spriteFront->setOrigin(texturaFront->getSize().x/2.f,texturaFront->getSize().y/2);
    spriteFront->setScale(0.1,0.1);
    spriteFront->setPosition(238,102);
    spritesSigilo[1] = spriteFront;

    //Ninja2
    sf::Sprite* spriteBack2 = new sf::Sprite(*texturaBack);
    spriteBack2->setOrigin(texturaBack->getSize().x/2.f,texturaBack->getSize().y/2);
    spriteBack2->setScale(0.1,0.1);
    spriteBack2->setPosition(695,103);
    spritesSigilo2[0] = spriteBack2;

    sf::Sprite* spriteFront2 = new sf::Sprite(*texturaFront);
    spriteFront2->setOrigin(texturaFront->getSize().x/2.f,texturaFront->getSize().y/2);
    spriteFront2->setScale(0.1,0.1);
    spriteFront2->setPosition(833,102);
    spritesSigilo2[1] = spriteFront2;

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

    // ==== HUD ninjas ====
    hudTextureNinja2 = new sf::Texture();
    hudTextureNinja2->loadFromFile("tileset/health_ninja2.png");
    hudSpriteNinja2 = new sf::Sprite(*hudTextureNinja2);
    hudSpriteNinja2->setOrigin(hudTextureNinja2->getSize().x/2.f,hudTextureNinja2->getSize().y/2);
    hudSpriteNinja2->setPosition(800,65);

    // ==== VIDA HUD ====
    sf::Texture* textureVidaHud = new sf::Texture();
    textureVidaHud->loadFromFile("tileset/hud_damage.png");
    spriteVidaHud = new sf::Sprite(*textureVidaHud);
    spriteVidaHud->setPosition(0,0);
    spriteVidaHud->setScale(0.67,0.67);


}

void Hud::updateFPS(int _fps){
    string fps = to_string(_fps);

    fpsText->setString(fps);

}

void Hud::drawSigilo(sf::RenderWindow &window, sf::RectangleShape* sliderSigilo1, sf::RectangleShape* sliderSigilo2){
    window.setView(*vistaHUD);
    // ==== Ninja 1 ====
    window.draw(sliderSigilo1[0]);
    window.draw(sliderSigilo1[1]);
    window.draw(*spritesSigilo[0]);
    window.draw(*spritesSigilo[1]);

    // ==== Ninja 2 ====
    window.draw(sliderSigilo2[0]);
    window.draw(sliderSigilo2[1]);
    window.draw(*spritesSigilo2[0]);
    window.draw(*spritesSigilo2[1]);
}

void Hud::drawVida(sf::RenderWindow &window, sf::RectangleShape* vida1, sf::RectangleShape* vida2, float vidaValor1, float vidaValor2){
    window.setView(*vistaHUD);
    window.draw(*vida1);
    window.draw(*vida2);

    float vidaMinima;
    if(vidaValor1>0 && vidaValor2>0){
        if(vidaValor1<vidaValor2){
        vidaMinima = vidaValor1;
        }else{
            vidaMinima = vidaValor2;
        }
    }else{
        vidaMinima=1;
    }


    float trasparencia = (1-((1.0/317.0) *vidaMinima));
    cout << trasparencia << endl;
    spriteVidaHud->setColor(sf::Color(255,255,255,255*trasparencia));
    window.draw(*spriteVidaHud);
}

void Hud::drawHUD(sf::RenderWindow &window){
    window.setView(*vistaHUD);
    window.draw(*hudSpriteNinja1);
    window.draw(*hudSpriteNinja2);
}

void Hud::drawFPS(sf::RenderWindow &window){
    window.draw(*fpsText);
}

Hud::~Hud()
{
    //dtor
}
