//#include <SFML/Graphics.hpp>
//#include "Device.cpp"
//
//class VisualiserManager {
//
//private:
//    sf::Font font;
//    sf::Text text;
//    std::string(&_buttonStates)[4];
//
//
//    std::vector<Device> devices;
//
//public:
//    VisualiserManager(std::string(& buttonStates)[4]): _buttonStates(buttonStates) {
//        if (!font.loadFromFile("assets/arial.ttf")) {
//            throw std::runtime_error("Failed to load font");
//        }
//        text.setFont(font);
//        text.setCharacterSize(20);
//        text.setFillColor(sf::Color::White);
//    }
//
//    void draw(sf::RenderWindow& window) {
//        std::string displayText = "Button States:\n";
//        for (int i = 0; i < 4; ++i) {
//            displayText += "Button " + std::to_string(i + 1) + ": " + _buttonStates[i] + "\n";
//        }
//        text.setString(displayText);
//        text.setPosition(10.f, 150.f); // Display below buttons
//        window.draw(text);
//    }
//};


#include "VisualiserManager.hpp"
#include <stdexcept>
#include <sstream>

VisualiserManager::VisualiserManager()
     {
    if (!font.loadFromFile("assets/arial.ttf")) {
        throw std::runtime_error("Failed to load font");
    }
    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);

}

void VisualiserManager::addButton(std::unique_ptr<Button> button) {
	buttons.push_back(std::move(button));
}

void VisualiserManager::draw(sf::RenderWindow& window) {
    std::ostringstream displayText;
    displayText << "Button States:\n";

    for (int i = 0; i < buttons.size(); ++i) {
        displayText << "Button " << (i + 1) << ": " << buttons[i]->getState() << "\n";
    }
    text.setString(displayText.str());
    text.setPosition(10.f, 300.f); // Display below buttons
    window.draw(text);
}
