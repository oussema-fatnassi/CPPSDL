// #ifndef RESOURCEMANAGER_HPP
// #define RESOURCEMANAGER_HPP

// #include <../sdl/SDL.h>
// #include <../sdl/SDL_image.h>
// #include <string>
// #include <unordered_map>
// #include <iostream>
// using namespace std;

// class ResourceManager {                                         // ResourceManager class used for managing resources, to be loaded only once (images)
//     private:
//         ResourceManager();                                      // Constructor
//         ResourceManager(ResourceManager const&);                // Copy constructor
//         ResourceManager operator = (ResourceManager const&);    // Assignment operator
//         unordered_map<string, SDL_Surface*> surfaces;

//     public:
//         static ResourceManager& getInstance();                  // Getters
//         SDL_Surface* getSurface(string filepath);
// };
// #endif // RESOURCEMANAGER_HPP