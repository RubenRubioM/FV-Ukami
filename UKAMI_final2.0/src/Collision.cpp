#include "Collision.h"

Collision::Collision()
{
    //ctor
}

Collision::~Collision()
{
    //dtor
}

void Collision::loadCollision(XMLElement* mapa)
{
    XMLElement* objectgroup = mapa->FirstChildElement("objectgroup");
    XMLElement* object = objectgroup->FirstChildElement("object");
    // Key
    const char* name;
    // Valores del vector de floats
    float x, y, width, height;

    while (objectgroup) {
        name = objectgroup->Attribute("name");
        // Hay que hacerlo para cada object del objectgroup
        while (object) {
            object->QueryAttribute("x", &x);
            object->QueryAttribute("y", &y);
            object->QueryAttribute("width", &width);
            object->QueryAttribute("height", &height);

            // Introducimos los datos dentro de nuestro multimap
            collisions.insert(pair<string, vector<float> >(name, { x, y, width, height }));
            cout << "Cargamos colision con los siguientes DATOS: " << endl;
            cout << "Name: " << name << endl;
            cout << "X: " << x << endl;
            cout << "Y: " << y << endl;
            cout << "Width: " << width << endl;
            cout << "Height: " << height << endl;

            object = object->NextSiblingElement("object");
        }
        objectgroup = objectgroup->NextSiblingElement("objectgroup");
    }

    // Ahora vamos a crear FloatRect "invisibles" con las coordenadas de antes.
    // Hay que pensar esto mejor...
}
