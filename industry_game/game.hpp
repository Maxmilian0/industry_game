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
    void update(sf::RenderWindow& _GameWindow);
    int handleEvent(const sf::Event& _Event, sf::RenderWindow& _GameWindow);

private:
    std::vector<sf::ConvexShape> mapItems;  // Seznam dlaždic
    sf::Texture tileSet;                   // Textura, která bude použitá na dlaždice
    std::fstream logFile;                  // Soubor pro zapisování chybových hlášek
    sf::View camera;
    sf::Clock deltaClock;  // Hodiny pro měření delta time
    int cameraMoreSpeed = 0;
    sf::Vector2f movedCameraQuestion = sf::Vector2f(0, 0);
};

#endif // GAME_H
