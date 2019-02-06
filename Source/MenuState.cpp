/*
 * MenuState.cpp
 *
 *  Created on: 23 дек. 2018 г.
 *      Author: ivan
 */

#include <MenuState.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <Utility.hpp>
#include <ResourceIdentifiers.hpp>
#include <ResourceHolder.hpp>

MenuState::MenuState(StateStack& stack, Context context)
: State(stack, context)
, m_Options()
, m_OptionIndex(0)
{
	//Create links to our textures and fonts.
	sf::Texture& texture =
				context.m_Textures->get(Textures::TitleScreen);
	sf::Font& font = context.m_Fonts->get(Fonts::Main);


	m_BackgroundSprite.setTexture(texture);

	// A simple menu demonstration
	sf::Text playOption;
	playOption.setFont(font);
	playOption.setString("Play");
	centerOrigin(playOption);
	playOption.setPosition(context.m_Window->
							getView().getSize()/ 2.f);
	m_Options.push_back(std::move(playOption));

	sf::Text exitOption;
	exitOption.setFont(font);
	exitOption.setString("Exit");
	centerOrigin(exitOption);
	exitOption.setPosition(playOption.getPosition()
			+ sf::Vector2f(0.f, 50.f));
	m_Options.push_back(std::move(exitOption));


	updateOptionText();
}

void MenuState::draw()
{
	sf::RenderWindow& window = *getContext().m_Window;

	window.setView(window.getDefaultView());
	window.draw(m_BackgroundSprite);


	for(auto itr = m_Options.begin(); itr != m_Options.end(); ++itr)
	{
		window.draw(*itr);
	}
}

bool MenuState::update(sf::Time)
{
	return true;
}

bool MenuState::handleEvent(const sf::Event& event)
{
	// The demonstration menu logic
	if (event.type != sf::Event::KeyPressed)
		return false;

	if (event.key.code == sf::Keyboard::Return)
	{
		if (m_OptionIndex == OptionNames::Play)
		{
			requestStackPop();
			requestStackPush(StatesID::Game);
		}
		else if (m_OptionIndex == OptionNames::Exit)
		{
			// The exit option was chosen, by removing itself, the stack will be empty, and the game will know it is time to close.
			requestStackPop();
		}
	}

	else if (event.key.code == sf::Keyboard::Up)
	{
		// Decrement and wrap-around
		if (m_OptionIndex > 0)
			m_OptionIndex--;
		else
			m_OptionIndex = m_Options.size() - 1;

		updateOptionText();
	}

	else if (event.key.code == sf::Keyboard::Down)
	{
		// Increment and wrap-around
		if (m_OptionIndex < m_Options.size() - 1)
			m_OptionIndex++;
		else
			m_OptionIndex = 0;

		updateOptionText();
	}

	return true;
}

void MenuState::updateOptionText()
{
	if (m_Options.empty())
		return;

	// White all texts
	for(auto itr = m_Options.begin(); itr != m_Options.end(); ++itr)
		{
			(*itr).setColor(sf::Color::White);

			(*itr).setScale(0.5, 0.5);
		}

	m_Options[m_OptionIndex].setScale(2, 2);
	// Red the selected text
	m_Options[m_OptionIndex].setColor(sf::Color::Yellow);

}
