#include "Window.hpp"
#include <iostream>

Window::Window(const string& title, int width, int height)
    : title(title), width(width), height(height) {
    closed = !init();
}

Window::~Window() {
    if (renderer) {
        SDL_DestroyRenderer(renderer);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
}

bool Window::init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cerr << "SDL_Init Error: " << SDL_GetError() << endl;
        return false;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0) {
        cerr << "IMG_Init Error: " << IMG_GetError() << endl;
        return false;
    }

    if (TTF_Init() == -1) {
        std::cerr << "TTF_Init Error: " << TTF_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (!window) {
        cerr << "Failed to create window: " << SDL_GetError() << endl;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        cerr << "Failed to create renderer: " << SDL_GetError() << endl;
        return false;
    }

    return true;
}

void Window::pollEvents() {
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            closed = true;
        }
    }
}

bool Window::isClosed() const {
    return closed;
}

void Window::clear() const {
    SDL_RenderClear(renderer);
}

void Window::present() const {
    SDL_RenderPresent(renderer);
}

void Window::renderImage(const string& imagePath, int x, int y, int width, int height) {
    SDL_Surface* surface = IMG_Load(imagePath.c_str());
    if (!surface) {
        cerr << "Failed to load image: " << IMG_GetError() << endl;
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (!texture) {
        cerr << "Failed to create texture: " << SDL_GetError() << endl;
        return;
    }

    SDL_Rect dstRect = {x, y, width, height};
    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
    SDL_DestroyTexture(texture);
}

SDL_Renderer* Window::getRenderer() const {
    return renderer;
}
