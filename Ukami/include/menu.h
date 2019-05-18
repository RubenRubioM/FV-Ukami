#ifndef MENU_H
#define MENU_H

#include "Game.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <cstring>
#include <AudioManager.h>

using namespace std;

class menu
{
    public:
        static menu* getInstance(sf::RenderWindow &window, sf::Event &eventGame);

        int drawMenu();
        int getNivel();
        void continuar();

    protected:

    private:


        menu(sf::RenderWindow &window, sf::Event &eventGame);
        static menu* menuUnico;


        bool continuar_bool;
        sf::RenderWindow* ventanaMenu;
        sf::Font* fuente;
        sf::Text* mensaje;
        sf::Text* menuInicial [4];
        sf::Text* menuSelectNivel [2];
        sf::Text* menuNiveles [3];
        sf::Text* menuEstad [4];
        sf::Text* menuMejoras [4];
        sf::Texture* texturaFondo;
        sf::Sprite* fondo;
        sf::Event* evento;
        sf::View* vistaMenu;
        sf::Clock tiempoEntreTeclas;
        int mostrarMenu;
        int separacion;
        int actual;
        int presionado;
        int idMenu;
        int cont;
        int nivel = 1;
        string textoMenuInicial [4];
        string textoMenuSelectNivel [2];
        string textoMenuNiveles [3];
        string textoMenuEstad [3];
        string textoMenuMejoras [4];
        string mensajesConsolaMI [4];
        string mensajesConsolaSelectNiv [2];
        string mensajesConsolaNivel [4];
        string mensajesConsolaEstad [4];
        string mensajesConsolaMej [5];
        string muertes;
        string kanjis;
        string tiempo;
        string nivel1;
        string nivel2;
        string nivel3;



        virtual ~menu();
        void cargarFondo();
        void cargarFuente();
        void cargarMensaje();
        void rellenarArrayMensajesConsolaMI(int indice);
        void rellenarArrayMensajesConsolaSelectNivel(int indice);
        void rellenarArrayMensajesConsolaNivel(int indice);
        void rellenarArrayMensajesConsolaEstad(int indice);
        void rellenarArrayMensajesConsolaMejoras(int indice);
        void cargarMensajesConsola();
        void escribirPorConsola();
        void rellenarArrayTextoMenu(int indice);
        void copiarTextArray(sf::Text* origen [4], sf::Text* destino [4]);
        void vaciarTextArray(sf::Text* textArray [4]);
        void cargarTextoMenu();
        void cargarMenu();
        void hoverMenu(sf::Text* menuAPintar [4]);

        void renderMenu(int queMenu);

        void actualizarMonedas();
        int actualizarMenu();
};

#endif // MENU_H
