/*
 * BoxBodyBox2d.cpp
 *
 *  Created on: 3 февр. 2019 г.
 *      Author: ivan
 */

#include <BoxBodyBox2d.hpp>

void BoxBodyBox2d::draw(sf::RenderTarget& taget,
		sf::RenderStates state) const
{
	taget.draw(m_Sprite);
}
void BoxBodyBox2d::setPosition(float x, float y, float angle)
{
	m_Sprite.setPosition(x, y);
	m_Sprite.setRotation(angle);
}
