#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <../sdl/SDL.h>
#include <../sdl/SDL_image.h>
#include <../sdl/SDL_ttf.h>
#include <iostream>
#include <string>
using namespace std;

class Window {                                          // Window class used for creating the game window and handling rendering
public:
    Window(const string& title, int width, int height); // Constructor
    ~Window();                                          // Destructor     

    void pollEvents();                                  // Public methods          
    bool isClosed() const;
    void clear() const;
    void present() const;
    void renderImage(const string& imagePath, int x, int y, int width, int height);

    SDL_Renderer* getRenderer() const;                  // Getters  

private:
    bool init();                                        // Private methods
    
    string title;                                       // Member variables    
    int width, height;
    bool closed = false;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
};

#endif
