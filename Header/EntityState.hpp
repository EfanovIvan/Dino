/*
 * EntityState.hpp
 *
 *  Created on: 2 февр. 2019 г.
 *      Author: ivan
 */

#ifndef HEADER_ENTITYSTATE_HPP_
#define HEADER_ENTITYSTATE_HPP_
#include <SFML/Graphics.hpp>
#include <SelectAnimation.hpp>
class MainGero;




class EntityState {
public:
	virtual ~EntityState() = default;
	virtual EntityState* handleEvent(MainGero& gero,
										const sf::Event& event) = 0;

enum class GraphicState
	{
		IDLE, WALK, RUN, JUMP
	};
	virtual GraphicState state() = 0;

protected:

	GraphicState m_GraphicState;
};

#endif /* HEADER_ENTITYSTATE_HPP_ */
