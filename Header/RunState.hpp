/*
 * RunState.hpp
 *
 *  Created on: 2 февр. 2019 г.
 *      Author: ivan
 */

#ifndef HEADER_RUNSTATE_HPP_
#define HEADER_RUNSTATE_HPP_

#include <EntityState.hpp>
#include <MainGero.hpp>
class RunState: public EntityState {
public:
	RunState();
	EntityState* handleEvent(MainGero& gero,
									const sf::Event& event) override;
	EntityState::GraphicState state() override;
};

#endif /* HEADER_RUNSTATE_HPP_ */
