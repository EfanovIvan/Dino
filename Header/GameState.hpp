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
#include <Converter.hpp>
#include <ObjectBox2D.hpp>
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

	std::vector<ObjectSfml> m_Stars;
	std::vector<ObjectBox2D> m_SolidBox2D;
	std::vector<ObjectBox2D> m_ObjectsBox2D;

	b2World m_World;
	MainGero m_Gero;
	sf::Sprite  m_BG;
	Level m_Level;
	StatusBar m_StatusBar;

	sf::Vector2u sizeWindow;
	int countStars;


	std::future<std::string> m_timeConvert;
	sf::Clock clock;

};

#endif /* HEADER_GAMESTATE_HPP_ */
