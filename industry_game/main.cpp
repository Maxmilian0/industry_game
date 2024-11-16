#include <iostream>
#include <string>
#include <array>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

// Private
#include "main_menu.h"
#include "media_loader.h"

int main() {
	// Settuping window, images, cursor, fonts
	sf::RenderWindow gameWindow(sf::VideoMode::getDesktopMode(), "The Game Of Industry", sf::Style::Fullscreen);
	sf::Image cursorImage;
	sf::Cursor gunCursor;
	sf::Font geistMonoExtraBold;
	sf::Font geistMonoMedium;
	std::vector<std::string> menuItems = { "Play", "Settings", "Exit" };

	Menu menu(geistMonoMedium, menuItems, "The Game Of Industry", gameWindow);

	// Loading media
	MediaLoader::loadSoundBuffer(geistMonoExtraBold, "fonts/GeistMono-ExtraBold.ttf");
	MediaLoader::loadSoundBuffer(geistMonoMedium, "fonts/GeistMono-Medium.ttf");
	MediaLoader::loadSoundBuffer(cursorImage, "cursor.png");

	gunCursor.loadFromPixels(cursorImage.getPixelsPtr(), cursorImage.getSize(), sf::Vector2u(0, 0));
	gameWindow.setMouseCursor(gunCursor);


	// Game loop
	while (gameWindow.isOpen()) {
		sf::Event event;
		while (gameWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				gameWindow.close();
			}
			menu.handleEvent(event, gameWindow);
		}

		gameWindow.clear(sf::Color(246, 246, 246));

		menu.draw(gameWindow);

		gameWindow.display();
	}


	return 0;
}
