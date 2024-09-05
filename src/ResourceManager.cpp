#include "ResourceManager.hpp"
#include <iostream>

ResourceManager::ResourceManager(){}

ResourceManager:: ResourceManager(ResourceManager const&){}

ResourceManager ResourceManager :: operator=(ResourceManager const& rhs){
    return *this;
}

ResourceManager& ResourceManager::getInstance(){
    static ResourceManager* instance = new ResourceManager();
    return *instance;
}

SDL_Surface* ResourceManager::getSurface(string filepath) {
    auto search = surfaces.find(filepath);
    if (search != surfaces.end()) {
        return surfaces[filepath];
    } else {
        SDL_Surface* surface = IMG_Load(filepath.c_str());  
        if (!surface) {
            cerr << "Failed to load image: " << IMG_GetError() << endl;
        } else {
            surfaces.insert(make_pair(filepath, surface));
            cout << "Loaded image: " << filepath << endl;
        }
        return surface;
    }
}
