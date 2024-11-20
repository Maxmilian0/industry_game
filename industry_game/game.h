#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <random>
#include <fstream>

class Game {
public:
    Game();

    void draw(sf::RenderWindow& _GameWindow);
    void update();
    int handleEvent(const sf::Event& _Event, sf::RenderWindow& _GameWindow);

private:
    std::vector<sf::ConvexShape> mapItems;  // Seznam dla�dic
    sf::Texture tileSet;                   // Textura, kter� bude pou�it� na dla�dice
    std::fstream logFile;                  // Soubor pro zapisov�n� chybov�ch hl�ek
};

#endif // GAME_H
