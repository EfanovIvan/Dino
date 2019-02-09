/*
 * StatusBar.cpp
 *
 *  Created on: 9 февр. 2019 г.
 *      Author: ivan
 */

#include <StatusBar.hpp>

StatusBar::StatusBar(sf::Font& l_font)

{
	m_TextOfStars.setFont(l_font);
	m_BarTextures.load(BarTexturesID::heart,
									"Media/heart.png");
	m_BarTextures.load(BarTexturesID::star,
										"Media/star.png");
	for(int i = 0; i < m_Hearts.size(); i++)
		m_Hearts[i].setTexture(m_BarTextures.get(BarTexturesID::heart));
	m_BarStar.setTexture(m_BarTextures.get(BarTexturesID::heart));
	m_Lives = 3;
}
void StatusBar::upate(sf::Vector2f& positionView, sf::Vector2u sizeWindow)
{
	positionView.x = positionView.x - sizeWindow.x/2;
	positionView.y = positionView.y - sizeWindow.y/2;
	for(std::size_t i = 0, offset = 60;  i < m_Hearts.size(); i++)
	{
		positionView.x = positionView.x + offset;
		m_Hearts[i].setPosition(positionView);
	}
	m_TextOfStars.setPosition(positionView.x + 100, positionView.y + 10 );
	m_BarStar.setPosition(m_TextOfStars.getOrigin());
}

void StatusBar::draw(sf::RenderTarget& taget,
								sf::RenderStates state) const
{
	for(std::size_t i = 0; i < m_Lives; i++)
		taget.draw(m_Hearts[i]);
	taget.draw(m_TextOfStars);
	taget.draw(m_BarStar);
}
