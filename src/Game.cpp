
#include "Game.h"
#include <iostream>
#include <sstream>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL)); //seeds random number generator with the current time
}

Game::~Game()
{
	delete[] animals;
	delete[] passport;
	delete character;
	delete passport;

}

// We call this once after the game class is instantiated
bool Game::init()
{
	
	//game code
	animals[0].loadFromFile("../Data/Images/Critter Crossing/moose.png");
	character = new sf::Sprite(animals[0]);
	passports[0].loadFromFile("../Data/Images/Critter Crossing/moose passport.png");
	passport = new sf::Sprite(passports[0]);



	//menu code
	title_text.setString("Main Text");
	title_text.setFont(font);
	title_text.setFillColor(sf::Color(255, 255, 255, 255));
	const unsigned int baseCharSize = 100u;
	title_text.setCharacterSize(baseCharSize);
	title_text.setPosition({ 300.f, 100.f });

	//play and quit options 
	unsigned int optionSize = static_cast<unsigned int>(
		std::clamp(window.getSize().y * 0.06f, 16.f, 120.f));
	play_option.setFont(font);
	play_option.setString("Play");
	play_option.setCharacterSize(optionSize);
	play_option.setPosition({ 200.f,350.f });

	quit_option.setFont(font);
	quit_option.setString("Quit");
	quit_option.setCharacterSize(optionSize);
	quit_option.setPosition({ 800.f,350.f });
	

  return true;
}

// Update runs after event polling and before rendering
// use it for everything that needs to update between frames
void Game::update(float dt)
{
	if (in_menu)
	{
		return;
	}
}

// Runs after update, use it to tell the window what to draw this frame
void Game::render()
{
	if (in_menu)
	{
		window.draw(title_text);
		window.draw(play_option);
		window.draw(quit_option);
		return;
	}

	window.draw(background);

	window.draw(*character);
}

//Called by event polling when a MouseButtonPressed event is found
void Game::mouseButtonPressed(const sf::Event::MouseButtonPressed* event)
{
	// Event contains mouse position and which button was clicked

	// Don't need to extract position to a variable like this, this is just to show you it's a Vector2i
	sf::Vector2i position = event->position;

	// You can tell which button was pressed by comparing it to SFML's definitions of mouse buttons
	if (event->button == sf::Mouse::Button::Left)
	{
		//Left mouse button was pressed
	}
}

//Called by event polling when a MouseButtonReleased event is found
void Game::mouseButtonReleased(const sf::Event::MouseButtonReleased* event)
{
	//Works the same as MouseButtonPressed
	if (event->button == sf::Mouse::Button::Left)
	{
		//Left mouse button was released
	}
}

// Called by event polling when a KeyPressed event is found
void Game::keyPressed(const sf::Event::KeyPressed* event)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)))
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

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
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
	
	// You can tell which button was pressed by the scancode to SFML's definitions of keyboard keys
	if (event->scancode == sf::Keyboard::Scancode::W)
	{
		//play_option.setString(">Play<");
	}

}

// Called by event polling when a KeyReleased event is found
void Game::keyReleased(const sf::Event::KeyReleased* event)
{
	// Works the same way as KeyPressed
	if (event->scancode == sf::Keyboard::Scancode::W)
	{
		// W was released
	}

}


void Game::newAnimal()
{
	int animal_index = rand() % 3;
	int passport_index = rand() % 3;

	if (animal_index == passport_index)
	{
		should_accpet = true;
	}
	else
	{
		should_accpet = false;
	}

	character->setTexture();

}