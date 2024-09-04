#include "Window.hpp"
#include <SDL_image.h>
#include <iostream>

Window::Window(const std::string& title, int width, int height)
    : _title(title), _width(width), _height(height) {
    _closed = !init();
}

Window::~Window() {
    if (_texture) {
        SDL_DestroyTexture(_texture);
    }
    if (_renderer) {
        SDL_DestroyRenderer(_renderer);
    }
    if (_window) {
        SDL_DestroyWindow(_window);
    }
    SDL_Quit();
    IMG_Quit();
}

bool Window::init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return false;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0) {
        std::cerr << "IMG_Init Error: " << IMG_GetError() << std::endl;
        return false;
    }

    _window = SDL_CreateWindow(_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _width, _height, 0);
    if (!_window) {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        return false;
    }

    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    if (!_renderer) {
        std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void Window::pollEvents() {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                _closed = true;
                break;
            default:
                break;
        }
    }
}

bool Window::isClosed() const {
    return _closed;
}

void Window::clear() const {
    SDL_RenderClear(_renderer);
}

void Window::renderImage(const std::string& imagePath, int x, int y, int width, int height) {
    SDL_Surface* surface = IMG_Load(imagePath.c_str());
    if (!surface) {
        std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
        return;
    }

    if (_texture) {
        SDL_DestroyTexture(_texture);
    }
    
    _texture = SDL_CreateTextureFromSurface(_renderer, surface);
    SDL_FreeSurface(surface);

    if (!_texture) {
        std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_Rect dstRect;
    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = width;
    dstRect.h = height;

    SDL_RenderClear(_renderer);
    SDL_RenderCopy(_renderer, _texture, nullptr, &dstRect);
    SDL_RenderPresent(_renderer);
}

void Window::renderGameObject(GameObject* gameObjects) {
    SDL_Surface* surface = IMG_Load(gameObjects->getImagePath().c_str());
    if (!surface) {
        std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
        return;
    }

    if (_texture) {
        SDL_DestroyTexture(_texture);
    }
    
    _texture = SDL_CreateTextureFromSurface(_renderer, surface);
    SDL_FreeSurface(surface);

    if (!_texture) {
        std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_Rect dstRect;
    dstRect.x = gameObjects->getX();
    dstRect.y = gameObjects->getY();
    dstRect.w = gameObjects->getWidth();
    dstRect.h = gameObjects->getHeight();

    SDL_RenderClear(_renderer);
    SDL_RenderCopy(_renderer, _texture, nullptr, &dstRect);
    SDL_RenderPresent(_renderer);

}
