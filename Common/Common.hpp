#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <mutex>
#include "../Button/Button.hpp"
#include "../VisualiserManager/VisualiserManager.hpp"

//shared data
#pragma once

//shared data
extern std::vector<std::string> logMessages;  // Shared container for received strings
extern std::mutex logMutex;                  // Mutex to protect the container
extern bool isRunning;                // Flag to signal threads to stop

extern std::string COMMUNICATION_MODE;
extern int TICK_NB; 
extern double DISTANCE_THRESHOLD;
extern std::mutex deviceMutex;



//General DATA:
extern  const int windowWidth;
extern  const int windowHeight;

//Buttons:
extern const std::string on;
extern const std::string off;

extern const float x1coor;
extern const float y1coor;
extern const float width1;
extern const float height1;
extern const sf::Color color1;
extern std::string state1;
extern const std::string iconPath1;

extern const float x2coor;
extern const float y2coor;
extern const float width2;
extern const float height2;
extern const sf::Color color2;
extern std::string state2;
extern const std::string iconPath2;

extern const float x3coor;
extern const float y3coor;
extern const float width3;
extern const float height3;
extern const sf::Color color3;
extern std::string state3;
extern const std::string iconPath3;

extern const float x4coor;
extern const float y4coor;
extern const float width4;
extern const float height4;
extern const sf::Color color4;
extern std::string state4;
extern const std::string iconPath4;

////x,y width, height, color, state, on, off
//extern Button button1;
//extern Button button2;
//extern Button button3;
//extern Button button4;
//extern VisualiserManager visualiserManager;


