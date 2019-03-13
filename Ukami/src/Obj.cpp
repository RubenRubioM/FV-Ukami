#include "Obj.h"

Obj::Obj()
{
    //ctor
    texture = new sf::Texture();

    texture->loadFromFile("Assets/Adventurer/sprites.png",sf::IntRect(0*75, 2*75, 75, 75));
    sprite = new sf::Sprite(*texture);
    sprite->setOrigin(sprite->getTexture()->getSize().x/2.f,sprite->getTexture()->getSize().y/2.f);
    sprite->setPosition(500,100); //We set origin to 16,16 so now we have to spawn him at 16,16 instead of 0,0

}


//Getters
sf::Sprite* Obj::getSprite(){return sprite;}

Obj::~Obj()
{
    //dtor
}
