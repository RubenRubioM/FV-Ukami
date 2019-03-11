#include <SFML/Graphics.hpp>
#include <iostream>

#include "kanji.h"

using namespace sf;

int main()
{

    kanji* puzzle;
    puzzle = new kanji(1080, 720, 0, "Puzzle Kanji");

    return EXIT_SUCCESS;
}
