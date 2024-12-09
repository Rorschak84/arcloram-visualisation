



#include "Device.hpp"
#include <iostream>

Device::Device(int nodeId,
    int classNode, std::pair<int, int> coordinates):
    nodeId(nodeId), classNode(classNode), coordinates(coordinates) {

        double radius=40.f;

        shape= sf::CircleShape (radius);
        iconTexture= sf::Texture();



        //depending of the class, we load the corresponding icon
        if(classNode==3){
            if (!iconTexture.loadFromFile("assets/Icons/star.png")) {
                throw std::runtime_error("Failed to load icon texture for class 3·");
            }            
            shape.setTexture(&iconTexture);
            shape.setPosition(
                coordinates.first- radius ,
                coordinates.second- radius
            );

        }
        else if(classNode==2){
            if (!iconTexture.loadFromFile("assets/Icons/triangle.png")) {
                throw std::runtime_error("Failed to load icon texture for class 2·");
            }            
            shape.setTexture(&iconTexture);
            shape.setPosition(
                coordinates.first- radius ,
                coordinates.second- radius
            );
        }
        else{
            std::cerr<<"Error: classNode not recognized"<<std::endl;
        }
}

void Device::draw(sf::RenderWindow &window)
{
    window.draw(shape);
    //window.draw(icon);
}
