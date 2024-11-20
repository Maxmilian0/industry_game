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
    std::vector<sf::ConvexShape> mapItems;  // Seznam dlaždic
    sf::Texture tileSet;                   // Textura, která bude použitá na dlaždice
    std::fstream logFile;                  // Soubor pro zapisování chybových hlášek
};

#endif // GAME_H
