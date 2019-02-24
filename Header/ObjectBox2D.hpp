/*
 * BoxBodyBox2d.hpp
 *
 *  Created on: 3 февр. 2019 г.
 *      Author: ivan
 */

#ifndef HEADER_OBJECTBOX2D_HPP_
#define HEADER_OBJECTBOX2D_HPP_
#include <Box2D.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Converter.hpp>
#include <Utility.hpp>


class ObjectBox2D : public sf::Drawable {
public:
	ObjectBox2D(sf::Texture& l_Texture,
				 sf::Rect<float> l_Rect,
				 b2World& l_world, b2BodyType type = b2_dynamicBody);

	ObjectBox2D(sf::Rect<float> l_Rect, b2World& l_world, b2BodyType type );
	explicit ObjectBox2D(b2World& l_world );

	virtual void draw(sf::RenderTarget& taget,
								sf::RenderStates state) const override;
	void update();
protected:
	void setPosition(float x, float y, float angle);
	void setPositionBody(sf::Rect<float>& rect);
	void creatFixtureType(float density, float friction, b2BodyType type);
protected:
	sf::Rect<float> Rect;
	sf::Sprite m_Sprite;
	b2World &world;
	b2FixtureDef m_FixtureDef;
	b2BodyDef bodyDef;
	b2PolygonShape b2shape;
	b2Body* body;



};


#endif /* HEADER_OBJECTBOX2D_HPP_ */
