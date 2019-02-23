/*
 * StatusBar.hpp
 *
 *  Created on: 9 февр. 2019 г.
 *      Author: ivan
 */

#ifndef HEADER_STATUSBAR_HPP_
#define HEADER_STATUSBAR_HPP_
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <ResourceHolder.hpp>
#include <iostream>
#include <string>
#include <future>
#include <thread>
#include <chrono>
class StatusBar: public sf::Drawable
{
public:
	StatusBar(sf::Font& l_font);
	void draw(sf::RenderTarget& taget,
								sf::RenderStates state) const override;
	void udate(sf::Vector2f positionView, sf::Vector2u sizeWindow,
			int count, std::string, int lives);

private:

private:
	enum BarTexturesID { heart, star, time, deadheart };
	ResourceHolder<sf::Texture, BarTexturesID>  m_BarTextures;
	std::array<sf::Sprite, 3> m_Hearts;
	std::array<sf::Sprite, 3> m_Deadheart;
	sf::Sprite m_BarStar;
	sf::Sprite m_TimeBar;
	sf::Text m_TextOfStars;
	sf::Text m_Time;
	int m_Lives;
	int second;
	int minut;
};

#endif /* HEADER_STATUSBAR_HPP_ */
