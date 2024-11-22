#include "main_menu.hpp"

Menu::Menu(const sf::Font& _Font, const std::vector<std::string>& _Items, std::string _MenuTitle, sf::RenderWindow& _GameWindow) {
    sf::Vector2u zakladniRozliseni(1920, 1080);
    sf::Vector2u aktualniRozliseni = _GameWindow.getSize();
    float textSizeRatio = static_cast<float>(aktualniRozliseni.y) / zakladniRozliseni.y;

    if (!buffer.loadFromFile("sound/anvilStrike.wav")) {
        logFile.open("REPORT.txt", std::ios::app);
        logFile << "\t[X] Error_4v8e (anviltrike.wav)" << std::endl;
        logFile.close();
    }

    for (int i = 0; i < 5; ++i) { 
        sf::Sound sound;
        sound.setBuffer(buffer);
        soundPool.push_back(sound);
    }

    sf::Text menuTitleText;
    menuTitleText.setFont(_Font);
    menuTitleText.setString(_MenuTitle);
    menuTitleText.setPosition(80, 100);
    menuTitleText.setFillColor(sf::Color(10, 10, 10));
    menuTitleText.setCharacterSize(static_cast<unsigned int>(textSizeRatio * 80));
    menuTitleTextGlobal = menuTitleText;

    for (size_t i = 0; i < _Items.size(); i++) {
        sf::Text menuItemText;
        menuItemText.setFont(_Font);
        menuItemText.setString(_Items[i]);
        menuItemText.setFillColor(sf::Color(200, 200, 200));
        menuItemText.setCharacterSize(static_cast<unsigned int>(textSizeRatio * 50));
        menuItemText.setPosition(110, 200 + i * 80);

        menuItems.push_back(menuItemText);
        howers.push_back(false);
    }
}

void Menu::setPosition(float _X, float _Y) {
    for (size_t i = 0; i < menuItems.size(); i++) {
        menuItems[i].setPosition(_X, _Y + i * 80);
    }
}

void Menu::draw(sf::RenderWindow& _GameWindow) {
    _GameWindow.draw(menuTitleTextGlobal);
    for (const auto& item : menuItems) {
        _GameWindow.draw(item);
    }
}

int Menu::handleEvent(const sf::Event& _Event, sf::RenderWindow& _GameWindow) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(_GameWindow);

    for (size_t i = 0; i < menuItems.size(); ++i) {
        if (menuItems[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
            menuItems[i].setFillColor(sf::Color(100, 100, 100));
            if (!howers[i]) {
                soundPool[currentSoundIndex].play();
                currentSoundIndex = (currentSoundIndex + 1) % soundPool.size();
                howers[i] = true;
            }
            if (_Event.type == sf::Event::MouseButtonPressed && _Event.mouseButton.button == sf::Mouse::Button::Left) {
                logFile.open("REPORT.txt", std::ios::app);
                logFile << "[?] Opening " << menuItems[i].getString().toAnsiString() << std::endl;
                logFile.close();

               if (menuItems[i].getString() == "Exit") {
                   logFile.open("REPORT.txt", std::ios::app);
                   logFile << "[!] Closing program (menu button)" << std::endl;
                   logFile.close();
                   _GameWindow.close();
               }
               else if (menuItems[i].getString() == "Play") {
                   return 1;
               }
               else if (menuItems[i].getString() == "Settings") {
                   return 2;
               }
               else {
                   return -1;
               }
            }
        }
        else {
            howers[i] = false;
            menuItems[i].setFillColor(sf::Color(200, 200, 200));
        }
    }
}
