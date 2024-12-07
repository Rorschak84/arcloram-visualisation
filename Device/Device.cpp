



#include "Device.hpp"
#include <iostream>

Device::Device(int nodeId,
    int classNode, std::pair<int, int> coordinates):
    nodeId(nodeId), classNode(classNode), coordinates(coordinates) {

        double radius=35.f;
        shape.setRadius(radius);
        shape.setPosition(coordinates.first, coordinates.second);  
        shape.setFillColor(sf::Color::White);


        //depending of the class, we load the corresponding icon
        if(classNode==3){
            if (!iconTexture.loadFromFile("assets/Icons/star.png")) {
                throw std::runtime_error("Failed to load icon texture for class 3·");
            }
            // Set up the sprite
            icon.setTexture(iconTexture);

            // Scale the icon to fit inside the button if needed
            float scaleX = (radius * 0.6f) / iconTexture.getSize().x;
            float scaleY = (radius * 0.6f) / iconTexture.getSize().y;
            icon.setScale(scaleX, scaleY);

            // Center the icon inside the button
            icon.setPosition(
                coordinates.first + (radius - iconTexture.getSize().x * scaleX) / 2.f,
                coordinates.second + (radius - iconTexture.getSize().y * scaleY) / 2.f
            );
        }
        else if(classNode==2){

        }
        else{
            std::cerr<<"Error: classNode not recognized"<<std::endl;
        }
}

void Device::draw(sf::RenderWindow &window)
{
    window.draw(shape);
    window.draw(icon);   // Draw the icon
}
