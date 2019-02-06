/*
 * WalkState.hpp
 *
 *  Created on: 2 февр. 2019 г.
 *      Author: ivan
 */

#ifndef HEADER_WALKSTATE_HPP_
#define HEADER_WALKSTATE_HPP_

#include <EntityState.hpp>

class WalkState: public EntityState {
public:
	WalkState();
	EntityState* handleEvent(MainGero& gero,
								const sf::Event& event) override;
	virtual GraphicState state() override;
};

#endif /* HEADER_WALKSTATE_HPP_ */
