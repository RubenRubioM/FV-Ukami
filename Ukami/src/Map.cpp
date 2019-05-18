#include "Map.h"

#define F 30.0f

Map::Map()
{
    // Creamos la gravedad y se la asignamos al objeto world;
    b2Vec2 gravity(0.f, 9.8f);
    world = new b2World(gravity);
}

Map::~Map()
{
    //dtor
}

void Map::initMap(string mapName)
{
    // Primero nos cargamos cualquier mapa, en caso de que exista
    eraseMap();
    // Creamos un documento XML
    XMLDocument doc;
    mapName = string("tileset/") + mapName;
    // Cargamos en este documento el documento XML del que tenemos que leer los datos.
    doc.LoadFile(mapName.c_str());
    // Tama�o del mapa y de los tiles

    //doc.PrintError();

    // Recogemos el primer elemento del xml, el mapa.
    mapa = doc.FirstChildElement("map");

    // Cargamos las colisiones
    loadCollision();

    int width, height, tileWidth, tileHeight, numLayers = 0;
    // Recogemos los datos del mapa
    mapa->QueryAttribute("width", &width);
    mapa->QueryAttribute("height", &height);
    mapa->QueryAttribute("tilewidth", &tileWidth);
    mapa->QueryAttribute("tileheight", &tileHeight);

    // Con esto obtenemos un puntero apuntando al primer layer;
    XMLElement *layer = mapa->FirstChildElement("layer");
    while (layer)
    {
        numLayers++;
        layer = layer->NextSiblingElement("layer");
    }

    // Tiene una direcci�n de memoria de un gid.
    // Guardamos aqui el gid para el layer correspondiente.
    XMLElement *capa = mapa->FirstChildElement("layer");
    XMLElement *tile;

    multimap<int, vector<int>>::iterator itGid;
    int i = 0;
    for (int l = 0; l < numLayers; l++)
    {
        // Empezamos por el primer tile
        tile = capa->FirstChildElement("data")->FirstChildElement("tile");
        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                // Comprobamos si el tile en cuestion tiene gid para meterlo en nuestro vector de gid's
                if (tile->Attribute("gid"))
                {
                    // Insertamos el gid dentro de nuestro vector
                    mapTile.insert(pair<int, vector<int>>(i, {x, y, atoi(tile->Attribute("gid"))}));
                    i++;
                }
                // Pasamos al siguiente tile
                if (tile->NextSiblingElement("tile"))
                    tile = tile->NextSiblingElement("tile");
            }
        }
        // Pasamos al siguiente layer.
        capa = capa->NextSiblingElement("layer");
    }

    // =================================================================

    // Este vector sirve para recoger los datos devueltos por la funcion findTileset.
    vector<const char *> tileInfo;

    //Cargamos todas las texturas del mapa
    t.loadTexture(mapa);

    int x = 0, y = 0;

    for (itGid = mapTile.begin(); itGid != mapTile.end(); itGid++)
    {
        int row = 0, col = 0, contgid = 0, cont = 0;
        tileInfo = findTileset(itGid->second.at(2));

        /*
         ===== Esto es la informacion que nos aportar�a el vector tileInfo =====
                    tileInfo.at(0); ----> Firstgid del tileset
                    tileInfo.at(1); ----> Source de la imagen
                    tileInfo.at(2); ----> Width de la imagen
                    tileInfo.at(3); ----> Height de la imagen
                    tileInfo.at(4); ----> Width del tile
                    tileInfo.at(5); ----> Height del tile
                    tileInfo.at(6); ----> Atributo "columns" del tileset en cuesti�n.
        */
        int gid = (itGid->second.at(2)) - atoi(tileInfo.at(0));

        // Iremos comprobando con la anchura y la altura del tileset

        while ((contgid < gid))
        {
            // Vamos aumentando al siguiente tile en la fila
            row += atoi(tileInfo.at(4));
            /*
            Contador para no pasarnos del numero de gid. Ej: Si tenemos un tile
            con gid 18, el contador empezar� desde 0 hasta 17
            */
            cont++;

            // Si tiene la misma anchura que el tileset, reseteamos
            if (cont > atoi(tileInfo.at(6)) - 1)
            {
                row = 0;
                col += atoi(tileInfo.at(5));
                // Reseteamos el contador
                cont = 0;
            }
            contgid++;
        }

        string path = tileInfo.at(1);
        tileSprite.push_back(t.setTexture(path, row, col, atoi(tileInfo.at(4)), atoi(tileInfo.at(5))));
        // Intentamos que el bug de bordes se vea menos, ponemos 32-1 para reducir la visibilidad del bug de momento.
        tileSprite.back().setPosition((itGid->second.at(0)) * (atoi(tileInfo.at(4))), (itGid->second.at(1)) * (atoi(tileInfo.at(5))));
    }
}

void Map::drawMap(RenderWindow &window)
{
    // Dibujamos los sprites
    vector<Sprite>::iterator it;

    if (transicionando == false)
    {
        for (int i = 0; i < tileSprite.size(); i++)
        {
            window.draw(tileSprite.at(i));
        }
    }
    else
    {
        if (frameTransicion < tileSprite.size() && relojTransicion.getElapsedTime().asSeconds() > 0.00001)
        {
            for (int i = 0; i < frameTransicion; i++)
            {
                window.draw(tileSprite.at(i));
            }
            frameTransicion += 100;
            relojTransicion.restart();
        }
        else if (frameTransicion >= tileSprite.size())
        {
            transicionando = false;
        }
    }

    // Fisicas
    world->Step(1.0f / 30.0f, 6, 2);
}

void Map::eraseMap()
{
    // Limpiamos tanto el vector de Sprites como todos los tile guardados para cargar el siguiente posible mapa.
    tileSprite.clear();
    mapTile.clear();
}

void Map::loadCollision()
{
    XMLElement *objectgroup = mapa->FirstChildElement("objectgroup");
    XMLElement *object = objectgroup->FirstChildElement("object");
    // Key
    const char *name;
    // Valores del vector de floats
    float x, y, width, height;

    while (objectgroup)
    {
        name = objectgroup->Attribute("name");
        // Hay que hacerlo para cada object del objectgroup
        while (object)
        {
            object->QueryAttribute("x", &x);
            object->QueryAttribute("y", &y);
            object->QueryAttribute("width", &width);
            object->QueryAttribute("height", &height);

            // Llamamos a la funcion para crear primero los platform collisions
            createCollision(x, y, width, height);

            // Pasamos al siguiente objeto
            object = object->NextSiblingElement("object");
        }
        objectgroup = objectgroup->NextSiblingElement("objectgroup");
    }
}

// Funci�n para encontrar a que Tileset pertenece el gid pasado por par�metro.
vector<const char *> Map::findTileset(int gid)
{
    // Variable de tileset que iremos iterando hasta encontrar la de mayor firstgid que aun siga siendo menor o igual que el gid del tile
    XMLElement *tileset = mapa->FirstChildElement("tileset");
    // Variable de retorno para el source de la imagen
    vector<const char *> tilesetInfo;
    // Recogemos el primer firstgid
    const char *firstgidComprobation;
    const char *firstgid;
    const char *tilesetColumns;
    const char *filename;
    const char *imageWidth;
    const char *imageHeight;
    const char *tileWidth;
    const char *tileHeight;
    firstgidComprobation = tileset->Attribute("firstgid");

    while (atoi(firstgidComprobation) <= gid)
    {
        // Si existe otro, guardamos los datos anteriores
        filename = tileset->FirstChildElement("image")->Attribute("source");
        imageWidth = tileset->FirstChildElement("image")->Attribute("width");
        imageHeight = tileset->FirstChildElement("image")->Attribute("height");
        tileWidth = tileset->Attribute("tilewidth");
        tileHeight = tileset->Attribute("tileheight");
        firstgid = tileset->Attribute("firstgid");
        tilesetColumns = tileset->Attribute("columns");
        // Comprobamos si existe siguiente tileset
        if (tileset->NextSiblingElement("tileset"))
        {
            // Pasamos al siguiente tileset
            tileset = tileset->NextSiblingElement("tileset");
            firstgidComprobation = tileset->Attribute("firstgid");
        }
        else
            break;
    }
    // Una vez hecho lo anterior, lo metemos todo en un vector
    tilesetInfo.push_back(firstgid);
    tilesetInfo.push_back(filename);
    tilesetInfo.push_back(imageWidth);
    tilesetInfo.push_back(imageHeight);
    tilesetInfo.push_back(tileWidth);
    tilesetInfo.push_back(tileHeight);
    tilesetInfo.push_back(tilesetColumns);

    return tilesetInfo;
}

void Map::createCollision(float x, float y, float width, float height)
{
    b2BodyDef bodyDef;
    bodyDef.position.Set((x + (width / 2.f)) / F, (y + (height / 2.f)) / F);
    bodyDef.type = b2_staticBody;
    b2Body *body = world->CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox((width / 2.f) / F, (height / 2.f) / F);
    b2FixtureDef fixtureDef;
    fixtureDef.density = 0.f;
    fixtureDef.shape = &shape;
    body->CreateFixture(&fixtureDef);

    cout << x << "  " << y << "  " << width << "  " << height << endl;
}

b2World *Map::getb2World()
{
    return world;
}

void Map::empezarTransicion()
{
    transicionando = true;
    frameTransicion = 0;
}
bool Map::getTransicionando() { return transicionando; }

void Map::setTransicionando(bool _transicionando)
{
    transicionando = _transicionando;
}
