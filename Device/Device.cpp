



#include "Device.hpp"
#include <iostream>

Device::Device(int nodeId,
    int classNode, std::pair<int, int> coordinates):
    nodeId(nodeId), classNode(classNode), coordinates(coordinates) {

        double radius=40.f;

        shape= sf::CircleShape (radius);
        iconTexture= sf::Texture();

        state="Sleep";

        //depending of the class, we load the corresponding icon
        if(classNode==3){
            if (!iconTexture.loadFromFile("assets/Icons/C3_Sleep.png")) {
                throw std::runtime_error("Failed to load icon texture for class 3·");
            }            
            shape.setTexture(&iconTexture);
            shape.setPosition(
                coordinates.first- radius ,
                coordinates.second- radius
            );

        }
        else if(classNode==2){
            if (!iconTexture.loadFromFile("assets/Icons/C2_Sleep.png")) {
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

void Device::changePNG(std::string state)
{
    std::string classNodeString;
    if(classNode==2){
        classNodeString="C2";
    }
    else if(classNode==3){
        classNodeString="C3";
    }
    else if(classNode==1){
        classNodeString="C1";
    }
    else{
        std::cerr<<"Error: classNode not recognized"<<std::endl;
    }

   std::string path = "assets/Icons/" +classNodeString+"_"+ state + ".png";
    if (!iconTexture.loadFromFile(path)) {
        throw std::runtime_error("Failed to load icon texture");
    }
    shape.setTexture(&iconTexture);
}
