﻿#include "main_menu.h"

Menu::Menu(const sf::Font& font, const std::vector<std::string>& items, std::string menuTitle, sf::RenderWindow& gameWindow) {
    sf::Vector2u zakladniRozliseni(1920, 1080);
    sf::Vector2u aktualniRozliseni = gameWindow.getSize();
    float textSizeRatio = static_cast<float>(aktualniRozliseni.y) / zakladniRozliseni.y;

    if (!buffer.loadFromFile("anvilStrike.wav")) {
        std::cerr << "ERROR - Failed to load sound" << std::endl;
    }

    // Inicializace poolu zvuků
    for (int i = 0; i < 5; ++i) { // 5 zvukových instancí
        sf::Sound sound;
        sound.setBuffer(buffer);
        soundPool.push_back(sound);
    }

    sf::Text menuTitleText;
    menuTitleText.setFont(font);
    menuTitleText.setString(menuTitle);
    menuTitleText.setPosition(80, 100);
    menuTitleText.setFillColor(sf::Color(10, 10, 10));
    menuTitleText.setCharacterSize(static_cast<unsigned int>(textSizeRatio * 80));
    menuTitleTextGlobal = menuTitleText;

    for (size_t i = 0; i < items.size(); i++) {
        sf::Text menuItemText;
        menuItemText.setFont(font);
        menuItemText.setString(items[i]);
        menuItemText.setPosition(110, 200 + i * 80);
        menuItemText.setFillColor(sf::Color(200, 200, 200));
        menuItemText.setCharacterSize(static_cast<unsigned int>(textSizeRatio * 50));

        menuItems.push_back(menuItemText);
        howers.push_back(false); // Inicializace hover stavu na false
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

    for (size_t i = 0; i < menuItems.size(); ++i) {
        if (menuItems[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
            if (!howers[i]) { // Pokud myš nově vstoupila na položku
                soundPool[currentSoundIndex].play();
                currentSoundIndex = (currentSoundIndex + 1) % soundPool.size(); // Posun na další zvuk
                howers[i] = true;
            }
            menuItems[i].setFillColor(sf::Color(100, 100, 100));
        }
        else {
            howers[i] = false; // Reset hover stavu, pokud myš opustí položku
            menuItems[i].setFillColor(sf::Color(200, 200, 200));
        }
    }
}
