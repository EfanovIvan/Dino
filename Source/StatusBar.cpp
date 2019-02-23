/*
 * StatusBar.cpp
 *
 *  Created on: 9 февр. 2019 г.
 *      Author: ivan
 */

#include <StatusBar.hpp>

StatusBar::StatusBar(sf::Font& l_font):second(0),minut(0)

{
	m_TextOfStars.setFont(l_font);
	m_Time.setFont(l_font);
	m_Time.setColor(sf::Color(162,109, 19, 250));

	m_BarTextures.load(BarTexturesID::heart,    "Media/heart.png");
	m_BarTextures.load(BarTexturesID::star,     "Media/bar.png");
	m_BarTextures.load(BarTexturesID::time,     "Media/time_bar.png");
	m_BarTextures.load(BarTexturesID::deadheart,"Media/deadheart.png");

	m_TimeBar.setTexture(m_BarTextures.get(BarTexturesID::time));
	m_TimeBar.setOrigin(m_BarTextures.get(BarTexturesID::time).getSize().x/2,
						m_BarTextures.get(BarTexturesID::time).getSize().y/2 );
	for(std::size_t i = 0; i < m_Hearts.size(); i++)
		m_Hearts[i].setTexture(m_BarTextures.get(BarTexturesID::heart));
	for(std::size_t i = 0; i < m_Hearts.size(); i++)
		m_Deadheart[i].setTexture(m_BarTextures.get(BarTexturesID::deadheart));

	m_BarStar.setTexture(m_BarTextures.get(BarTexturesID::star));
	m_BarStar.setOrigin(m_BarTextures.get(BarTexturesID::star).getSize().x/2,
			m_BarTextures.get(BarTexturesID::star).getSize().y/2);

	m_BarStar.scale(1.2f, 1.2f);
	m_TextOfStars.setColor(sf::Color(162,109, 19, 250));
	m_Lives = 3;
}
void StatusBar::udate(sf::Vector2f positionView,
						sf::Vector2u sizeWindow, int count, std::string str
						, int lives)
{
	m_Lives = lives;
	m_Time.setString(str);
	if(count > 10)
		m_TextOfStars.setString(std::to_string(count));
	else
		m_TextOfStars.setString("0" + std::to_string(count));


	positionView.x = positionView.x - sizeWindow.x/2;
	positionView.y = positionView.y - sizeWindow.y/2;
	for(std::size_t i = 0, offset = 70;  i < m_Hearts.size(); i++)
	{
		positionView.x = positionView.x + offset;
		m_Hearts[i].setPosition(positionView);
		m_Deadheart[i].setPosition(positionView);
	}

	m_BarStar.setPosition(positionView.x + 300, positionView.y + 20);
	m_TextOfStars.setPosition(m_BarStar.getPosition().x - 22,
			m_BarStar.getPosition().y - 10);
	m_TimeBar.setPosition(m_BarStar.getPosition().x + 325,
									m_BarStar.getPosition().y);

	m_Time.setPosition(m_TimeBar.getPosition().x - 40,
							m_TimeBar.getPosition().y- 20);

}

void StatusBar::draw(sf::RenderTarget& taget,
								sf::RenderStates state) const
{

	for(std::size_t i = 0; i < m_Lives; i++)
		taget.draw(m_Hearts[i]);
	for(std::size_t i = 2; i > m_Lives-1; i--)
		taget.draw(m_Deadheart[i]);
	taget.draw(m_BarStar);
	taget.draw(m_TextOfStars);
	taget.draw(m_TimeBar);
	taget.draw(m_Time);


}

