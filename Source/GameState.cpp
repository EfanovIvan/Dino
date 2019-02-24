/*
 * GameState.cpp
 *
 *  Created on: 4 янв. 2019 г.
 *      Author: ivan
 */

#include <GameState.hpp>

#include <ObjectSfml.hpp>
#include <Utility.hpp>


GameState::GameState(StateStack& stack, Context context)
					: State(stack, context)
					,m_World(b2Vec2(0.f, 9.8f))
					,m_Gero(context.m_Textures->
										get(Textures::MainGero),m_World)
					,m_StatusBar(context.m_Fonts->get(Fonts::Main),
									context.m_Window->getSize())
{
	countStars = 0;
	selectLevel();
	m_BG = m_Level.getBackGround();
	m_BG.scale(1.2, 1.4);
	downloudTexture();
	createObjectWorld();
}

void GameState::draw()
{
	sf::Vector2f centerView(m_Gero.getGeroView().getCenter());
	sf::RenderWindow& window = *getContext().m_Window;
	 sizeWindow = { window.getSize() };
	m_BG.setPosition(centerView);
	window.draw(m_BG);
	window.draw(m_Level);

	for(std::size_t i = 0; i < m_ObjectsBox2D.size(); i++)
		window.draw(m_ObjectsBox2D[i]);

	window.setView(m_Gero.getGeroView());
	for(size_t i = 0; i < m_Stars.size(); ++i)
		if(m_Stars[i].isAlive())
			window.draw(m_Stars[i]);

	window.draw(m_Gero);
	window.draw(m_StatusBar);
}

bool GameState::update(sf::Time dt)
{
	float time = clock.getElapsedTime().asSeconds();
	m_Gero.update(float(dt.asMilliseconds()));
	m_timeConvert = std::async(std::launch::async, getElapsedTimeLevel, time);

	m_World.Step(1/60.f, 8, 3);

	for(std::size_t i = 0; i < m_ObjectsBox2D.size(); i++)
		m_ObjectsBox2D[i].update();


	if(m_Gero.getRect().intersects(m_Level.GetObject("abyss").rect))
		m_Gero.reduceLive();


    for(size_t i = 0; i < m_Stars.size(); ++i)
			if(m_Gero.getRect().intersects(m_Stars[i].getRect()))
					m_Stars[i].setAlive(false);

    for(size_t i = 0; i < m_Stars.size(); ++i)
    	if(!m_Stars[i].isAlive() && !m_Stars[i].counted())
    	{
    		m_Stars[i].setCounted(true);
    		countStars++;
    	}

    if(checkWinLevel())
    {
    	(*getContext().m_CurrentLevel)++;
    	requestStateClear();
    	requestStackPush(StatesID::PassedLevel);
    }
    if(checkGameOver())
    {
    	requestStateClear();
    	requestStackPush(StatesID::GameOver);
    }
    m_StatusBar.udate(m_Gero.getGeroView().getCenter(),
    		countStars, m_timeConvert.get(), m_Gero.getLives());



}

bool GameState::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed &&
						event.key.code == sf::Keyboard::Escape)
			requestStackPush(StatesID::Pause);

			m_Gero.handleEvent(event);
}



void GameState::selectLevel()
{

	auto levelId = *getContext().m_CurrentLevel;
	auto& levels = *getContext().m_LevelsPathFromXML;
	LevelParser(levels[levelId++].c_str(), m_Level);
}

void GameState::createObjectWorld()
{

	for(std::size_t i = 0; i < m_Level.GetAllObjects().size(); ++i)
	{
		if(m_Level.GetAllObjects()[i].name == "solid")
			m_SolidBox2D.emplace_back(m_Level.GetAllObjects()[i].rect,
					m_World, b2BodyType::b2_staticBody);

		if(m_Level.GetAllObjects()[i].name == "Dino")
			m_Gero.creatBodyBox2d(m_Level.GetAllObjects()[i].rect);

		if(m_Level.GetAllObjects()[i].name == "box")
			m_ObjectsBox2D.emplace_back(m_ObjectWorldTexturs.get(ObjectID::box),
							m_Level.GetAllObjects()[i].rect, m_World);

		if(m_Level.GetAllObjects()[i].name == "star")
			m_Stars.emplace_back(m_Level.GetAllObjects()[i].rect
					,m_ObjectWorldTexturs.get(ObjectID::star));
	}

}
bool GameState::checkWinLevel()
{

	if(m_Gero.getRect().intersects(m_Level.GetObject("EndLevel").rect))
	{
		if(countStars == m_Stars.size()
				&& clock.getElapsedTime().asSeconds() < 180)
		return true;
	}

	else
		return false;
}
bool GameState::checkGameOver()
{
	if(clock.getElapsedTime().asSeconds() > 180
			|| m_Gero.getLives() == 0)
		return true;
	return false;
}
void GameState::downloudTexture()
{
	m_ObjectWorldTexturs.load(ObjectID::box,
								"Media/summer/Object/Crate.png");
	m_ObjectWorldTexturs.load(ObjectID::star,
									"Media/star.png");
	m_ObjectWorldTexturs.load(ObjectID::bar_star,
										"Media/bar.png");
}
