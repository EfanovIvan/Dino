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
					,m_StatusBar(context.m_Fonts->get(Fonts::Main))
{
	stars = 0;
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

	for(std::size_t i = 0; i < m_box2d.size(); i++)
		window.draw(m_box2d[i]);

	window.setView(m_Gero.getGeroView());
	for(size_t i = 0; i < m_Mushrooms.size(); ++i)
		if(m_Mushrooms[i].isAlive())
			window.draw(m_Mushrooms[i]);

	window.draw(m_Gero);
	window.draw(m_StatusBar);
}

bool GameState::update(sf::Time dt)
{
	float time = clock.getElapsedTime().asSeconds();
	m_Gero.update(float(dt.asMilliseconds()));
	f = std::async(std::launch::async, getElapsedTimeLevel, time);
	m_World.Step(1/60.f, 8, 3);
	int j = 0;

    for (b2Body* it = m_World.GetBodyList(); it != 0; it = it->GetNext())
       {
			b2Vec2 pos = it->GetPosition();
			float angle = it->GetAngle();
			std::string * str =
					static_cast<std::string*>(it->GetUserData());

			if(str != nullptr)
				if (*str == "box")
				{

					float x, y;
					x = converter::metersToPixels(pos.x);
					y = converter::metersToPixels(pos.y);
					m_box2d[j++].setPosition(x, y,
							converter::radToDeg(angle));
				}
		 }


	if(m_Gero.getRect().intersects(m_Level.GetObject("abyss").rect))
	{
		m_Gero.reduceLive();
		m_Gero.getBody()->SetTransform(b2Vec2(10,10),0) ;
	}


    for(size_t i = 0; i < m_Mushrooms.size(); ++i)
			if(m_Gero.getRect().intersects(m_Mushrooms[i].getRect()))
					m_Mushrooms[i].setAlive(false);

    for(size_t i = 0; i < m_Mushrooms.size(); ++i)
    	if(!m_Mushrooms[i].isAlive() && !m_Mushrooms[i].counted())
    	{
    		m_Mushrooms[i].setCounted(true);
    		stars++;
    	}
    m_StatusBar.udate(m_Gero.getGeroView().getCenter(),sizeWindow,
    		stars, f.get(), m_Gero.getLives());

   // std::cout  << (int)clock.getElapsedTime().asSeconds() << std::endl;
  //  m_TextofStars.
    //m_TextofStars.setString(m_ElepsadeTimeGame.str() );
}

bool GameState::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed &&
						event.key.code == sf::Keyboard::Escape)
	{
			//requestStateClear();
			requestStackPush(StatesID::Pause);
	}
			m_Gero.handleEvent(event);
}



void GameState::selectLevel()
{
	auto levelId = getContext().m_CurrentLevel;
	auto& levels = *getContext().m_LevelsPathFromXML;
	LevelParser(levels[levelId].c_str(), m_Level);
}

void GameState::createObjectWorld()
{

	for(std::size_t i = 0; i < m_Level.GetAllObjects().size(); ++i)
	{
		if(m_Level.GetAllObjects()[i].name == "solid")
			m_BodysBox2d.emplace_back(m_Level.GetAllObjects()[i].rect,
					m_World);

		if(m_Level.GetAllObjects()[i].name == "Dino")
			m_Gero.creatBodyBox2d(m_Level.GetAllObjects()[i].rect);

		if(m_Level.GetAllObjects()[i].name == "box")
			m_box2d.emplace_back(m_ObjectWorldTexturs.get(ObjectID::box),
							m_Level.GetAllObjects()[i].rect, m_World);

		if(m_Level.GetAllObjects()[i].name == "star")
			m_Mushrooms.emplace_back(m_Level.GetAllObjects()[i].rect
					,m_ObjectWorldTexturs.get(ObjectID::star));

	}

//	for(std::size_t i = 0; i < m_BoxBox2d.size(); i++)
//		centerOrigin(m_BoxBox2d[i]);
}

void GameState::downloudTexture()
{
	m_ObjectWorldTexturs.load(ObjectID::box,
								"Media/summer/png/Object/Crate.png");
	m_ObjectWorldTexturs.load(ObjectID::star,
									"Media/star.png");
	m_ObjectWorldTexturs.load(ObjectID::bar_star,
										"Media/bar.png");
}
