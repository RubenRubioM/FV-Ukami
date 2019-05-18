#ifndef MAP_H
#define MAP_H
#include <SFML/Graphics.hpp>
#include "tinyxml2.h"
#include "TextureHolder.h"
#include "Box2D/Box2D.h";
#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace tinyxml2;
using namespace std;
using namespace sf;

class Map
{
public:
    Map();
    virtual ~Map();
    // Inicializar el mapa
    void initMap(string mapName);
    // Dibujar el mapa
    void drawMap(RenderWindow &window);
    // Borrar el mapa
    void eraseMap();
    // Cargar colisiones del mapa
    void loadCollision();
    void createCollision(float x, float y, float width, float height);
    // Guardar los datos de cierto tileset
    vector<const char *> findTileset(int gid);
    b2World *getb2World();

    void setTransicionando(bool);
    bool getTransicionando();
    void empezarTransicion();

protected:
private:
    // Aqui guardaremos cada tile, con sus respectivas coordenadas.(Lo cambiare mas tarde por solo guardar Sprite/X y Y de cada sprite en un multimap)
    multimap<int, vector<int>> mapTile;
    // Vector en el que guardaremos los Sprites
    vector<Sprite> tileSprite;
    // Aqui guardaremos el source de las imagenes usadas en Tiled
    TextureHolder t;
    // XMLElement de nuestro mapa
    XMLElement *mapa;
    // Nuestro mundo 2D
    b2World *world;

    int frameTransicion = 0;
    bool transicionando = false;
    sf::Clock relojTransicion;
};

#endif // MAP_H
