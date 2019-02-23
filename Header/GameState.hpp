/*
 * GameState.hpp
 *
 *  Created on: 4 янв. 2019 г.
 *      Author: ivan
 */

#ifndef HEADER_GAMESTATE_HPP_
#define HEADER_GAMESTATE_HPP_

#include <Box2D.h>
#include <Level.hpp>
#include <State.hpp>
#include <MainGero.hpp>
#include <ResourceHolder.hpp>
#include <ResourceIdentifiers.hpp>
#include <LevelParser.hpp>
#include <SolidBodyBox2d.hpp>
#include <BoxBodyBox2d.hpp>
#include <Converter.hpp>
#include <ObjectSfml.hpp>
#include <StatusBar.hpp>
#include <future>
#include <functional>
#include <Utility.hpp>
#include <future>
#include <thread>

class GameState: public State {
public:

	GameState(StateStack& stack, Context context);

	virtual void draw()  override;
	virtual bool update(sf::Time dt) override;
	virtual bool handleEvent(const sf::Event& event) override;
	enum ObjectID { box, mushroom, heart, star, bar_star };


private:

	void selectLevel();
	void createObjectWorld();
	void downloudTexture();
private:
	ResourceHolder<sf::Texture, ObjectID>  m_ObjectWorldTexturs;
	//std::vector<sf::Sprite> m_BoxBox2d;

	std::vector<ObjectSfml> m_Mushrooms;
	std::vector<SolidBodyBox2d> m_BodysBox2d;
	std::vector<BoxBodyBox2d> m_box2d;

	b2World m_World;
	MainGero m_Gero;
	sf::Sprite  m_BG;

	sf::Vector2u sizeWindow;
	sf::Text m_TextofStars;
	int stars;
	Level m_Level;
	std::future<std::string> f;

	sf::Clock clock;
	StatusBar m_StatusBar;
};

#endif /* HEADER_GAMESTATE_HPP_ */
