#include "main_menu.h"

Menu::Menu(const sf::Font& font, const std::vector<std::string>& items, std::string menuTitle, sf::RenderWindow& gameWindow) {
	sf::Vector2u zakladniRozliseni(1920, 1080);
	sf::Vector2u aktualniRozliseni = gameWindow.getSize();
	float textSizeRatio = static_cast<float>(aktualniRozliseni.y) / zakladniRozliseni.y;

	sf::Text menuTitleText;
	menuTitleText.setFont(font);
	menuTitleText.setString(menuTitle);
	menuTitleText.setPosition(90, 100);
	menuTitleText.setFillColor(sf::Color(10, 10, 10));
	menuTitleText.setCharacterSize(textSizeRatio * 80);

	menuTitleTextGlobal = menuTitleText;

	for (size_t i = 0; i < items.size(); i++) {
		sf::Text menuItemText;
		menuItemText.setFont(font);
		menuItemText.setString(items[i]);
		menuItemText.setPosition(100, 200 + i * 80);
		menuItemText.setFillColor(sf::Color(200, 200, 200));
		menuItemText.setCharacterSize(textSizeRatio * 50);

		menuItems.push_back(menuItemText);
	}
}

void Menu::setPosition(float x, float y) {
	for (size_t i = 0; i < menuItems.size(); i++) {
		menuItems[i].setPosition(x, y + i * 80);
	}
}

void Menu::draw(sf::RenderWindow& gameWindow) {
	gameWindow.draw(menuTitleTextGlobal);
	for (const auto& item : menuItems) {
		gameWindow.draw(item);
	}
}

void Menu::handleEvent(const sf::Event& event, sf::RenderWindow& gameWindow) {
	sf::Vector2i mousePos = sf::Mouse::getPosition(gameWindow);

	for (auto& item : menuItems) {
		if (item.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
			item.setFillColor(sf::Color(50, 50, 50));
			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				std::cout << "Clicked on: " << item.getString().toAnsiString() << std::endl;
				if (item.getString() == "Exit") {
					gameWindow.close();
				}
			}
		}
		else {
			item.setFillColor(sf::Color(100, 100, 100));
		}
	}
}