#include "ResourceManager.hpp"

ResourceManager::ResourceManager() {}   // Constructor

ResourceManager::ResourceManager(const ResourceManager&) {} // Copy constructor

ResourceManager& ResourceManager::operator=(const ResourceManager&) {  // Assignment operator
    return *this;
}

ResourceManager& ResourceManager::getInstance() {   // Singleton instance
    static ResourceManager instance;  // static instance of ResourceManager
    return instance;
}

sf::Texture* ResourceManager::getTexture(const std::string& filepath) {   // Get texture method
    // Check if texture is already loaded
    auto search = textures.find(filepath);
    if (search != textures.end()) {   // If texture is found, return it
        return &search->second;
    } else {   // If texture is not found, load it
        sf::Texture texture;
        if (!texture.loadFromFile(filepath)) {
            std::cerr << "Failed to load texture: " << filepath << std::endl;
            return nullptr;
        } else {
            textures.insert(std::make_pair(filepath, texture));   // Insert loaded texture
            std::cout << "Loaded texture: " << filepath << std::endl;
            return &textures[filepath];  // Return the newly loaded texture
        }
    }
}
