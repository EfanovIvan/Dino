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
#include <sstream>
struct position
{
	position():x(0),y(0),angle(0){}
	position(float l_x, float l_y):x(l_x), y(l_y) {}
	float x,y, angle;
};
class GameState: public State {
public:

	GameState(StateStack& stack, Context context);

	virtual void draw()  override;
	virtual bool update(sf::Time dt) override;
	virtual bool handleEvent(const sf::Event& event) override;
	enum Box2dTextureID { box, mushroom, heart, star, bar_star };


private:

	void selectLevel();
	void createWorldBox2d();
	void createSfmlObject();
	void downloudTexture();

	ResourceHolder<sf::Texture, Box2dTextureID>  m_TexHolderforBoxd2;
	std::vector<sf::Sprite> m_BoxBox2d;
	std::vector<sf::Sprite> m_Heart;
	std::vector<ObjectSfml> m_Mushrooms;
	std::vector<SolidBodyBox2d> m_BodysBox2d;
	std::vector<BoxBodyBox2d> m_box2d;

	b2World m_World;
	MainGero m_Gero;
	sf::Sprite  m_BG;


	sf::Vector2f m_positionHealth;


	sf::Text m_TextofStars;
	int stars;
	Level m_Level;


	sf::Clock clock;
	std::stringstream m_ElepsadeTimeGame;
	sf::Sprite m_Bar_star;
};

#endif /* HEADER_GAMESTATE_HPP_ */
