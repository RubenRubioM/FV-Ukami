#include "TextureHolder.h"

TextureHolder::TextureHolder()
{

}

TextureHolder::~TextureHolder()
{
    //dtor
}


Sprite TextureHolder::setTexture(string path, int row, int col, int tileWidth, int tileHeight)
{
    // Se le asignamos a un sprite y enviamos el sprite
    Sprite sprite;
    sprite.setTexture(this->getTexture(path));
    sprite.setTextureRect(IntRect(row, col, tileWidth, tileHeight));

    return sprite;
}


void TextureHolder::loadTexture(XMLElement* mapa)
{
    // Aqui iremos iterando sobre cada tileset para conseguir el source de la imagen.
    XMLElement *tileset = mapa->FirstChildElement("tileset");
    while(tileset){
        Texture texture;
        texture.loadFromFile(string("tileset/") + tileset->FirstChildElement("image")->Attribute("source"));

        // Aqui asignamos al map de texturas, donde guardaremos una key con el nombre de la textura y la textura en si.
        textures[tileset->FirstChildElement("image")->Attribute("source")] = texture;
        tileset = tileset->NextSiblingElement("tileset");
    }
}

Texture& TextureHolder::getTexture(const string& textureName)
{
    // Aqui devolvemos una referencia a la memoria donde se encuentra la textura.
    return textures.at(textureName);
}
