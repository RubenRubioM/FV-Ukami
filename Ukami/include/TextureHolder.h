#ifndef TEXTUREHOLDER_H
#define TEXTUREHOLDER_H
#include <SFML/Graphics.hpp>
#include "tinyxml2.h"
#include <iostream>
#include <vector>

using namespace tinyxml2;
using namespace std;
using namespace sf;

class TextureHolder
{
    map<string, Texture> textures;

public:
    TextureHolder();
    virtual ~TextureHolder();
    void loadTexture(XMLElement *mapa);
    Texture &getTexture(const string &textureName);
    Sprite setTexture(string path, int row, int col, int tileWidth, int tileHeight);
};

#endif // TEXTUREHOLDER_H
