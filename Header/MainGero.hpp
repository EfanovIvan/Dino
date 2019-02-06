/*
 * MainGero.hpp
 *
 *  Created on: 4 янв. 2019 г.
 *      Author: ivan
 */

#ifndef HEADER_MAINGERO_HPP_
#define HEADER_MAINGERO_HPP_
#include <SFML/Graphics.hpp>
#include <Box2D.h>
#include <Converter.hpp>
#include <SelectAnimation.hpp>
#include <iostream>
class EntityState;

class MainGero {
public:
	MainGero(sf::Texture& l_texture, b2World& l_world);
	virtual void update(float time);
	virtual void handleEvent(const sf::Event& event);

	sf::FloatRect getRect() { return m_Rect; }
	sf::Sprite getSprite(){ return m_SelectAnim.getSprite(); }
	sf::View& getGeroView();
	void creatBodyBox2d(sf::Rect<float> l_Rect);
	bool const getOnGround() { return m_OnGround; }
	EntityState::GraphicState const getStateID() { return stateID; }
	bool const getDirection() { return m_Direction; }
	b2Body* getBody() { return body; }
public:
	void walk();
	void walkLeft();
	void jump();
	void runLeft();
	void runRight();
	void idle();

private:
	bool direct(float dir);
private:
	SelectAnimation m_SelectAnim;
	sf::View 		viewGero;
	sf::FloatRect 	m_Rect;
	std::string const m_nameGero{"dino"};
	EntityState::GraphicState stateID;

	bool m_OnGround;
	float delta  = 0;
	bool m_Direction = true;

	b2World &world;
	b2FixtureDef m_FixtureDef;
	b2BodyDef bodyDef;
	b2PolygonShape b2shape;
	b2Body* body = nullptr;
	std::string* name;
	EntityState* m_EntityState;

};

#endif /* HEADER_MAINGERO_HPP_ */
