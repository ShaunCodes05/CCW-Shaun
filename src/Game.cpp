
#include "Game.h"
#include <iostream>
#include <sstream>

// to do list 
// 1. fix texture and button overlap (kinda done)
// 2 make button pressed show on passport 
// 3 allow passport to be dragged to animal to progress to next animal instead of clicking buttons (bounding boxes)
// 4 maybe add timer idk prob drop idea 




Game::Game(sf::RenderWindow& game_window)
	: window(game_window)
{
	srand(time(NULL));
}

Game::~Game()
{
	delete[] animals;
	delete[] passports;
	delete character;
	delete passport;
	delete accept_btn;
	delete reject_btn;
	delete accept_label;
	delete reject_label;
}

bool Game::init()
{
	//game code
	animals = new sf::Texture[3];
	passports = new sf::Texture[3];

	animals[2].loadFromFile("../Data/Images/Critter Crossing/penguin.png");
	animals[1].loadFromFile("../Data/Images/Critter Crossing/elephant.png");
	animals[0].loadFromFile("../Data/Images/Critter Crossing/moose.png");
	character = new sf::Sprite(animals[0]);

	passports[2].loadFromFile("../Data/Images/Critter Crossing/penguin passport.png");
	passports[1].loadFromFile("../Data/Images/Critter Crossing/elephant passport.png");
	passports[0].loadFromFile("../Data/Images/Critter Crossing/moose passport.png");
	passport = new sf::Sprite(passports[0]);

	// button textures
	reject_button.loadFromFile("../Data/Images/Critter Crossing/reject button.png");
	accept_button.loadFromFile("../Data/Images/Critter Crossing/accept button.png");
	reject_texture.loadFromFile("../Data/Images/Critter Crossing/reject.png");
	accept_texture.loadFromFile("../Data/Images/Critter Crossing/accept.png");

	reject_btn = new sf::Sprite(reject_button);
	accept_btn = new sf::Sprite(accept_button);

	reject_label = new sf::Sprite(reject_texture);
	accept_label = new sf::Sprite(accept_texture);

	reject_btn->setScale({ 0.5f, 0.5f });
	accept_btn->setScale({ 0.5f, 0.5f });

	reject_label->setScale({ 0.4f, 0.4f });
	accept_label->setScale({ 0.4f, 0.4f });

	
	float padding = 20.f;
	float spacing = 20.f;

	float reject_y = window.getSize().y - reject_btn->getGlobalBounds().size.y - padding;
	float accept_y = reject_y - accept_btn->getGlobalBounds().size.y - spacing;

	reject_btn->setPosition({ padding, reject_y });
	accept_btn->setPosition({ padding, accept_y });

	reject_label->setPosition({ 1000.f,1000.f });
	accept_label->setPosition({ 1000.f,1000.f });

	newAnimal();
	character->setScale({ 0.5f,0.5f });



	//reject_label->setPosition(
		//reject_btn->getPosition() +
		//(reject_btn->getGlobalBounds().size - reject_label->getGlobalBounds().size) / 5.f
	//);
	//accept_label->setPosition(
		//accept_btn->getPosition() +
		//(accept_btn->getGlobalBounds().size - accept_label->getGlobalBounds().size) / 5.f
	//);

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

void Game::update(float dt)
{
	if (in_menu)
	{
		return;
	}

	if (passport->getGlobalBounds().findIntersection(character->getGlobalBounds()))
	{
		
		std::cout << "true";
	}

}

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
	window.draw(*passport);

	// buttons
	window.draw(*accept_btn);
	window.draw(*accept_label);
	window.draw(*reject_btn);
	window.draw(*reject_label);
}

void Game::mouseButtonPressed(const sf::Event::MouseButtonPressed* event)
{
	if (event->button == sf::Mouse::Button::Left)
	{
		sf::Vector2f mouse_pos(
			static_cast<float>(event->position.x),
			static_cast<float>(event->position.y)
		);

		
		if (accept_btn->getGlobalBounds().contains(mouse_pos))
		{
			if (should_accpet)
			{
				std::cout << "Correct! Accepted a matching passport.\n";
				score++;
			}
			else
			{
				std::cout << "Wrong! That passport didn't match.\n";
				mistakes++;
			}

			accept_label->setPosition({});

			newAnimal();
			return;
		}

		
		if (reject_btn->getGlobalBounds().contains(mouse_pos))
		{
			if (!should_accpet)
			{
				std::cout << "Correct! Rejected a mismatched passport.\n";
				score++;
			}
			else
			{
				std::cout << "Wrong! They actually matched.\n";
				mistakes++;
			}

			newAnimal();
			return;
		}

		if (passport->getGlobalBounds().contains(mouse_pos))
		{
			dragged = passport;
			drag_offset = mouse_pos - passport->getPosition();
		}
	}
}

void Game::mouseButtonReleased(const sf::Event::MouseButtonReleased* event)
{
	if (event->button == sf::Mouse::Button::Left)
	{
		dragged = nullptr;
	}
}

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

	if (event->scancode == sf::Keyboard::Scancode::W)
	{
		// W was pressed
	}
}

void Game::keyReleased(const sf::Event::KeyReleased* event)
{
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

	character->setTexture(animals[animal_index], true);
	character->setScale({ 1.8,1.8 });
	character->setPosition(sf::Vector2f(window.getSize().x / 12, window.getSize().y / 12));

	passport->setTexture(passports[passport_index]);
	passport->setScale({ 0.6,0.6 });
	passport->setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 3));
}

void Game::dragspirte(const sf::Event::MouseMoved* event)
{
	if (dragged != nullptr)
	{
		sf::Vector2f mouse_pos(
			static_cast<float>(event->position.x),
			static_cast<float>(event->position.y)
		);

		sf::Vector2f drag_possition = mouse_pos - drag_offset;
		dragged->setPosition(drag_possition);
	}
}

