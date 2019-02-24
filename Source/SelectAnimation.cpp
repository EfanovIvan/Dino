/*
 * SelectAnimation.cpp
 *
 *  Created on: 24 сент. 2018 г.
 *      Author: ivan
 */

#include <SelectAnimation.hpp>
#include <tinyxml.h>
#include <MainGero.hpp>


SelectAnimation::SelectAnimation(sf::Texture& texture)
{
	m_CurrentSprite.setTexture(texture);
	m_CurrentFrame = 0;
	//m_PositionAfterRun = true;
	m_SpeedFrame = 0;
//	m_fileNameXML = "testedit.xml";
}
void SelectAnimation::setPosition(float x, float y)
{
	m_CurrentSprite.setPosition(x, y);
}
void SelectAnimation::init()
{
	SelectAnimation::load(m_fileNameXML);
}
void SelectAnimation::setSprite(std::string spriteName)
{


	m_CurrentSprite.setTextureRect(sf::IntRect(
			m_NameSprite[spriteName][static_cast<int>(m_CurrentFrame)]));

}
void SelectAnimation::load(std::string const& fileNameXML)
{
//	TiXmlDocument doc(fileNameXML.c_str());
//	if(!doc.LoadFile())
//		throw std::runtime_error("bad parse");
	loadFromFile(fileNameXML);
	TiXmlElement *root = getRootElement();
	TiXmlElement* animation = root->FirstChildElement();
	while(animation)
	{
		std::string str = animation->Attribute("title");
		m_SpeedFrame = 0.005;//atoi(animation->Attribute("delay"));
		TiXmlElement* cut = animation -> FirstChildElement();
		int w, x, y, h;
		std::vector<sf::IntRect> localVector, reflectionVector;
		while(cut)
		{


			cut -> Attribute("w", &w);
			cut -> Attribute("x", &x);
			cut -> Attribute("y", &y);
			cut -> Attribute("h" ,&h);
			localVector.push_back(sf::IntRect(x, y, w, h));
			reflectionVector.push_back(sf::IntRect(x+w, y, -w, h));
			cut = cut -> NextSiblingElement();
		}


		m_NameSprite.insert(std::make_pair(str, localVector));
			m_NameSprite.insert(
					std::make_pair(str + "Left", reflectionVector));
		animation = animation ->NextSiblingElement() ;
	}
	clear();

}
sf::Sprite&  SelectAnimation::getCurrentSprit(MainGero& player, float time)
{
	using stateID = EntityState::GraphicState;
	m_CurrentFrame += m_SpeedFrame * time;
	switch( player.getStateID())
	{
		case  stateID::IDLE :
		{
			if (m_CurrentFrame > 10)
				m_CurrentFrame -= 10;

			if(player.getDirection())
				setSprite("idle");
			else
				setSprite("idleLeft");
			break;
		}
		case stateID::JUMP :
		{
			if (m_CurrentFrame > 12)
					m_CurrentFrame -= 12;
			if(player.getDirection())
				setSprite("jump");
			else
				setSprite("jumpLeft");
			break;
		}
		case stateID::WALK :
		{
			if (m_CurrentFrame > 10)
				m_CurrentFrame -= 10;
			if(player.getDirection())
				setSprite("walk");
			else
				setSprite("walkLeft");
			break;
		}
		case stateID::RUN:
		{
			if (m_CurrentFrame > 8)
				m_CurrentFrame -= 8;
			if(player.getDirection())
				setSprite("run");
			else
				setSprite("runLeft");
			break;
		}
	}

		return m_CurrentSprite;
}



