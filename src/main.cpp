#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"


int main()
{
  std::cout << "You should see a window that opens as well as this writing to console..."
            << std::endl;

  // create window and set up
  sf::RenderWindow window(sf::VideoMode({ 1080, 720 }), "SFML game");
  window.setFramerateLimit(60);

  //initialise an instance of the game class
  Game game(window);

  //run the init function of the game class and check it all initialises ok
  if (!game.init())
  {
      return 0;
  }

  // A Clock starts counting as soon as it's created
  sf::Clock clock;

  // Game loop: run the program as long as the window is open
  while (window.isOpen())
  {
    //calculate delta time dt = time between the last loop and this one
    sf::Time time = clock.restart();
    float dt = time.asSeconds();

    //'process inputs' element of the game loop
    while (const std::optional event = window.pollEvent())
    {
        //Close was requested, close the window (e.g. player clicks the window's close button)
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }

        //A Key was pressed, put the information in a KeyPressed event and send it to a game function to be handled
        else if (const sf::Event::KeyPressed* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            game.keyPressed(keyPressed);
        }

        //A Key was released, put the information in a KeyReleased event and send it to a game function to be handled
        else if (const sf::Event::KeyReleased* keyReleased = event->getIf<sf::Event::KeyReleased>())
        {
            game.keyReleased(keyReleased);
        }

        //A Mouse button was pressed, put the information in a MouseButtonPressed event and send it to a game function to be handled
        else if (const sf::Event::MouseButtonPressed* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
        {
            game.mouseButtonPressed(mousePressed);
        }

        //A Mouse button was released, put the information in a MouseButtonPressed event and send it to a game function to be handled
        else if (const sf::Event::MouseButtonReleased* mouseReleased = event->getIf<sf::Event::MouseButtonReleased>())
        {
            game.mouseButtonReleased(mouseReleased);
        }
        if (const auto* e = event->getIf<sf::Event::MouseMoved>()) game.dragspirte(e);       
    }

    //'update' element of the game loop
    game.update(dt);    

    //'render' element of the game loop
    window.clear(sf::Color::Black);
    game.render();
    window.display();
  }

  return 0;
}
