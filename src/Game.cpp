
#include "Game.h"

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
    : window(game_window)
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

Game::~Game()
{
    delete character;
    delete passport;

    delete accept_btn;
    delete reject_btn;

    delete accept_label;
    delete reject_label;
}

bool Game::init()
{
    // Load animal textures
    if (!animals[0].loadFromFile(
        "../Data/Images/Critter Crossing/moose.png") ||
        !animals[1].loadFromFile(
            "../Data/Images/Critter Crossing/elephant.png") ||
        !animals[2].loadFromFile(
            "../Data/Images/Critter Crossing/penguin.png"))
    {
        std::cerr << "Failed to load animal textures.\n";
        return false;
    }

    // Load passport textures
    if (!passports[0].loadFromFile(
        "../Data/Images/Critter Crossing/moose passport.png") ||
        !passports[1].loadFromFile(
            "../Data/Images/Critter Crossing/elephant passport.png") ||
        !passports[2].loadFromFile(
            "../Data/Images/Critter Crossing/penguin passport.png"))
    {
        std::cerr << "Failed to load passport textures.\n";
        return false;
    }

    // Load button and stamp textures
    if (!reject_button.loadFromFile(
        "../Data/Images/Critter Crossing/reject button.png") ||
        !accept_button.loadFromFile(
            "../Data/Images/Critter Crossing/accept button.png") ||
        !reject_texture.loadFromFile(
            "../Data/Images/Critter Crossing/reject.png") ||
        !accept_texture.loadFromFile(
            "../Data/Images/Critter Crossing/accept.png"))
    {
        std::cerr << "Failed to load button or stamp textures.\n";
        return false;
    }

    // Create sprites
    character = new sf::Sprite(animals[0]);
    passport = new sf::Sprite(passports[0]);

    reject_btn = new sf::Sprite(reject_button);
    accept_btn = new sf::Sprite(accept_button);

    reject_label = new sf::Sprite(reject_texture);
    accept_label = new sf::Sprite(accept_texture);

    // Scale buttons and stamps
    reject_btn->setScale({ 0.5f, 0.5f });
    accept_btn->setScale({ 0.5f, 0.5f });

    reject_label->setScale({ 0.4f, 0.4f });
    accept_label->setScale({ 0.4f, 0.4f });

    // Position buttons on the left side
    /*const float padding = 20.f;
    const float spacing = 20.f;

    const float reject_y =
        static_cast<float>(window.getSize().y)
        - reject_btn->getGlobalBounds().size.y
        - padding;

    const float accept_y =
        reject_y
        - accept_btn->getGlobalBounds().size.y
        - spacing;

    reject_btn->setPosition({ padding, reject_y });
    accept_btn->setPosition({ padding, accept_y });*/

    // pos button toggle test 
    float padding = 20.f;
    float spacing = 20.f;

    float right_x = static_cast<float>(window.getSize().x)
        - accept_btn->getGlobalBounds().size.x
        - padding;

    float reject_y = static_cast<float>(window.getSize().y)
        - reject_btn->getGlobalBounds().size.y
        - padding;

    float accept_y = reject_y
        - accept_btn->getGlobalBounds().size.y
        - spacing;

    reject_btn->setPosition({ right_x, reject_y });
    accept_btn->setPosition({ right_x, accept_y });

    // Hide stamps until a decision is made
    accept_label->setPosition({ 1000.f, 1000.f });
    reject_label->setPosition({ 1000.f, 1000.f });

    // Menu title
    title_text.setString("Critter Crossing");
    title_text.setFillColor(sf::Color::White);
    title_text.setCharacterSize(70);
    title_text.setPosition({ 200.f, 100.f });

    // Menu options
    const unsigned int option_size =static_cast<unsigned int>(std::clamp(static_cast<float>(window.getSize().y) * 0.06f,16.f,120.f));

    play_option.setString("> Play <");
    play_option.setCharacterSize(option_size);
    play_option.setPosition({ 200.f, 350.f });

    quit_option.setString("Quit");
    quit_option.setCharacterSize(option_size);
    quit_option.setPosition({ 800.f, 350.f });

    play_selected = true;
    in_menu = true;

    newAnimal();

    return true;
}

void Game::update(float dt)
{
    // Gameplay updates can go here later maybe.
	// Passport sub is in mouse button released and dragspirte functions for now dont forget.
    (void)dt;
}

void Game::render()
{
    window.draw(background);

    if (in_menu)
    {
        window.draw(title_text);
        window.draw(play_option);
        window.draw(quit_option);
        return;
    }

    // Draw animal and passport
    window.draw(*character);
    window.draw(*passport);


    if (current_label != nullptr)
    {
        window.draw(*current_label);
    }

    if (show_decision_buttons)
    {
        window.draw(*accept_btn);
        window.draw(*reject_btn);
    }
}


void Game::mouseButtonPressed(
    const sf::Event::MouseButtonPressed* event)
{
    if (in_menu)
    {
        return;
    }

    if (event->button == sf::Mouse::Button::Right)
    {
        show_decision_buttons = !show_decision_buttons;
        return;
    }

    if (event->button != sf::Mouse::Button::Left)
    {
        return;
    }

    const sf::Vector2f mouse_pos(
        static_cast<float>(event->position.x),
        static_cast<float>(event->position.y)
    );

    // ACCEPT
    if (show_decision_buttons &&
        accept_btn->getGlobalBounds().contains(mouse_pos))
    {
        decision_made = true;
        decision_accept = true;
        current_label = accept_label;

        const auto passport_bounds =
            passport->getGlobalBounds();

        const auto stamp_size =
            current_label->getGlobalBounds().size;

        current_label->setPosition({
            passport_bounds.position.x +
                (passport_bounds.size.x - stamp_size.x) / 2.f,

            passport_bounds.position.y +
                (passport_bounds.size.y - stamp_size.y) / 2.f
            });

        std::cout << "Passport stamped: ACCEPT\n";
        return;
    }

    // REJECT
    if (show_decision_buttons &&
        reject_btn->getGlobalBounds().contains(mouse_pos))
    {
        decision_made = true;
        decision_accept = false;
        current_label = reject_label;

        const auto passport_bounds =
            passport->getGlobalBounds();

        const auto stamp_size =
            current_label->getGlobalBounds().size;

        current_label->setPosition({
            passport_bounds.position.x +
                (passport_bounds.size.x - stamp_size.x) / 2.f,

            passport_bounds.position.y +
                (passport_bounds.size.y - stamp_size.y) / 2.f
            });

        std::cout << "Passport stamped: REJECT\n";
        return;
    }

    if (decision_made &&
        passport->getGlobalBounds().contains(mouse_pos))
    {
        dragged = passport;

        drag_offset = mouse_pos - passport->getPosition();
    }
}


void Game::mouseButtonReleased(
    const sf::Event::MouseButtonReleased* event)
{
    if (event->button != sf::Mouse::Button::Left)
    {
        return;
    }

    if (dragged == passport && decision_made)
    {
        const bool dropped_on_animal =
            passport->getGlobalBounds().findIntersection(
                character->getGlobalBounds()
            ).has_value();

        if (dropped_on_animal)
        {
  
            if (decision_accept == should_accpet)
            {
                ++score;
                std::cout << "Correct decision!\n";
            }
            else
            {
                ++mistakes;
                std::cout << "Wrong decision!\n";
            }

            std::cout << "Score: " << score
                << " | Mistakes: " << mistakes << '\n';

            dragged = nullptr;
            newAnimal();
            return;
        }

        passport->setPosition(passport_home_position);


        if (current_label != nullptr)
        {
            const auto passport_bounds =
                passport->getGlobalBounds();

            const auto stamp_size =
                current_label->getGlobalBounds().size;

            current_label->setPosition({
                passport_bounds.position.x +
                    (passport_bounds.size.x - stamp_size.x) / 2.f,

                passport_bounds.position.y +
                    (passport_bounds.size.y - stamp_size.y) / 2.f
                });
        }
    }

    dragged = nullptr;
}

void Game::dragspirte(const sf::Event::MouseMoved* event)
{
    if (in_menu || dragged != passport)
    {
        return;
    }

    const sf::Vector2f mouse_pos(
        static_cast<float>(event->position.x),
        static_cast<float>(event->position.y)
    );

    // Move the passport with the mouse
    passport->setPosition(mouse_pos - drag_offset);

    // Move the stamp with the passport
    if (current_label != nullptr)
    {
        const auto passport_bounds =
            passport->getGlobalBounds();

        const auto stamp_size =
            current_label->getGlobalBounds().size;

        current_label->setPosition({
            passport_bounds.position.x +
                (passport_bounds.size.x - stamp_size.x) / 2.f,

            passport_bounds.position.y +
                (passport_bounds.size.y - stamp_size.y) / 2.f
            });
    }
}

void Game::keyPressed(const sf::Event::KeyPressed* event)
{
    if (in_menu)
    {
        if (event->scancode == sf::Keyboard::Scancode::Left ||
            event->scancode == sf::Keyboard::Scancode::Right)
        {
            play_selected = !play_selected;

            if (play_selected)
            {
                play_option.setString("> Play <");
                quit_option.setString("Quit");
            }
            else
            {
                play_option.setString("Play");
                quit_option.setString("> Quit <");
            }
        }
        else if (event->scancode == sf::Keyboard::Scancode::Enter)
        {
            if (play_selected)
            {
                in_menu = false;
            }
            else
            {
                window.close();
            }
        }
    }
}

void Game::keyReleased(const sf::Event::KeyReleased* event)
{
    // void func test 
    (void)event;
}

void Game::newAnimal()
{
    // Reset the previous decision and stamp
    decision_made = false;
    decision_accept = false;
    current_label = nullptr;
    dragged = nullptr;

    accept_label->setPosition({ 1000.f, 1000.f });
    reject_label->setPosition({ 1000.f, 1000.f });

    // Randomly select the animal and passport
    const int animal_index = std::rand() % 3;
    const int passport_index = std::rand() % 3;

    // The passport matche check
    should_accpet = (animal_index == passport_index);

    character->setTexture(animals[animal_index], true);
    character->setScale({ 1.8f, 1.8f });

    character->setPosition({
        static_cast<float>(window.getSize().x) / 12.f,
        static_cast<float>(window.getSize().y) / 12.f
        });

    passport->setTexture(passports[passport_index], true);
    passport->setScale({ 0.6f, 0.6f });

    // Remember the original passport pos
    passport_home_position = {
        static_cast<float>(window.getSize().x) / 2.f,
        static_cast<float>(window.getSize().y) / 3.f
    };

    passport->setPosition(passport_home_position);
}
