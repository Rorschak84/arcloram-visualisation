#include "Common.hpp"


//shared data
std::vector<std::string> logMessages;  // Shared container for received strings
std::mutex logMutex;                  // Mutex to protect the container
bool isRunning = true;                // Flag to signal threads to stop
//std::string buttonStates[4] = { "OFF", "OFF", "OFF", "OFF" };


//General DATA:
constexpr const int windowWidth = 1800;
constexpr const int windowHeight = 1200;

//Buttons:
const std::string on = "ON";
const std::string off = "OFF";

const float x1coor = 1800.f - 310.f;
const float y1coor = 40.f;
const float width1 = 80.f;
const float height1 = 40;
const sf::Color color1 = sf::Color::Red;
std::string state1 = off;
const std::string iconPath1 = "assets/Icons/infinity.png";

const float x2coor = 1800.f - 230.f;
const float y2coor = 40.f;
const float width2 = 80.f;
const float height2 = 40;
const sf::Color color2 = sf::Color::Green;
std::string state2 = off;
const std::string iconPath2 = "assets/Icons/play.png";

const float x3coor = 1800.f - 150.f;
const float y3coor = 40.f;
const float width3 = 80.f;
const float height3 = 40;
const sf::Color color3 = sf::Color::Blue;
std::string state3 = off;
const std::string iconPath3 = "assets/Icons/fastplay.png";

const float x4coor = 1800.f - 150.f;
const float y4coor = 100.f;
const float width4 = 80.f;
const float height4 = 40;
const sf::Color color4 = sf::Color::Yellow;
std::string state4 = off;
const std::string iconPath4 = "assets/Icons/routing.png";


//
//
//Button button1(x1coor, y1coor, width1, height1, color1, state1, on, off, iconPath1);
//Button button2(x2coor, y2coor, width2, height2, color2, state2, on, off, iconPath2);
//Button button3(x3coor, y3coor, width3, height3, color3, state3, on, off, iconPath3);
//Button button4(x4coor, y4coor, width4, height4, color4, state4, on, off, iconPath4);
//
//VisualiserManager visualiserManager(buttonStates);

