#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>
#include <iostream>

#include <SFML/Graphics.hpp>

class Menu {
public:
	Menu(const sf::Font& font, const std::vector<std::string>& items, unsigned int characterSize = 20);

	void setPosition(float x, float y);
	void draw(sf::RenderWindow& gameWindow);

private:
	std::vector<sf::Text> menuItems;
};

#endif // MENU_H