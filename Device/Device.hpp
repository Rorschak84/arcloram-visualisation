#include <utility>
#include <SFML/Graphics.hpp>

class Device {

    std::pair<int, int> coordinates;
    int nodeId;
    int classNode;
    sf::Sprite icon;            // Icon inside the button
    sf::Texture iconTexture;    // Texture for the icon
    std::string state;
};