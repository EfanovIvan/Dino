/*
 * PassedLevel.cpp
 *
 *  Created on: 24 февр. 2019 г.
 *      Author: ivan
 */

#include <PassedLevel.hpp>
#include <iostream>
PassedLevel::PassedLevel(StateStack& stack, Context context)
						: State(stack, context)
						, m_LableText()
						, m_OptionIndex(0)
{
	m_BackgroundSprite.setTexture(
			context.m_Textures->get(Textures::TitleScreen));
	sf::Font& font = context.m_Fonts->get(Fonts::Main);
	m_LableText.setFont(font);
	m_LableText.setString("Level passed");
	centerOrigin(m_LableText);
	m_LableText.setPosition(context.m_Window->getView().getSize().x/ 2
				,context.m_Window->getView().getSize().y/2 - 300 );
	m_LableText.scale(2.5,2.5);
	std::cout << "passed" << std::endl;
	sf::Text playOption;
	playOption.setFont(font);
	playOption.setString("NextLevel");
	centerOrigin(playOption);
	playOption.setPosition(context.m_Window->
							getView().getSize()/ 2.f);
	m_Options[0] = (std::move(playOption));

	sf::Text exitOption;
	exitOption.setFont(font);
	exitOption.setString("Exit");
	centerOrigin(exitOption);
	exitOption.setPosition(playOption.getPosition()
			+ sf::Vector2f(0.f, 50.f));
	m_Options[1] = (std::move(exitOption));
	updateOptionText();
}
void PassedLevel::draw()
{
	sf::RenderWindow& window = *getContext().m_Window;

	window.setView(window.getDefaultView());
	window.draw(m_BackgroundSprite);
	window.draw(m_LableText);

	for(auto itr = m_Options.begin(); itr != m_Options.end(); ++itr)
	{
		window.draw(*itr);
	}
}

bool PassedLevel::update(sf::Time)
{
	return true;
}

bool PassedLevel::handleEvent(const sf::Event& event)
{
	// The demonstration menu logic
	if (event.type != sf::Event::KeyPressed)
		return false;

	if (event.key.code == sf::Keyboard::Return)
	{
		if (m_OptionIndex == OptionNames::NextLevel)
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

void PassedLevel::updateOptionText()
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
