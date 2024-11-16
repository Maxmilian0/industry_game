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
#include <sstream>

int main() {
	// Settuping window, images, cursor, fonts
	sf::RenderWindow gameWindow(sf::VideoMode::getDesktopMode(), "The Game Of Industry", sf::Style::Fullscreen);
	sf::Image cursorImage;
	sf::Cursor gunCursor;
	sf::Font geistMonoExtraBold;
	sf::Font geistMonoMedium;
	std::vector<std::string> menuItems = { "Play", "Settings", "Exit" };
	sf::Text fpsText;
	

	fpsText.setFont(geistMonoMedium);
	fpsText.setFillColor(sf::Color::Black);
	fpsText.setPosition(gameWindow.getSize().x - 200.f, gameWindow.getSize().y - (gameWindow.getSize().y - 50));
	
	sf::Clock clock;
	float fps = 0.f;

	Menu menu(geistMonoMedium, menuItems, "The Game Of Industry", gameWindow);

	// Loading media
	MediaLoader::loadMedia(geistMonoExtraBold, "fonts/GeistMono-ExtraBold.ttf");
	MediaLoader::loadMedia(geistMonoMedium, "fonts/GeistMono-Medium.ttf");
	MediaLoader::loadMedia(cursorImage, "cursor.png");

	gunCursor.loadFromPixels(cursorImage.getPixelsPtr(), cursorImage.getSize(), sf::Vector2u(0, 0));
	gameWindow.setMouseCursor(gunCursor);
	
	int fpsSlower = 110;
	gameWindow.setFramerateLimit(60);

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

		float deltaTime = clock.restart().asSeconds();
		fps = 1.f / deltaTime;

		fpsSlower++;
		if (fpsSlower > 10) {
			std::ostringstream oss;
			oss << "FPS: " << static_cast<int>(fps);
			fpsText.setString(oss.str());
			fpsSlower = 0;
		}
		gameWindow.clear(sf::Color(246, 246, 246));

		menu.draw(gameWindow);
		gameWindow.draw(fpsText);

		gameWindow.display();
	}


	return 0;
}
