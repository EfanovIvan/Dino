/*
 * BoxBodyBox2d.cpp
 *
 *  Created on: 3 февр. 2019 г.
 *      Author: ivan
 */

#include <ObjectBox2D.hpp>

ObjectBox2D::ObjectBox2D(sf::Texture& l_Texture,
				 sf::Rect<float> l_Rect,
				 b2World& l_world, b2BodyType type)
				:Rect(l_Rect)
				,world(l_world)
				,m_Sprite(l_Texture)

{
	centerOrigin(m_Sprite);
	setPositionBody(Rect);
	creatFixtureType(2.0, 0.3, type);
}

ObjectBox2D::ObjectBox2D(sf::Rect<float> l_Rect,
						b2World& l_world,
						b2BodyType type )
						:Rect(l_Rect)
						,world(l_world)
{
	setPositionBody(Rect);
	creatFixtureType(1.0, 0.01, type);
}
ObjectBox2D::ObjectBox2D(b2World& l_world):world(l_world),body(nullptr)
{

}
void ObjectBox2D::draw(sf::RenderTarget& taget,
		sf::RenderStates state) const
{
	taget.draw(m_Sprite);
}
void ObjectBox2D::setPosition(float x, float y, float angle)
{
	m_Sprite.setPosition(x, y);
	m_Sprite.setRotation(angle);
}

void ObjectBox2D::update()
{
	b2Vec2 pos = body->GetPosition();
	float angle = body->GetAngle();
	float x, y, ang;
	x = converter::metersToPixels(pos.x);
	y = converter::metersToPixels(pos.y);
	ang = converter::radToDeg(angle);
	setPosition(x, y, ang);
}
void ObjectBox2D::setPositionBody(sf::Rect<float>& rect)
{
	Rect = rect;
	using converter::pixelsToMeters;
	bodyDef.position.Set(pixelsToMeters<double>(Rect.left+Rect.width/2),
						pixelsToMeters<double>(Rect.top+Rect.height/2));
	b2shape.SetAsBox(pixelsToMeters<double>(Rect.width/2.0),
							 pixelsToMeters<double>(Rect.height/2.0));
}

void ObjectBox2D::creatFixtureType(float density, float friction, b2BodyType type)
{
	m_FixtureDef.density = density;
	m_FixtureDef.friction = friction;
	m_FixtureDef.shape = &b2shape;
	bodyDef.type = type;
	body = world.CreateBody(&bodyDef);
	body->CreateFixture(&m_FixtureDef);
}




