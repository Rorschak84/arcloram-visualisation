#ifndef VISUALISERMANAGER_HPP
#define VISUALISERMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <memory>
#include "../Device/Device.hpp"
#include "../Button/Button.hpp"
#include "../Common/Common.hpp"



//everything related to the protocol itself is done here
//the rest: button, logs, is done in the display thread
class VisualiserManager {
private:
    sf::Font font; // Font for rendering text
    sf::Text text; // SFML text object
    sf::Text communicationMode;
    sf::Text tickNb;

public:
    VisualiserManager();
    // Draw the text visualisation
    void draw(sf::RenderWindow& window);
    std::vector<std::unique_ptr<Button>> buttons; // List of buttons
    std::vector<std::unique_ptr<Device>> devices; // List of devices (if used elsewhere)


    void addButton(std::unique_ptr<Button> button);
    void addDevice(std::unique_ptr<Device> device);
};

#endif // VISUALISERMANAGER_HPP
