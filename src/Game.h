
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
  void dragspirte(const sf::Event::MouseMoved* event);


  

 private:
  sf::RenderWindow& window;
  
  sf::Texture background_texture{"../Data/Images/WhackaMole Worksheet/background.png"};
  sf::Sprite background = sf::Sprite(background_texture);

 //game code
  sf::Sprite* character;
  sf::Sprite* passport;
 
  
  sf::Texture* animals = new sf::Texture[3];
  sf::Texture* passports = new sf::Texture[3];
  sf::Texture accept_button;
  sf::Texture reject_button;
  sf::Texture accept_texture;
  sf::Texture reject_texture;

  // button
  sf::Sprite* accept_btn = nullptr;
  sf::Sprite* reject_btn = nullptr;
  sf::Sprite* accept_label = nullptr;
  sf::Sprite* reject_label = nullptr;

  sf::Font font{ "../Data/Fonts/OpenSans-Bold.ttf" };
  
  bool in_menu;

  sf::Text title_text{ font };
  sf::Text play_option{ font };
  sf::Text quit_option{ font };
  
  bool play_selected = true;
  bool should_accpet = true;

  sf::Sprite* dragged = nullptr;
  sf::Vector2f drag_offset;

  //score and mistakes w/e placeholder
  int score = 0;
  int mistakes = 0;
};

#endif // SFML_GAME_H
