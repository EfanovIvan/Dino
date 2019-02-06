/*
 * WalkState.cpp
 *
 *  Created on: 2 февр. 2019 г.
 *      Author: ivan
 */
#include <IdleState.hpp>
#include <WalkState.hpp>
#include <JumpState.hpp>
#include <RunState.hpp>
WalkState::WalkState()
{
	m_GraphicState = GraphicState::WALK;
}
EntityState* WalkState::handleEvent(MainGero& gero, const sf::Event& event)
{

if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			//&& (sf::Keyboard::isKeyPressed(sf::Keyboard::Right )))
	{
		gero.jump();
		return new JumpState;

	}
else if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			if(gero.getDirection())
				gero.runRight();
			else
				gero.runLeft();
			return new RunState;
		}


else if (  ((!sf::Keyboard::isKeyPressed(sf::Keyboard::Right ) )
			       &&(!sf::Keyboard::isKeyPressed(sf::Keyboard::Left)))
					|| ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right ))
			        &&(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))))
		{

			gero.idle();
			return new IdleState;
		}
else return nullptr;

}

EntityState::GraphicState WalkState::state()
{
	return m_GraphicState;
}
