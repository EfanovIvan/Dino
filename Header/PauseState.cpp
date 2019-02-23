/*
 * PauseState.cpp
 *
 *  Created on: 10 февр. 2019 г.
 *      Author: ivan
 */

#include <PauseState.hpp>
#include <Utility.hpp>
#include <ResourceHolder.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
PauseState::PauseState(StateStack& stack, Context context)
: State(stack, context)
, mBackgroundSprite()
, mPausedText()
, mInstructionText()
{
	std::cout << "creat pause" << std::endl;
	sf::Font& font = context.m_Fonts->get(Fonts::Main);
	sf::Vector2f viewSize = context.m_Window->getView().getSize();
	mBackgroundSprite.setTexture(context.m_Textures->
			get(Textures::TitleScreen));
	mPausedText.setFont(font);
	mPausedText.setString("Game Paused");
	mPausedText.setCharacterSize(70);
	centerOrigin(mPausedText);
	mPausedText.setPosition(0.5f * viewSize.x, 0.4f * viewSize.y);

	mInstructionText.setFont(font);
	mInstructionText.setString("(Press Backspace to return to the main menu)");
	centerOrigin(mInstructionText);
	mInstructionText.setPosition(0.5f * viewSize.x, 0.6f * viewSize.y);

}

void PauseState::draw()
{

	sf::RenderWindow& window = *getContext().m_Window;
	window.setView(window.getDefaultView());

	sf::RectangleShape backgroundShape;
	backgroundShape.setFillColor(sf::Color(0, 0, 0, 0));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(mPausedText);
	window.draw(mInstructionText);
}

bool PauseState::update(sf::Time)
{
	return false;
}

bool PauseState::handleEvent(const sf::Event& event)
{
	if (event.type != sf::Event::KeyPressed)
		return false;

	if (event.key.code == sf::Keyboard::Escape)
	{
		// Escape pressed, remove itself to return to the game
		requestStackPop();
	}

	if (event.key.code == sf::Keyboard::BackSpace)
	{
		// Escape pressed, remove itself to return to the game
		requestStateClear();
		requestStackPush(StatesID::Menu);
	}

	return false;
}
