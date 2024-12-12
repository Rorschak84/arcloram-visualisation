


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


