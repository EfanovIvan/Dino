/*
 * IdleState.cpp
 *
 *  Created on: 2 февр. 2019 г.
 *      Author: ivan
 */

#include <IdleState.hpp>
#include <WalkState.hpp>

#include <JumpState.hpp>
IdleState::IdleState()
{
	m_GraphicState = GraphicState::IDLE;
}
EntityState* IdleState::handleEvent(MainGero& gero, const sf::Event& event)
{


if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)
				&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		gero.walk();
		return new WalkState;

	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)
				&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		gero.walkLeft();
		return new WalkState;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
			gero.jump();
			return new JumpState;

	}
	else
	{
		return nullptr;
	}

}

EntityState::GraphicState IdleState::state()
{
	return m_GraphicState;
}

