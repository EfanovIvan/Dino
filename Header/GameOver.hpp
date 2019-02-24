/*
 * GameOver.hpp
 *
 *  Created on: 24 февр. 2019 г.
 *      Author: ivan
 */

#ifndef HEADER_GAMEOVER_HPP_
#define HEADER_GAMEOVER_HPP_

#include <State.hpp>
#include <Utility.hpp>
#include <SFML/Graphics.hpp>
#include <ResourceHolder.hpp>
class GameOver: public State
{
public:
	GameOver(StateStack& stack,
								Context context);

	virtual void	draw()  override ;
	virtual bool	update(sf::Time dt) override;
	virtual bool	handleEvent(const sf::Event& event) override;


private:
	enum  OptionNames
		{
			Repeat,
			Exit,
		};
	void updateOptionText();
private:
	sf::Sprite			m_BackgroundSprite;
	sf::Text			m_LableText;
	std::array<sf::Text, 2> m_Options;
	std::size_t				m_OptionIndex;
};

#endif /* HEADER_GAMEOVER_HPP_ */
