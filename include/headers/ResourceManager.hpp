#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <../sdl/SDL.h>
#include <../sdl/SDL_image.h>
#include <string>
#include <unordered_map>
using namespace std;

class ResourceManager {
    private:
        ResourceManager();                                  // Private constructor
        ResourceManager(ResourceManager const&);                // Copy constructor
        ResourceManager operator = (ResourceManager const&);    // Assignment operator
        unordered_map<string, SDL_Surface*> surfaces;

    public:
        static ResourceManager& getInstance();
        SDL_Surface* getSurface(string filepath);
};
#endif // RESOURCEMANAGER_HPP