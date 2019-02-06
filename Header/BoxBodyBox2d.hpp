/*
 * BoxBodyBox2d.hpp
 *
 *  Created on: 3 февр. 2019 г.
 *      Author: ivan
 */

#ifndef HEADER_BOXBODYBOX2D_HPP_
#define HEADER_BOXBODYBOX2D_HPP_
#include <Box2D.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Converter.hpp>
class BoxBodyBox2d {
public:
	BoxBodyBox2d(sf::Rect<float> l_Rect, b2World& l_world)
								:Rect(l_Rect)
								,world(l_world)
{
	name = new std::string("box");
	using converter::pixelsToMeters;
	bodyDef.position.Set(pixelsToMeters<double>(Rect.left+Rect.width/2),
						pixelsToMeters<double>(Rect.top+Rect.height/2));

	bodyDef.type = b2_dynamicBody;

		b2shape.SetAsBox(pixelsToMeters<double>(Rect.width/2.0),
						 pixelsToMeters<double>(Rect.height/2.0));


		m_FixtureDef.density = 2.0;
		m_FixtureDef.friction = 0.3;
		m_FixtureDef.restitution= 0;
		m_FixtureDef.shape = &b2shape;

		body = world.CreateBody(&bodyDef);
		body->CreateFixture(&m_FixtureDef);
		body->SetUserData(name);

}
private:
	sf::Rect<float> Rect;

	b2World &world;
	b2FixtureDef m_FixtureDef;
	b2BodyDef bodyDef;
	b2PolygonShape b2shape;
	b2Body* body;
	std::string * name;


};


#endif /* HEADER_BOXBODYBOX2D_HPP_ */
