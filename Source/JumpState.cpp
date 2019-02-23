/*
 * JumpState.cpp
 *
 *  Created on: 2 февр. 2019 г.
 *      Author: ivan
 */

#include <JumpState.hpp>
#include <IdleState.hpp>
#include <WalkState.hpp>
JumpState::JumpState()
{
	m_GraphicState = GraphicState::JUMP;
}

EntityState* JumpState::handleEvent(MainGero& gero, const sf::Event& event)
{
//if( gero.getBody()->GetLinearVelocity().y == 0 && gero.getOnGround())
//{
//	return new IdleState;
//}
//else
	return nullptr;


}

EntityState::GraphicState JumpState::state()
{
	return m_GraphicState;
}
