#include <iostream>
#include <string>
#include <array>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include "main_menu.h"

int main() {
	sf::RenderWindow gameWindow(sf::VideoMode::getDesktopMode(), "The Game Of Industry", sf::Style::Fullscreen);

	sf::Image cursorImage;
	if (!cursorImage.loadFromFile("cursor.png")) {
		std::cerr << "Cursor image didn't load!";
		return -1;
	}

	sf::Cursor gunCursor;
	if (gunCursor.loadFromPixels(cursorImage.getPixelsPtr(), cursorImage.getSize(), sf::Vector2u(16, 16))) {
		gameWindow.setMouseCursor(gunCursor);
	}

	sf::Font geistMonoExtraBold;
	sf::Font geistMonoMedium;

	if (!geistMonoExtraBold.loadFromFile("fonts/GeistMono-ExtraBold.ttf")) {
		std::cerr << "Error while loading GeistMono-ExtraBold.ttf!";
		return -1;
	}
	if (!geistMonoMedium.loadFromFile("fonts/GeistMono-Medium.ttf")) {
		std::cerr << "Error while loading GeistMono-Medium.tff!";
		return -1;
	}

	std::vector<std::string> menuItems = { "Play", "Settings", "Exit"};
	Menu menu(geistMonoMedium, menuItems);

	while (gameWindow.isOpen()) {
		sf::Event event;
		while (gameWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				gameWindow.close();
			}
		}

		gameWindow.clear(sf::Color(246, 246, 246));

		menu.draw(gameWindow);

		gameWindow.display();
	}


	return 0;
}