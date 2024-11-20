#include "game.h"

// Globální inicializace generátoru náhodných čísel
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> dis(0, 4);

// Konstruktor třídy Game
Game::Game() {
    // Pokus o načtení textury
    if (!tileSet.loadFromFile("img/texture4.png")) {
        logFile.open("REPORT.txt", std::ios::app);
        if (logFile.is_open()) {
            logFile << "[X] Error while loading img/texture.png" << std::endl;
            logFile.close();
        }
        else {
            std::cerr << "Failed to open log file." << std::endl;
        }
        return;  // Ukončí konstruktor, pokud se textura nepodaří načíst
    }

    // Vytvoření a inicializace dlaždic
    int halfer = 0;
    int y = 0;
    int iHelper = 0;
    for (size_t i = 0; i < 300; i++) {
        sf::ConvexShape mapTile;
        mapTile.setPointCount(6); // Hexagonální tvar
        if (i % 11 == 0 && i != 0) {
            y += 50;
            iHelper = 0;
            if (halfer == 100) {
                halfer = 0;
            }
            else {
                halfer = 100;
            }
        }
        mapTile.setPosition(sf::Vector2f(iHelper * 200 - halfer, y - 200));

        // Nastavení bodů hexagonu
        mapTile.setPoint(0, sf::Vector2f(0, 50));
        mapTile.setPoint(1, sf::Vector2f(100, 0));
        mapTile.setPoint(2, sf::Vector2f(200, 50));
        mapTile.setPoint(3, sf::Vector2f(200, 150));
        mapTile.setPoint(4, sf::Vector2f(100, 200));
        mapTile.setPoint(5, sf::Vector2f(0, 150));

        // Připojení textury k dlaždici
        mapTile.setTexture(&tileSet);
        mapTile.setTextureRect(sf::IntRect(dis(gen) * 200, 0, 200, 200));

        // Přidání dlaždice do seznamu
        mapItems.push_back(mapTile);
        iHelper++;
    }
}

// Kreslení objektů na obrazovku
void Game::draw(sf::RenderWindow& _GameWindow) {
    for (const auto& mapItem : mapItems) {
        _GameWindow.draw(mapItem);
    }
}

// Aktualizace herní logiky (zatím prázdná)
void Game::update() {
}

// Zpracování událostí
int Game::handleEvent(const sf::Event& _Event, sf::RenderWindow& _GameWindow) {
    // Vrátí 0, pokud hra pokračuje
    // Vrátí 1, pokud se má vrátit do hlavního menu
    sf::Vector2i mousePos = sf::Mouse::getPosition(_GameWindow);

    if (_Event.type == sf::Event::KeyPressed && _Event.key.scancode == sf::Keyboard::Scan::Escape) {
        return 1;
    }

    for (size_t i = 0; i < mapItems.size(); ++i) {
        // Zde můžete implementovat zpracování kliknutí na dlaždice
        // if (/* nějaká podmínka */) {
        //     // Reakce na událost
        // }
    }

    return 0;
}
