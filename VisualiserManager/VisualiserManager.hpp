#ifndef VISUALISERMANAGER_HPP
#define VISUALISERMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <memory>
#include "../Device/Device.hpp"
#include "../Button/Button.hpp"

class VisualiserManager {
private:
    sf::Font font; // Font for rendering text
    sf::Text text; // SFML text object
    std::vector<Device> devices; // List of devices (if used elsewhere)

public:
    VisualiserManager();
    // Draw the text visualisation
    void draw(sf::RenderWindow& window);
    std::vector<std::unique_ptr<Button>> buttons; // List of buttons

    void addButton(std::unique_ptr<Button> button);
};

#endif // VISUALISERMANAGER_HPP
