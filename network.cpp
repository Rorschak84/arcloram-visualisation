#include <SFML/Network.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include <thread>
#include <chrono>

// Assuming these are your custom packet structures
#include "Packets/Packets.hpp" 
#include "Common/Common.hpp"



inline void networkThread(VisualiserManager& manager) {
    sf::TcpListener listener;
    std::vector<std::unique_ptr<sf::TcpSocket>> clients;

    // Start listening on port 5000
    if (listener.listen(5000) != sf::Socket::Done) {
        std::cerr << "Error starting server on port 5000\n";
        isRunning = false;
        return;
    }
    std::cout << "Server is running on port 5000...\n";

    listener.setBlocking(false);  // Non-blocking mode

    while (isRunning) {
        // Accept new connections
        auto client = std::make_unique<sf::TcpSocket>();
        if (listener.accept(*client) == sf::Socket::Done) {
            std::cout << "New client connected\n";
            client->setBlocking(false);  // Non-blocking client
            clients.push_back(std::move(client));
        }

        // Receive data from clients
        for (auto& client : clients) {
            sf::Packet packet;
            if (client->receive(packet) == sf::Socket::Done) {
                
                int packetType;
                packet >> packetType; // Read the type first

                switch (packetType) {
                case 0: {
                    systemPacket sp;
                    
                    packet >> sp.distanceThreshold>>sp.mode; // Deserialize the systemPacket
                    std::cout << "Received systemPacket: "
                        << "distanceThreshold=" << sp.distanceThreshold
                        << ", mode=" << sp.mode << std::endl;
                    DISTANCE_THRESHOLD = sp.distanceThreshold;
                    COMMUNICATION_MODE = sp.mode;
                    std::string message = "Received systemPacket: distanceThreshold=" + std::to_string(sp.distanceThreshold) + ", mode=" + sp.mode;
                    {
                        std::lock_guard<std::mutex> lock(logMutex);
                        logMessages.push_back(message);
                    }
                    break;
                }
                case 1: {
                    tickPacket tp;
                    packet >> tp.tickNb; // Deserialize the systemPacket
                    std::cout << "Received tickPacket: "
                        << "tickNumber=" << tp.tickNb << std::endl;
                    TICK_NB = tp.tickNb;
                    std::string message = "Received tickPacket: tickNumber=" + std::to_string(tp.tickNb);
                    {
                        std::lock_guard<std::mutex> lock(logMutex);
                        logMessages.push_back(message);
                    }
                    break;
                }
                case 2: {
                    stateNodePacket snp;
                    packet >> snp.nodeId >> snp.state; // Deserialize the stateNodePacket
                    std::cout << "Received stateNodePacket: "
                        << "nodeId=" << snp.nodeId
                        << ", state=" << snp.state << std::endl;
                    std::string message = "Received stateNodePacket: nodeId=" + std::to_string(snp.nodeId) + ", state=" + snp.state;
                    {
                        std::lock_guard<std::mutex> lock(logMutex);
                        logMessages.push_back(message);
                    }
                    break;
                }
                case 3: {
                    positionPacket pp;
                    packet >>pp.nodeId>> pp.classNode>> pp.coordinates.first>> pp.coordinates.second; // Deserialize the positionPacket
                    std::cout << "Received positionPacket: "
                        << "nodeId=" << pp.nodeId
                        << ", classNode=" << pp.classNode
                        << "coordinates=(" << pp.coordinates.first
                        << ", " << pp.coordinates.second << ")" << std::endl;

                    {
                        std::lock_guard<std::mutex> lock(deviceMutex);
                        // Update the device position
                        //TODO: adapt the magnitude in the simulator to the relative magnitude in the visualisator
                        std::unique_ptr<Device> device = std::make_unique<Device>(pp.nodeId, pp.classNode, pp.coordinates);
                        manager.addDevice(std::move(device));
                    }

                    std::string message = "Received positionPacket: nodeId=" + std::to_string(pp.nodeId) + ", coordinates=(" + std::to_string(pp.coordinates.first) + ", " + std::to_string(pp.coordinates.second) + ")";
                    {
                        std::lock_guard<std::mutex> lock(logMutex);
                        logMessages.push_back(message);
                    }
                    break;
                }
                case 4: {
                    transmitMessagePacket tmp;
                    packet >> tmp.senderId >> tmp.receiverId; // Deserialize the transmitMessagePacket
                    std::cout << "Received transmitMessagePacket: "
                        << "senderId=" << tmp.senderId
                        << ", receiverId=" << tmp.receiverId << std::endl;
                    std::string message = "Received transmitMessagePacket: senderId=" + std::to_string(tmp.senderId) + ", receiverId=" + std::to_string(tmp.receiverId);
                    {
                        std::lock_guard<std::mutex> lock(logMutex);
                        logMessages.push_back(message);
                    }

                    break;
                }
                case 5: {
                    receiveMessagePacket rmp;
                    packet >> rmp.senderId >> rmp.receiverId >> rmp.state; // Deserialize the receiveMessagePacket
                    std::cout << "Received receiveMessagePacket: "
                        << "senderId=" << rmp.senderId
                        << ", receiverId=" << rmp.receiverId
                        << ", state=" << rmp.state << std::endl;
                    
                    std::string message = "Received receiveMessagePacket: senderId=" + std::to_string(rmp.senderId) + ", receiverId=" + std::to_string(rmp.receiverId) + ", state=" + rmp.state;
                    {
                        std::lock_guard<std::mutex> lock(logMutex);
                        logMessages.push_back(message);
                    }
                    break;
                }
                case 6:{
                    routingDecisionPacket rp;
                    packet >> rp.receiverId >> rp.senderId>>rp.newRoute;
                    std::cout << "Received routingDecisionPacket: "
                        << "receiverId=" << rp.receiverId
                        << ", senderId=" << rp.senderId
                        << ", newRoute=" << rp.newRoute << std::endl; 
                    std::string message = "Received routingDecisionPacket: receiverId=" + std::to_string(rp.receiverId) + ", senderId=" + std::to_string(rp.senderId) + ", newRoute=" + std::to_string(rp.newRoute);
                    {
                        std::lock_guard<std::mutex> lock(logMutex);
                        logMessages.push_back(message);
                    }
                    break;
                }
                case 7: {
                    broadcastMessagePacket bmp;
                    packet >> bmp.nodeId; // Deserialize the broadcastMessagePacket
                    std::cout << "Received broadcastMessagePacket: "
                        << "nodeId=" << bmp.nodeId << std::endl;
                    std::string message = "Received broadcastMessagePacket: nodeId=" + std::to_string(bmp.nodeId);
                    {
                        std::lock_guard<std::mutex> lock(logMutex);
                        logMessages.push_back(message);
                    }
                    break;
                }
                default:
                    std::cerr << "Unknown packet type: " << packetType << std::endl;
                    break;
                }
            }
            }
        }

        // Small delay to reduce CPU usage
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
 }
