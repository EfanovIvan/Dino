/*
 * World.hpp
 *
 *  Created on: 9 февр. 2019 г.
 *      Author: ivan
 */

#ifndef HEADER_WORLD_HPP_
#define HEADER_WORLD_HPP_

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics.hpp>
#include <ResourceHolder.hpp>
#include <Box2D.h>
#include <MainGero.hpp>

class World: public sf::Drawable, public sf::NonCopyable
{
public:
	void draw(sf::RenderTarget& taget,
							sf::RenderStates state) const override;
	bool handleEvent(const sf::Event& event);
	bool update(sf::Time dt);
private:
	enum ObjectsID { box, mushroom, heart, star, bar_star };
	void downloudLevel();
	void downloudTexture();
	void createObject();
private:
	ResourceHolder<sf::Texture, ObjectsID>  m_TexturesObjects;
	b2World m_WorldBox2d;
	MainGero m_Gero;
	sf::Sprite m_LeveBackGround;
};

#endif /* HEADER_WORLD_HPP_ */
