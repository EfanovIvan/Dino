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
#include <EntityState.hpp>
#include <memory>
#include <ObjectBox2D.hpp>
class MainGero : public ObjectBox2D
{
public:
	MainGero(sf::Texture& l_texture, b2World& l_world);
	virtual void update(float time);
	virtual void handleEvent(const sf::Event& event);

	sf::FloatRect const& getRect() { return m_Rect; }
	sf::View& getGeroView();
	void creatBodyBox2d(sf::Rect<float> l_Rect);
	bool const getOnGround() { return m_OnGround; }
	EntityState::GraphicState const getStateID() { return stateID; }
	bool const getDirection() { return m_Direction; }
//	void draw(sf::RenderTarget& taget,
//								sf::RenderStates state) const override;
	void reduceLive();
	int getLives() { return m_Lives; }
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

	EntityState::GraphicState stateID;

	bool m_OnGround;
	float delta  = 0;
	bool m_Direction = false;


	int m_Lives;
	EntityState* m_EntityState ;

};

#endif /* HEADER_MAINGERO_HPP_ */
