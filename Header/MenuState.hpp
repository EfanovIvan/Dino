/*
 * MenuState.hpp
 *
 *  Created on: 23 дек. 2018 г.
 *      Author: ivan
 */

#ifndef HEADER_MENUSTATE_HPP_
#define HEADER_MENUSTATE_HPP_
#include <State.hpp>
#include <StateStack.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
class MenuState : public State {
public:
							MenuState(StateStack& stack, Context context);

	virtual void			draw()  override ;
	virtual bool			update(sf::Time dt) override;
	virtual bool			handleEvent(const sf::Event& event) override;

	void					updateOptionText();


private:
	enum  OptionNames
	{
		Play,
		Exit,
	};


private:
	sf::Sprite				m_BackgroundSprite;

	std::vector<sf::Text>	m_Options;
	std::size_t				m_OptionIndex;
};

#endif /* HEADER_MENUSTATE_HPP_ */
