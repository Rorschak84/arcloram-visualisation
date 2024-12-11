#include "Arrow.hpp"
#include <cmath> // For trigonometric functions

// Constructor
Arrow::Arrow(const sf::Vector2f& start, const sf::Vector2f& end, float duration,int senderId, int receiverId)
    : start(start), end(end), progress(0.0f), duration(duration) ,SenderId(senderId),ReceiverId(receiverId) {
    // Initialize line (shaft of the arrow)
    line.setSize(sf::Vector2f(0, 5)); // Initially, the line length is 0, thickness = 5
    line.setFillColor(sf::Color::Red);

    // Initialize arrowhead (a triangle)
    arrowhead.setPointCount(3);
    arrowhead.setFillColor(sf::Color::Red);
}

// Calculate the angle between two points
float Arrow::calculateAngle(const sf::Vector2f& p1, const sf::Vector2f& p2) const {
    return std::atan2(p2.y - p1.y, p2.x - p1.x) * 180.0f / 3.14159265f;
}

// Update the arrow animation
void Arrow::update() {
    // Update progress based on elapsed time
    float elapsed = clock.getElapsedTime().asSeconds();
    progress = elapsed / duration;

    if (progress > 1.0f) {
        progress = 1.0f; // Clamp progress
    }

    // Interpolate current position
    sf::Vector2f currentPosition = start + progress * (end - start);

    // Update line
    sf::Vector2f direction = currentPosition - start;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y) * 0.95;//0.95 so the shaft don't overstep on the arrow
    line.setSize(sf::Vector2f(length, 7)); // Adjust the line's length and keep thickness = 5
    line.setPosition(start);
    line.setRotation(calculateAngle(start, currentPosition));

    // Update arrowhead position and rotation
    float angle = calculateAngle(line.getPosition(), currentPosition);
    arrowhead.setPosition(currentPosition);

    // Adjust arrowhead direction
    arrowhead.setRotation(angle);

    // Define the triangle points for the arrowhead
    float arrowSize = 35.0f;  // Size of the arrowhead
    arrowhead.setPoint(0, sf::Vector2f(0, 0));

    arrowhead.setPoint(1, sf::Vector2f(-arrowSize, arrowSize / 2));
    arrowhead.setPoint(2, sf::Vector2f(-arrowSize, -arrowSize / 2));
}

// Draw the arrow on the window
void Arrow::draw(sf::RenderWindow& window) {
    window.draw(line);
    window.draw(arrowhead);
}

// Check if the animation is finished
bool Arrow::isFinished() const {
    return progress >= 1.0f;
}

// Restart the animation
void Arrow::restart() {
    progress = 0.0f;
    clock.restart();
}
