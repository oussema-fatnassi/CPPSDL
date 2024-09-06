#ifndef GAMEMANAGER_HPP
#define GAMEMANAGER_HPP

#include "UI.hpp"
#include "Menu.hpp"
#include "Window.hpp"
#include <SDL.h>

enum class GameState {
    MAIN_MENU,
    GAME_PLAY,
    GAME_OVER
};

class GameManager{
public:
    GameManager();
    ~GameManager();
    void init(Window* window);
    void run();

private:
    UI ui;
    Menu menu;
    Window* window;
    bool isRunning;
    GameState gameState;

    void handleEvents();
    void update();
    void render();
    
};



#endif // GAMEMANAGER_HPP