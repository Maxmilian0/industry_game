#define NOMINMAX
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <ctime>
#include <sstream>
#include <array>
#include <thread>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include "main_menu.h"
#include "media_loader.h"
#include "game.h"

// Funkce pro získání aktuálního času
std::string getCurrentTime() {
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    char buffer[26];
    ctime_s(buffer, sizeof(buffer), &now);
    std::string timeStr(buffer);
    timeStr.pop_back();
    return timeStr;
}

// Funkce pro získání uživatelského jména
std::string getUsername() {
    wchar_t username[256];
    DWORD len = 256;
    if (GetUserNameW(username, &len)) {
        int sizeNeeded = WideCharToMultiByte(CP_UTF8, 0, username, -1, nullptr, 0, nullptr, nullptr);
        std::string result(sizeNeeded, '\0');
        WideCharToMultiByte(CP_UTF8, 0, username, -1, &result[0], sizeNeeded, nullptr, nullptr);
        return result;
    }
    else {
        return "Unknown User";
    }
}

// Funkce pro získání verze operačního systému
std::string getOSVersion() {
    OSVERSIONINFOEX osvi = {};
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

    typedef NTSTATUS(WINAPI* RtlGetVersionPtr)(OSVERSIONINFOEX*);
    RtlGetVersionPtr RtlGetVersion = (RtlGetVersionPtr)GetProcAddress(GetModuleHandle(L"ntdll.dll"), "RtlGetVersion");

    if (RtlGetVersion) {
        if (RtlGetVersion(&osvi) == 0) {
            std::ostringstream oss;
            oss << "Windows " << osvi.dwMajorVersion << "." << osvi.dwMinorVersion
                << " (Build " << osvi.dwBuildNumber << ")";
            return oss.str();
        }
    }
    return "Unable to determine OS version";
}

// Funkce pro získání informací o RAM
void logMemoryInfo(std::ofstream& logFile) {
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof(MEMORYSTATUSEX);

    if (GlobalMemoryStatusEx(&statex)) {
        logFile << "Total RAM: " << statex.ullTotalPhys / (1024 * 1024) << " MB" << std::endl;  // Celková RAM
        logFile << "Available RAM: " << statex.ullAvailPhys / (1024 * 1024) << " MB" << std::endl;  // Volná RAM
        logFile << "Used RAM: " << (statex.ullTotalPhys - statex.ullAvailPhys) / (1024 * 1024) << " MB" << std::endl; // Použitá RAM
    }
    else {
        logFile << "[X] Failed to get memory info." << std::endl;
    }
}

// Funkce pro zápis diagnostických informací
void logDiagnostics(const std::string& logFileName) {
    std::ofstream logFile(logFileName, std::ios::app);
    if (!logFile.is_open()) {
        std::cerr << "Failed to open log file\n";
        return;
    }

    std::string timeStr = getCurrentTime();
    std::string username = getUsername();
    std::string osVersion = getOSVersion();
    unsigned int cores = std::thread::hardware_concurrency();

    logFile << "========================- PLAYER'S PC  -========================\n\n";
    logFile << "Time: " << timeStr << "\n";
    logFile << "User: " << username << "\n";
    logFile << "OS Version: " << osVersion << "\n";
    logFile << "CPU Cores: " << cores << "\n";
    auto desktopMode = sf::VideoMode::getDesktopMode();
    logFile << "Screen resolution: " << desktopMode.width << "x" << desktopMode.height << "\n"; 
    logMemoryInfo(logFile);
    logFile << "\n========================- DEBUG REPORT -========================\n\n";
    logFile.close();
}


int main() {
    auto start = std::chrono::system_clock::now();

    std::ofstream logFile;
    logFile.open("REPORT.txt");

    logFile << "DEBUG TERMINAL - The Game Of Industry" << std::endl << std::endl;
    logFile << "[*]         = something is successfully done" << std::endl;
    logFile << "[O]         = \"new chapter\" of debug output" << std::endl;
    logFile << "* STATE *   = current state. Examples: GAME STATE, MENU STATE" << std::endl;
    logFile << "[X]         = error message" << std::endl;
    logFile << "[!]         = warning" << std::endl;
    logFile << "[?]         = debug info" << std::endl;
    logDiagnostics("REPORT.txt");
    logFile.close();

    // Setting up window, images, cursor, fonts
    sf::RenderWindow gameWindow(sf::VideoMode::getDesktopMode(), "The Game Of Industry", sf::Style::Fullscreen);
    sf::Image cursorImage;
    sf::Cursor gunCursor;
    sf::Font geistMonoExtraBold;
    sf::Font geistMonoMedium;
    std::vector<std::string> menuItems = { "Play", "Settings", "Exit" };
    sf::Text fpsText, mousePosText;

    fpsText.setFont(geistMonoMedium);
    fpsText.setFillColor(sf::Color::Black);
    fpsText.setCharacterSize(15.f);
    fpsText.setPosition(gameWindow.getSize().x - 100.f, gameWindow.getSize().y - (gameWindow.getSize().y - 5));

    mousePosText = fpsText;
    mousePosText.setPosition(gameWindow.getSize().x - 150.f, gameWindow.getSize().y - (gameWindow.getSize().y - 25));

    sf::Clock clock;
    float fps = 0.f;

    Menu menu(geistMonoMedium, menuItems, "The Game Of Industry", gameWindow);

    // Loading media
    MediaLoader::loadMedia(geistMonoExtraBold, "font/GeistMono-ExtraBold.ttf");
    MediaLoader::loadMedia(geistMonoMedium, "font/GeistMono-Medium.ttf");
    MediaLoader::loadMedia(cursorImage, "img/cursor.png");

    gunCursor.loadFromPixels(cursorImage.getPixelsPtr(), cursorImage.getSize(), sf::Vector2u(0, 0));
    gameWindow.setMouseCursor(gunCursor);

    // FPS settings
    int fpsSlower = 110; // For better debugging output
    int fpsFramerateLimitNum = 60;
    gameWindow.setFramerateLimit(fpsFramerateLimitNum);

    logFile.open("REPORT.txt", std::ios::app);
    logFile << "[?] Game window FPS limit: " << fpsFramerateLimitNum << std::endl;
    logFile.close();

    // State switching mechanism (when I play the game, I don't see the menu)
    enum GameState { MENU, GAME };
    GameState currentState = MENU;

    // Initialize game
    Game game;

    logFile.open("REPORT.txt", std::ios::app);
    logFile << "[*] Program setup completed" << std::endl;
    if (currentState == MENU)
        logFile << "\t* MENU STATE *" << std::endl;
    logFile.close();

    // Game loop
    while (gameWindow.isOpen()) {
        sf::Event event;
        while (gameWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                logFile.open("REPORT.txt", std::ios::app);
                logFile << "[*] Closing program (user requested)" << std::endl;
                logFile.close();
                gameWindow.close();
            }

            if (currentState == MENU) {
                switch (menu.handleEvent(event, gameWindow)) {
                case 1:
                    logFile.open("REPORT.txt", std::ios::app);
                    logFile << "\t* GAME STATE *" << std::endl;
                    logFile.close();
                    currentState = GAME;
                    break;
                case 2:
                    break;
                case -1:
                    logFile.open("REPORT.txt", std::ios::app);
                    logFile << "[X] Error_01a4 (menu selector)" << std::endl;
                    logFile.close();
                    return -1;
                }
            }
            else if (currentState == GAME) {
                game.handleEvent(event, gameWindow);
            }
        }

        float deltaTime = clock.restart().asSeconds();
        fps = 1.f / deltaTime;

        fpsSlower++;
        if (fpsSlower > 10) {
            std::ostringstream oss;
            oss << "FPS: " << static_cast<int>(fps);
            if (fps < 5) {
                logFile.open("REPORT.txt", std::ios::app);
                logFile << "[!] Low FPS (" << fps << "fps) at " << getCurrentTime() << std::endl;
                logFile.close();
            }
            fpsText.setString(oss.str());
            fpsSlower = 0;
        }

        std::ostringstream oss2;
        sf::Vector2i mousePos = sf::Mouse::getPosition(gameWindow);
        oss2 << "x: " << mousePos.x << " y: " << mousePos.y;
        mousePosText.setString(oss2.str());

        // MAIN LOOP
        gameWindow.clear(sf::Color(246, 246, 246));

        if (currentState == MENU) {
            menu.draw(gameWindow);
        }
        else if (currentState == GAME) {
            game.draw(gameWindow);
        }

        gameWindow.draw(fpsText); // FPS count for debug
        gameWindow.draw(mousePosText); // Mouse position for debug

        gameWindow.display();
    }

    // Measure elapsed time
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    char timeBuffer[26];
    ctime_s(timeBuffer, sizeof(timeBuffer), &end_time);

    logFile.open("REPORT.txt", std::ios::app);
    logFile << "[?] Program finished at " << timeBuffer;
    logFile << "[?] Elapsed time: " << elapsed_seconds.count() << "s" << std::endl;
    logFile << "[*] Log completed";
    logFile.close();

    return 0;
}
