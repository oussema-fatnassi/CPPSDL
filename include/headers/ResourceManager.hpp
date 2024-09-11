#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <iostream>

class ResourceManager {
private:
    ResourceManager();                                      // Constructor (private for singleton pattern)
    ResourceManager(const ResourceManager&);                // Copy constructor
    ResourceManager& operator=(const ResourceManager&);     // Assignment operator

    std::unordered_map<std::string, sf::Texture> textures;  // Container for textures

public:
    static ResourceManager& getInstance();                  // Get instance of ResourceManager (singleton)
    sf::Texture* getTexture(const std::string& filepath);   // Get texture by file path
};

#endif // RESOURCEMANAGER_HPP
