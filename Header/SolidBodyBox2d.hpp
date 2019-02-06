/*
 * SolidBodyBox2d.hpp
 *
 *  Created on: 30 янв. 2019 г.
 *      Author: ivan
 */

#ifndef HEADER_SOLIDBODYBOX2D_HPP_
#define HEADER_SOLIDBODYBOX2D_HPP_
#include <Box2D.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Converter.hpp>
class SolidBodyBox2d {
public:
	//bool alive;
	SolidBodyBox2d(sf::Rect<float> l_Rect, b2World& l_world)
								:Rect(l_Rect)
								,world(l_world)
{
	name = new std::string("");
	using converter::pixelsToMeters;
	bodyDef.position.Set(pixelsToMeters<double>(Rect.left+Rect.width/2),
						pixelsToMeters<double>(Rect.top+Rect.height/2));

	bodyDef.type = b2_staticBody;

		b2shape.SetAsBox(pixelsToMeters<double>(Rect.width/2.0),
						 pixelsToMeters<double>(Rect.height/2.0));


		m_FixtureDef.density = 1.0;
		m_FixtureDef.friction = 0.01;
		m_FixtureDef.restitution= 0;
		m_FixtureDef.shape = &b2shape;

		body = world.CreateBody(&bodyDef);
		body->CreateFixture(&m_FixtureDef);


}
private:
	sf::Rect<float> Rect;
	std::string * name;
	b2World &world;
	b2FixtureDef m_FixtureDef;
	b2BodyDef bodyDef;
	b2PolygonShape b2shape;
	b2Body* body;



};

#endif /* HEADER_SOLIDBODYBOX2D_HPP_ */
