#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

class ResourceManager {
private:
    ResourceManager();                                      // Constructor (private for singleton pattern)
    ResourceManager(const ResourceManager&);                // Copy constructor
    ResourceManager& operator=(const ResourceManager&);     // Assignment operator

    unordered_map<string, sf::Texture> textures;  // Container for textures

public:
    static ResourceManager& getInstance();                  // Get instance of ResourceManager (singleton)
    sf::Texture* getTexture(const string& filepath);   // Get texture by file path
};

#endif // RESOURCEMANAGER_HPP
