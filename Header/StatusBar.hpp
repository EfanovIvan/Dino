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
class StatusBar: public sf::Drawable
{
public:
	StatusBar(sf::Font& l_font);
	void draw(sf::RenderTarget& taget,
								sf::RenderStates state) const override;
	void upate(sf::Vector2f& positionView, sf::Vector2u sizeWindow);

private:
	enum BarTexturesID { heart, star };
	ResourceHolder<sf::Texture, BarTexturesID>  m_BarTextures;
	std::array<sf::Sprite, 3> m_Hearts;
	sf::Sprite m_BarStar;
	sf::Text m_TextOfStars;
	int m_Lives;
};

#endif /* HEADER_STATUSBAR_HPP_ */
