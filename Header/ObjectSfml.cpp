/*
 * ObjectSfml.cpp
 *
 *  Created on: 5 февр. 2019 г.
 *      Author: ivan
 */

#include <ObjectSfml.hpp>

ObjectSfml::ObjectSfml(sf::Rect<float> l_Rect, sf::Texture& l_Texture):
					m_Rect(l_Rect)
					,m_Sprite(l_Texture)
					,m_Alive(true)
					,m_counted(false)
{
	m_Sprite.setPosition(m_Rect.left, m_Rect.top);
}
bool ObjectSfml::isAlive()
{
	return m_Alive;
}

void ObjectSfml::draw(sf::RenderTarget& taget,
		sf::RenderStates state) const
{
	taget.draw(m_Sprite);
}
