


#include "VisualiserManager.hpp"
#include <stdexcept>
#include <sstream>
#include <iostream>


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

void VisualiserManager::addArrow(std::unique_ptr<Arrow> arrow)
{
    arrows.push_back(std::move(arrow));
}

void VisualiserManager::changeArrowState(int senderId, int receiverId, std::string state)
{
    if(state!="interference"&&state!="notListening"&&state!="received"){
        throw std::runtime_error("Error: state not recognized");
    }
    for(auto& arrow : arrows){
        if(arrow->SenderId==senderId && arrow->ReceiverId==receiverId){
            arrow->receptionState=state;
        }
    }
}

void VisualiserManager::startBroadcast(const sf::Vector2f &startPosition, float duration)
{
        broadcastAnimations.push_back(std::make_unique<BroadcastAnimation>(startPosition, duration));

}

void VisualiserManager::addDeviceId(int id)
{
    if (devicesId.emplace(id).second) {
            routings[id] = {};
        } else {
            std::cout << "********Device " << id << " already exists********.\n";
        }
}

void VisualiserManager::addRouting(int id1, int id2)
{
    // ID1 ---> ID2 , path towards ID2

    if (devicesId.count(id1) && devicesId.count(id2)) {
            routings[id1].insert(id2);  // Only store id2 in id1's adjacency list       
        } else {
            std::cout << "********One or both devices do not exist.********\n";
    }
}

void VisualiserManager::removeRouting(int id1, int id2)
{
    if (devicesId.count(id1) && devicesId.count(id2)) {
            routings[id1].erase(id2);
        }else {
            std::cout << "********One or both devices do not exist.********\n";
        }
}

void VisualiserManager::update()
{
    // Update all broadcast animations
    for (auto& animation : broadcastAnimations) {
        animation->update();
    }

    //remove finished broadcast animations
    broadcastAnimations.erase(std::remove_if(broadcastAnimations.begin(), broadcastAnimations.end(),
        [](const std::unique_ptr<BroadcastAnimation>& animation) {
            return animation->isFinished();
        }),
        broadcastAnimations.end());


    //Update transmission animation
    for(auto& arrow : arrows){
        arrow->update();
    }

    //remove finished arrows
    arrows.erase(std::remove_if(arrows.begin(), arrows.end(), [](const std::unique_ptr<Arrow>& arrow) {
        return (arrow->isFinished()&&arrow->isReceptionFinished());
    }), arrows.end());


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



    drawRootings(window);

    for (auto& device : devices) {
        device->draw(window);
    }

    for(auto& arrow : arrows){
        arrow->draw(window);
    }
    for(auto& animation : broadcastAnimations){
        animation->draw(window);
    }


}


void VisualiserManager::drawRootings(sf::RenderWindow& window)
{
    for (const auto& [device, connectedDevices] : routings) {
            
            for (const auto& connectedDevice : connectedDevices) {
                //get start position and end position
                sf::Vector2f start;
                sf::Vector2f end;
                bool foundPos=false;
                for(auto& device1 : devices){
                    if(device1->nodeId==device){
                         start=device1->shape.getPosition();
                         //center the start position
                         start.x+=radiusIcon;
                            start.y+=radiusIcon;
                        //get end position
                        for(auto& device2 : devices){
                            if(device2->nodeId==connectedDevice){
                                 end=device2->shape.getPosition();
                                 //center the end position
                                 end.x+=radiusIcon;
                                    end.y+=radiusIcon;
                                 foundPos=true;
                            }
                        }
                    }
                }

                if(foundPos){
                    drawArrowWithHeads(window, start, end, 35.f);
                }
            }
        }

}


