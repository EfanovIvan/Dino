/*
 * RunState.cpp
 *
 *  Created on: 2 февр. 2019 г.
 *      Author: ivan
 */

#include <RunState.hpp>
#include <JumpState.hpp>
#include <IdleState.hpp>
RunState::RunState()
{
	m_GraphicState = GraphicState::RUN;
}

EntityState* RunState::handleEvent(MainGero& gero,
									const sf::Event& event)
{

if (  (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) )
				&&(!sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) )
		{
			gero.idle();
			return new IdleState;
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			gero.jump();
			return new JumpState;
		}


}

EntityState::GraphicState RunState::state()
{
	return m_GraphicState;
}
