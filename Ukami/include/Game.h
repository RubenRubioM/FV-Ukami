
#ifndef GAME_H
#define GAME_H

#include "SFML/Graphics.hpp"

using namespace std;


class Game
{
    public:
        Game(int x,int y, std::string title);
        void draw();
        void gameLoop();
        void eventsLoop();

        virtual ~Game();

    protected:

    private:

        sf::RenderWindow *window;
        sf::Event *event;
};

#endif // GAME_H
