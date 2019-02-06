/*
 * IdleState.hpp
 *
 *  Created on: 2 февр. 2019 г.
 *      Author: ivan
 */

#ifndef HEADER_IDLESTATE_HPP_
#define HEADER_IDLESTATE_HPP_

#include <EntityState.hpp>
#include <MainGero.hpp>
class IdleState: public EntityState
{
public:
	IdleState();
	EntityState* handleEvent(MainGero& gero,
										const sf::Event& event) override;
	virtual GraphicState state() override;

};

#endif /* HEADER_IDLESTATE_HPP_ */
