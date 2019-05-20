#include "OjoJade.h"

OjoJade::OjoJade()
{
    texture.loadFromFile("tileset/ojoJade.png");
    texture.setSmooth(true);
    sprite.setTexture(texture);

    sprite.setPosition(7500, 300);
    sprite.setScale(0.8f, 0.8f);
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
}

OjoJade::~OjoJade()
{
    //dtor
}

void OjoJade::draw(sf::RenderWindow &window)
{
    window.draw(sprite);
}

void OjoJade::update(float deltatime)
{

    sprite.rotate(-0.1 * deltatime);
}

sf::Sprite OjoJade::getSprite()
{
    return sprite;
}
