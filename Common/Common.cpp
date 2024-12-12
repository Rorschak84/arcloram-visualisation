#include "Common.hpp"


//shared data
std::vector<std::string> logMessages;  // Shared container for received strings
std::mutex logMutex;                  // Mutex to protect the container
bool isRunning = true;                // Flag to signal threads to stop
std::string COMMUNICATION_MODE = "None";
int TICK_NB = 0;
float DISTANCE_THRESHOLD = 0.0f;
float broadcastDuration = 1.3f;
float arrowDuration = 1.0f;

std::mutex deviceMutex;

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



