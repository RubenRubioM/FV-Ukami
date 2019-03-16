#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstring>

using namespace std;

class menu
{
    public:
        static menu* getInstance();

    protected:

    private:
        sf::RenderWindow* ventanaMenu;
        sf::Font* fuente;
        sf::Text* mensaje;
        sf::Text* menuInicial [4];
        sf::Text* menuSelectNivel [2];
        sf::Text* menuNiveles [3];
        sf::Text* menuEstad [3];
        sf::Text* menuMejoras [4];
        sf::Texture* texturaFondo;
        sf::Sprite* fondo;
        sf::Event* evento;
        int fps;
        int mostrarMenu;
        int separacion;
        int actual;
        int presionado;
        int idMenu;
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
        static menu* menuUnico;
        menu();
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
        void render();
        void renderMenu(int queMenu);
        void gameLoop();
        void actualizarMenu();
};

#endif // MENU_H
