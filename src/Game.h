
#ifndef SFML_GAME_H
#define SFML_GAME_H

#include <SFML/Graphics.hpp>
#include <array>

class Game
{
public:
    Game(sf::RenderWindow& window);
    ~Game();

    bool init();
    void update(float dt);
    void render();

    void mouseButtonPressed(
        const sf::Event::MouseButtonPressed* event);

    void mouseButtonReleased(
        const sf::Event::MouseButtonReleased* event);

    void keyPressed(const sf::Event::KeyPressed* event);
    void keyReleased(const sf::Event::KeyReleased* event);

    void newAnimal();

    void dragspirte(const sf::Event::MouseMoved* event);

private:
    sf::RenderWindow& window;

    // Background
    sf::Texture background_texture{"../Data/Images/WhackaMole Worksheet/background.png"};
    sf::Sprite background{ background_texture };

    // Animal & passport textures array test 
    std::array<sf::Texture, 3> animals;
    std::array<sf::Texture, 3> passports;

    // Sprites
    sf::Sprite* character = nullptr;
    sf::Sprite* passport = nullptr;

    // Button & stamp textures
    sf::Texture accept_button;
    sf::Texture reject_button;
    sf::Texture accept_texture;
    sf::Texture reject_texture;

    // Button & stamp sprites
    sf::Sprite* accept_btn = nullptr;
    sf::Sprite* reject_btn = nullptr;
    sf::Sprite* accept_label = nullptr;
    sf::Sprite* reject_label = nullptr;

    // Font & menu
    sf::Font font{ "../Data/Fonts/OpenSans-Bold.ttf" };

    bool in_menu = true;
    sf::Text title_text{ font };
    sf::Text play_option{ font };
    sf::Text quit_option{ font };

    bool play_selected = true;

    bool should_accpet = true;

    // Passport decision
    bool decision_made = false;
    bool decision_accept = false;

    // stamp
    sf::Sprite* current_label = nullptr;

    // Dragging
    sf::Sprite* dragged = nullptr;
    sf::Vector2f drag_offset;
    sf::Vector2f passport_home_position;

    // Score
    int score = 0;
    int mistakes = 0;

    // btn toggle test
    bool show_decision_buttons = false;
};

#endif // SFML_GAME_H
