#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SDL.h>
#include <string>

class Window {
public:
    Window(const std::string& title, int width, int height);
    ~Window();

    void pollEvents();
    bool isClosed() const;

    void clear() const;
    void renderImage(const std::string& imagePath, int x, int y, int width, int height);

private:
    bool init();
    
    std::string _title;
    int _width = 800;
    int _height = 600;

    bool _closed = false;

    SDL_Window* _window = nullptr;
    SDL_Renderer* _renderer = nullptr;
    SDL_Texture* _texture = nullptr;
};

#endif
