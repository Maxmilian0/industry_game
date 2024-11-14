#ifndef MENU_H
#define MENU_H

#include <vector>
#include <string>
#include <iostream>

#include <SFML/Graphics.hpp>

class Menu {
public:
	Menu(const sf::Font& font, const std::vector<std::string>& items, std::string menuTitle, sf::RenderWindow& gameWindow);

	void setPosition(float x, float y);
	void draw(sf::RenderWindow& gameWindow);
	void handleEvent(const sf::Event& event, sf::RenderWindow& gameWindow);

private:
	std::vector<sf::Text> menuItems;
	sf::Text menuTitleTextGlobal;
};

#endif // MENU_H