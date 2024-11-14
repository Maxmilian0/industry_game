#include <iostream>
#include <string>
#include <array>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

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

	sf::Vector2u basicResolution(1920, 1080);
	unsigned int basicTextSize = 100;

	sf::Vector2u currentResolution = gameWindow.getSize();

	float textSizeRatio = static_cast<float>(currentResolution.y) / basicResolution.y;

	sf::Text menuMainHeading;
	menuMainHeading.setFont(geistMonoExtraBold);
	menuMainHeading.setString("The Game Of Industry");
	menuMainHeading.setCharacterSize(40);
	menuMainHeading.setFillColor(sf::Color::Black);
	menuMainHeading.setPosition(100, 100);

	sf::Text menu[3];
	std::string menuItems[] = {"Play", "Settings", "Exit"};

	for (int i = 0; i < std::size(menuItems); i++) {
		menu[i].setFont(geistMonoMedium);
		menu[i].setCharacterSize(20);
		menu[i].setFillColor(sf::Color::Color(100, 100, 100));
		menu[i].setPosition(100, 200 + i * 80);
		menu[i].setString(menuItems[i]);
	}	

	while (gameWindow.isOpen()) {
		sf::Event event;
		while (gameWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				gameWindow.close();
			}
		}

		gameWindow.clear(sf::Color(246,246,246));

		gameWindow.draw(menuMainHeading);
		for (int i = 0; i < std::size(menu); i++) {
			gameWindow.draw(menu[i]);
		}

		gameWindow.display();
	}
	

	return 0;
}