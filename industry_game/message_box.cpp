#include "message_box.h"

MessageBox::MessageBox(const sf::Font& font, const std::string& message, const std::string& title) {
    // Background
    background.setSize(sf::Vector2f(400, 200));
    background.setFillColor(sf::Color(50, 50, 50));
    background.setOutlineThickness(2);
    background.setOutlineColor(sf::Color::White);
    background.setPosition(200, 200);

    // Title
    titleText.setFont(font);
    titleText.setString(title);
    titleText.setCharacterSize(24);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(background.getPosition().x + 10, background.getPosition().y + 10);

    // Message
    messageText.setFont(font);
    messageText.setString(message);
    messageText.setCharacterSize(20);
    messageText.setFillColor(sf::Color::White);
    messageText.setPosition(background.getPosition().x + 10, background.getPosition().y + 50);

    // Yes button
    yesButton.setSize(sf::Vector2f(100, 40));
    yesButton.setFillColor(sf::Color(100, 255, 100));
    yesButton.setPosition(background.getPosition().x + 50, background.getPosition().y + 130);

    yesButtonText.setFont(font);
    yesButtonText.setString("Yes");
    yesButtonText.setCharacterSize(18);
    yesButtonText.setFillColor(sf::Color::Black);
    yesButtonText.setPosition(yesButton.getPosition().x + 25, yesButton.getPosition().y + 8);

    // No button
    noButton.setSize(sf::Vector2f(100, 40));
    noButton.setFillColor(sf::Color(255, 100, 100));
    noButton.setPosition(background.getPosition().x + 250, background.getPosition().y + 130);

    noButtonText.setFont(font);
    noButtonText.setString("No");
    noButtonText.setCharacterSize(18);
    noButtonText.setFillColor(sf::Color::Black);
    noButtonText.setPosition(noButton.getPosition().x + 25, noButton.getPosition().y + 8);
}

bool MessageBox::show(sf::RenderWindow& window) const {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return false; // Default to "No" if window is closed
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                if (yesButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    return true; // User clicked "Yes"
                }

                if (noButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                    return false; // User clicked "No"
                }
            }
        }

        // Draw message box
        window.clear();
        window.draw(background);
        window.draw(titleText);
        window.draw(messageText);
        window.draw(yesButton);
        window.draw(yesButtonText);
        window.draw(noButton);
        window.draw(noButtonText);
        window.display();
    }

    return false; // Shouldn't reach here under normal circumstances
}
