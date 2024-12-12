#include "BroadcastAnimation.hpp"
#include "../Common/Common.hpp"

BroadcastAnimation::BroadcastAnimation(const sf::Vector2f& startPosition, float duration)
    : startPosition(startPosition), duration(duration){

    circle.setFillColor(sf::Color(255, 255, 255, 50)); // Semi-transparent white
    circle.setOutlineThickness(1.f);
    circle.setOutlineColor(sf::Color::White);
    circle.setRadius(0.f); // Start with zero radius
    circle.setOrigin(0.f, 0.f); // No size, no origin adjustment needed yet
    circle.setPosition(startPosition);
}

void BroadcastAnimation::update() {
    // Calculate progress based on elapsed time
    float elapsedTime = clock.getElapsedTime().asSeconds();
    float progress = elapsedTime / duration;

    if (progress > 1.0f) {
        progress = 1.0f; // Clamp progress to 1.0
    }

    // Calculate the current radius
    float currentRadius = progress * DISTANCE_THRESHOLD;

    circle.setRadius(currentRadius);

    // Adjust the origin to keep the circle centered
    circle.setOrigin(currentRadius, currentRadius);
}

void BroadcastAnimation::draw(sf::RenderWindow& window) const {
    if (!isFinished()) {
        window.draw(circle);
    }
}

bool BroadcastAnimation::isFinished() const {
    // The animation is finished if the elapsed time exceeds the duration
    return clock.getElapsedTime().asSeconds() >= duration;
}