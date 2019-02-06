/*
 * JumpState.hpp
 *
 *  Created on: 2 февр. 2019 г.
 *      Author: ivan
 */

#ifndef HEADER_JUMPSTATE_HPP_
#define HEADER_JUMPSTATE_HPP_

#include <EntityState.hpp>
#include <MainGero.hpp>
class JumpState: public EntityState {
public:
	JumpState();
	EntityState* handleEvent(MainGero& gero,
									const sf::Event& event) override;
	EntityState::GraphicState state() override;


};

#endif /* HEADER_JUMPSTATE_HPP_ */
