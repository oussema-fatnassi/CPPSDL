#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SFML/Graphics.hpp>
#include <string>

class Window {
public:
    Window(const std::string& title, int width, int height);  // Constructor
    ~Window();                                                // Destructor

    void pollEvents();                                        // Poll events (e.g., close)
    bool isClosed() const;                                    // Check if the window is closed
    void clear();                                       // Clear the window
    void present();                                           // Display the window
    void renderImage(const std::string& imagePath, int x, int y, int width, int height);  // Render an image at the given position
    sf::RenderWindow& getRenderWindow();              // Get the SFML window object

private:
    bool init();                                              // Initialize window and resources

    sf::RenderWindow window;                                  // SFML window object
    sf::Texture texture;                                      // Texture object for rendering images
    sf::Sprite sprite;                                        // Sprite to display the texture
    bool closed;                                              // Track if the window is closed
    std::string title;                                        // Window title
    int width, height;                                        // Window dimensions
};

#endif // WINDOW_HPP
