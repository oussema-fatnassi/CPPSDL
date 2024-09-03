#include "../include/headers/Window.hpp"

Window::Window(const char *title, int width, int height)
{
    m_isClosed = false;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        m_isClosed = true;
        return;
    }

    m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_ALLOW_HIGHDPI);

    if (m_window == NULL)
    {
        std::cerr << "Could not create window: " << SDL_GetError() << std::endl;
        m_isClosed = true;
        return;
    }
}

Window::~Window()
{
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

bool Window::isClosed() const
{
    return m_isClosed;
}

void Window::pollEvents()
{
    SDL_Event windowEvent;

    while (SDL_PollEvent(&windowEvent))
    {
        if (SDL_QUIT == windowEvent.type)
        {
            m_isClosed = true;
        }
    }
}

