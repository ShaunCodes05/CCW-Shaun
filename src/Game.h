
#ifndef SFML_GAME_H
#define SFML_GAME_H

#include <SFML/Graphics.hpp>
#include "Game.h"

class Game
{

 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void mouseButtonPressed(const sf::Event::MouseButtonPressed* event);
  void mouseButtonReleased(const sf::Event::MouseButtonReleased* event);
  void keyPressed(const sf::Event::KeyPressed* event);
  void keyReleased(const sf::Event::KeyReleased* event);
  void newAnimal();


  

 private:
  sf::RenderWindow& window;
  
  sf::Texture background_texture{"../Data/Images/WhackaMole Worksheet/background.png"};
  sf::Sprite background = sf::Sprite(background_texture);

 //game code
  sf::Sprite* character;
  sf::Sprite* passport;

  sf::Texture* animals = new sf::Texture[3];
  sf::Texture* passports = new sf::Texture[3];


  sf::Font font{ "../Data/Fonts/OpenSans-Bold.ttf" };
  
  bool in_menu;

  sf::Text title_text{ font };
  sf::Text play_option{ font };
  sf::Text quit_option{ font };
  
  bool play_selected = true;
  bool should_accpet = true;
};

#endif // SFML_GAME_H
