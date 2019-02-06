/*
 * GameState.cpp
 *
 *  Created on: 4 янв. 2019 г.
 *      Author: ivan
 */

#include <GameState.hpp>

#include <ObjectSfml.hpp>


GameState::GameState(StateStack& stack, Context context)
					: State(stack, context)
					,m_World(b2Vec2(0.f, 9.8f))
					,m_Gero(context.m_Textures->get(Textures::MainGero),
										m_World)


{
	stars = 0;
	sf::Texture& texture = getContext().m_Textures->
			get(Textures::BackGround);
	m_BG.setTexture(texture);
	m_BG.setOrigin(texture.getSize().x/2, texture.getSize().y/2 );
	m_BG.scale(1.2, 1.4);

	m_TexHolderforBoxd2.load(Box2dTextureID::box,
							"Media/summer/png/Object/Crate.png");
	m_TexHolderforBoxd2.load(Box2dTextureID::heart,
								"Media/heart.png");
	m_TexHolderforBoxd2.load(Box2dTextureID::star,
									"Media/star.png");
	m_TextofStars.setFont(context.m_Fonts->get(Fonts::Main));
	m_TextofStars.setString("Stars" );
	m_TextofStars.setColor(sf::Color:: Yellow);
	for(int i = 0; i < 3; i++)
		m_Heart.push_back(sf::Sprite(
			(m_TexHolderforBoxd2.get(Box2dTextureID::heart))));
	//m_BoxBox2d.setTexture(m_TexHolderforBoxd2.get(Box2dTextureID::box));
	selectLevel();
	createWorldBox2d(m_World);
	createSfmlObject(m_Level);

}

void GameState::draw()
{
	sf::RenderWindow& window = *getContext().m_Window;
	m_BG.setPosition(m_Gero.getGeroView().getCenter());
	window.draw(m_BG);
	//window.getSize()
	m_Level.Draw(window);
	for(std::size_t i = 0; i < m_BoxBox2d.size(); i++)
	{
		window.draw(*m_BoxBox2d[i]);
	}
	window.setView(m_Gero.getGeroView());
	m_positionHealth = {m_Gero.getGeroView().getCenter()};
	m_positionHealth.x = m_positionHealth.x - 500;
	m_positionHealth.y = m_positionHealth.y - 450;
	for( int i = 0, offset = 70; i < m_Heart.size(); i++)
	{
		m_positionHealth.x = m_positionHealth.x + offset;
		m_Heart[i].setPosition(m_positionHealth.x,m_positionHealth.y);
		window.draw(m_Heart[i]);

	}
	m_TextofStars.setPosition(m_positionHealth.x + 100,m_positionHealth.y);
	window.draw(m_TextofStars);
	for(size_t i = 0; i < m_Mushrooms.size(); ++i)
	{
		if(m_Mushrooms[i].isAlive())
		{

			m_Mushrooms[i].draw(window);
		}
	}

	window.draw(m_Gero.getSprite());
}

bool GameState::update(sf::Time dt)
{

	m_Gero.update(float(dt.asMilliseconds()));
	m_World.Step(1/60.f, 8, 3);
	int j = 0;
    for (b2Body* it = m_World.GetBodyList(); it != 0; it = it->GetNext())
       {
			b2Vec2 pos = it->GetPosition();
			float angle = it->GetAngle();
			std::string * str =
					static_cast<std::string*>(it->GetUserData());

			if(str != nullptr)
				if ( *str == "box")
				{

					float x, y;
					x = converter::metersToPixels(pos.x);
					y = converter::metersToPixels(pos.y);
					m_Position.push_back(sf::Vector2f(x,y));
					m_BoxBox2d[j]->setPosition(x, y);
					m_BoxBox2d[j++]->
								setRotation(converter::radToDeg(angle));
				}

		 }
//    for(std::size_t i = 0; i < m_BoxBox2d.size(); i++)
//    	{
//    		m_BoxBox2d[i]->setPosition(m_Position[i]);
//    		std::cout << m_Position[i].x << " " << m_Position[i].y
//    				<< std::endl;
//    	}

    for(size_t i = 0; i < m_Mushrooms.size(); ++i)
    	{

			if(m_Gero.getRect().intersects(m_Mushrooms[i].getRect()))
			{
				stars++;
				m_Mushrooms[i].setAlive(false);
			}
   	    }
   // std::cout  << (int)clock.getElapsedTime().asSeconds() << std::endl;
  //  m_TextofStars.
    //m_TextofStars.setString(m_ElepsadeTimeGame.str() );

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

			LevelParser("XMLfiles/new3.xml", m_Level);

}
void GameState::createWorldBox2d(b2World& world)
{
	for(std::size_t i = 0; i < m_Level.GetAllObjects().size(); ++i)
	{
		if(m_Level.GetAllObjects()[i].name == "solid")
			m_BodysBox2d.push_back(
					std::make_shared<SolidBodyBox2d>
							(m_Level.GetAllObjects()[i].rect, world));

		if(m_Level.GetAllObjects()[i].name == "Dino")
			m_Gero.creatBodyBox2d(m_Level.GetAllObjects()[i].rect);

		if(m_Level.GetAllObjects()[i].name == "box")
			{
				m_localRect = m_Level.GetAllObjects()[i].rect;
				m_BoxBox2d.push_back(
						std::make_shared<sf::Sprite>(
						m_TexHolderforBoxd2.get(Box2dTextureID::box)));


				m_box2d.push_back(
					std::make_shared<BoxBodyBox2d>
							(m_Level.GetAllObjects()[i].rect, world));

			}
		for(std::size_t i = 0; i < m_BoxBox2d.size(); i++)
		{
			m_BoxBox2d[i]->setOrigin(m_localRect.width/2,
					m_localRect.height/2);
			//m_Position.reserve(m_BoxBox2d.size());
		}

	}
}
void  GameState::createSfmlObject(Level& level)
{

	for(std::size_t i = 0; i < level.GetObjects("star").size(); i++)
	{
		m_Mushrooms.push_back(ObjectSfml(
				level.GetObjects("star")[i].rect
				,m_TexHolderforBoxd2.get(Box2dTextureID::star)));
	}





}
