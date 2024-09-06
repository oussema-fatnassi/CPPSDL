#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <../sdl/SDL.h>
#include <../sdl/SDL_ttf.h>
#include <../sdl/SDL_image.h>
#include <string>

using namespace std;

class Window {
public:
    Window(const string& title, int width, int height);
    ~Window();

    void pollEvents();
    bool isClosed() const;

    void clear() const;
    void present() const;
    void renderImage(const string& imagePath, int x, int y, int width, int height);
    SDL_Renderer* getRenderer() const;

private:
    bool init();
    
    string title;
    int width;
    int height;
    bool closed = false;

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
};

#endif
