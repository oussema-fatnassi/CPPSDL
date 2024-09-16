#include "ResourceManager.hpp"

ResourceManager::ResourceManager(){}                                                // Constructor

ResourceManager:: ResourceManager(ResourceManager const&){}                         // Copy constructor      

ResourceManager ResourceManager :: operator=(ResourceManager const& rhs){           // Assignment operator
    return *this;
}

ResourceManager& ResourceManager::getInstance(){                                    // Get instance method
    static ResourceManager* instance = new ResourceManager();
    return *instance;
}

SDL_Surface* ResourceManager::getSurface(string filepath) {                         // Get surface method           
    auto search = surfaces.find(filepath);                                          // Search for surface in map
    if (search != surfaces.end()) {                                                 // If surface is found, return it
        return surfaces[filepath];
    } else {                                                                        // If surface is not found, load it             
        SDL_Surface* surface = IMG_Load(filepath.c_str());  
        if (!surface) {
            cerr << "Failed to load image: " << IMG_GetError() << endl;
        } else {
            surfaces.insert(make_pair(filepath, surface));
        }
        return surface;
    }
}
