


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


    communicationMode.setFont(font);
    communicationMode.setCharacterSize(40);
    communicationMode.setPosition(10.f, 10.f);
    communicationMode.setFillColor(sf::Color::White);

    tickNb.setFont(font);
    tickNb.setCharacterSize(20);
    tickNb.setPosition(10.f, 80.f);
    tickNb.setFillColor(sf::Color::White);
}

void VisualiserManager::addButton(std::unique_ptr<Button> button) {
	buttons.push_back(std::move(button));
}

void VisualiserManager::addDevice(std::unique_ptr<Device> device) {
    devices.push_back(std::move(device));
}


void VisualiserManager::draw(sf::RenderWindow& window) {
    std::ostringstream displayText;

    communicationMode.setString("Communication Mode: "+COMMUNICATION_MODE);
    window.draw(communicationMode);

    tickNb.setString("Tick Number: " + std::to_string(TICK_NB));
    window.draw(tickNb);

    //Button States
    displayText << "Button States:\n";

    for (int i = 0; i < buttons.size(); ++i) {
        displayText << "Button " << (i + 1) << ": " << buttons[i]->getState() << "\n";
    }
    text.setString(displayText.str());
    text.setPosition(10.f, 300.f); // Display below buttons
    window.draw(text);



    //draw devices
    for (auto& device : devices) {
        device->draw(window);
    }
}
