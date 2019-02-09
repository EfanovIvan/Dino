/*
 * ObjectSfml.hpp
 *
 *  Created on: 5 февр. 2019 г.
 *      Author: ivan
 */

#ifndef HEADER_OBJECTSFML_HPP_
#define HEADER_OBJECTSFML_HPP_
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
class ObjectSfml : public sf::Drawable
{
public:
	explicit ObjectSfml(sf::Rect<float> l_Rect, sf::Texture&
			l_Texture);
	bool isAlive();
	void setAlive(bool alive) { m_Alive = alive; }
	sf::Rect<float> const getRect() { return m_Rect; }
	void draw(sf::RenderWindow& window);
	std::string const getName() { return m_Name; }
	virtual void draw(sf::RenderTarget& taget,
							sf::RenderStates state) const override;
	//~virtual ObjectSfml() = default;
private:
	sf::Rect<float> m_Rect;
	sf::Sprite m_Sprite;
	bool m_Alive;
	std::string m_Name;
};

#endif /* HEADER_OBJECTSFML_HPP_ */
