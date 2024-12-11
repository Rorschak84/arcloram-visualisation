#pragma once

#include <utility>
#include <SFML/Graphics.hpp>

class Device {

public:
    Device(int nodeId,
    int classNode, std::pair<int, int> coordinates);
    std::pair<int, int> coordinates;
    int nodeId;
    int classNode;

    sf::CircleShape shape;
    sf::Texture iconTexture;    // Texture for the icon
    std::string state;

    // sf::RectangleShape shape;
    // sf::Sprite icon;    // Icon inside the button
    // sf::Texture iconTexture; // Texture for the icon
    void draw(sf::RenderWindow& window);
    void changePNG(std::string state);
};