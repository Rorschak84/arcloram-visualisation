#ifndef BROADCASTANIMATION_HPP
#define BROADCASTANIMATION_HPP

#include <SFML/Graphics.hpp>

class BroadcastAnimation {
public:
    // Constructor
    BroadcastAnimation(const sf::Vector2f& startPosition, float duration);

    // Update the animation state (time-based, no deltaTime required)
    void update();

    // Draw the animation
    void draw(sf::RenderWindow& window) const;

    // Check if the animation is finished
    bool isFinished() const;

private:
    sf::CircleShape circle;     // Expanding circle shape
    sf::Vector2f startPosition; // Starting position of the circle
    float duration;             // Total duration of the animation (seconds)
    sf::Clock clock;            // Clock to track elapsed time
};

#endif // BROADCASTANIMATION_HPP
