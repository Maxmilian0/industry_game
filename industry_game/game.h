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
	void handleEvent(const sf::Event& _Event, sf::RenderWindow& _GameWindow);
private:
	std::vector<sf::VertexArray> mapItems;
	std::fstream logFile;
};
#endif // GAME_H