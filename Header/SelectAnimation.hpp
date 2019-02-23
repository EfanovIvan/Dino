/*
 * SelectAnimation.h
 *
 *  Created on: 24 сент. 2018 г.
 *      Author: ivan
 */

#ifndef SELECTANIMATION_H_
#define SELECTANIMATION_H_
#include <SFML/Graphics.hpp>

#include <map>
#include <vector>
#include <ParserXML.hpp>
class MainGero;
#include <EntityState.hpp>
class SelectAnimation : public ParserXML {

private:
	//using AmountOfFrame = std::pair<int, std::vector<sf::IntRect>>;
	using AmountOfFrame = std::tuple<int, std::vector<sf::IntRect>>;
	std::map<std::string, std::vector<sf::IntRect>> m_NameSprite;
	sf::Sprite 										m_CurrentSprite;
	float 											m_CurrentFrame;
	float 											m_SpeedFrame;
	std::string 									m_fileNameXML;


public:
	SelectAnimation(sf::Texture& texture);

	void load(std::string const& fileNameXML);
	void setSprite(std::string spriteName);
	void init();

	sf::Sprite& animationOutput(MainGero& player, float time);
	void setPosition(float x, float y);
	sf::Sprite getSprite() { return m_CurrentSprite; }
};

#endif /* SELECTANIMATION_H_ */
