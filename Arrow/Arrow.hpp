#ifndef ARROW_HPP
#define ARROW_HPP

#include <SFML/Graphics.hpp>

class Arrow {
private:
    sf::RectangleShape line;  // Line representing the arrow's shaft
    sf::ConvexShape arrowhead;  // Triangle representing the arrowhead
    sf::Vector2f start;  // Start position
    sf::Vector2f end;    // End position
    float progress;      // Animation progress (0.0 to 1.0)
    float duration;      // Total animation time
    sf::Clock clock;     // Clock to track animation time

    int SenderId;       //used to display the reception State of the message.
    int ReceiverId;

    // Helper to calculate angle for the arrowhead
    float calculateAngle(const sf::Vector2f& p1, const sf::Vector2f& p2) const;

public:
    // Constructor
    Arrow(const sf::Vector2f& start, const sf::Vector2f& end, float duration,int senderId, int receiverId);

    // Update the arrow animation
    void update();

    // Draw the arrow on the given window
    void draw(sf::RenderWindow& window);

    // Check if the animation is finished
    bool isFinished() const;

    // Restart the animation
    void restart();
};

#endif // ARROW_HPP
