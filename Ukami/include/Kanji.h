#ifndef KANJI_H
#define KANJI_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <ctime>

using namespace std;

class Kanji
{
    public:
        Kanji(int kanjiSelected, string title, sf::RenderWindow &window, sf::Event &eventGame); //Le pasamos la ventana ya en el constructor y la almacenamos para no pasarsela cada draw
        virtual ~Kanji();

        void drawKanji();
        bool updateKanji();

    private:
        int fps; //posibilidad de pasarlo a una clase generica puzzle
        int correctKanjiArray [4]; //array que guardara la posicion correcta del kanji (todo 0)
        int angle; //sera de 30 grados fijos
        int rotationsKanji [4]; //array que guardara las diferentes rotaciones que se le habran aplicado a cada sprite
        int n; //identidad de la circunferencia actual seleccionada (se utiliza en el evento de girar las circunferencias para controlar que circunferencia hay que girar tras pulsar las flechas arriba y abajo)
        bool win;
        string kanjiName;
        sf::Font* font1;
        sf::Text* winText;
        sf::Texture* kanjiTextures [4]; //array donde se almacenaran las texturas de las 4 circunferencias del kanji
        sf::Sprite* kanjiSprites [4]; //array donde se guardaran los sprites cargados
        sf::Texture* background; //textura del fondo de pantalla
        sf::Sprite* kanjiBack; //sprite del fondo de pantalla
        sf::Texture* finalKanji;
        sf::Sprite* correctKanji;
        sf::RenderWindow* kanjiWindow;
        sf::View* kanjiView;
        sf::CircleShape *circuloSelector;

        sf::Clock tiempoEntreTecla;

        void selectKanji(int idKanji);
        void createKanjiTextures();
        void loadKanjiTextures(int idText);
        void loadKanjiSprites();
        void loadFont();
        void loadWinMessage();
        void loadCorrectKanji();
        void kanjiSpritesPosition(sf::Sprite* kanjiSprite);
        void loadBackground();
        void renderSprites();
        void doRotationToSprites();
        void gameLoop();
        bool checkKanji();
        bool checkRep(int n, int rango, int num[]);
        void genRandRotIndices(int* rot);
};

#endif // KANJI_H
