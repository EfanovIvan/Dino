#ifndef BOOK_TITLESTATE_HPP
#define BOOK_TITLESTATE_HPP

#include <State.hpp>
#include <StateStack.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class TitleState final: public State
{
	public:
							TitleState(StateStack& stack,
									Context context);

		virtual void	draw()  override ;
		virtual bool	update(sf::Time dt) override;
		virtual bool	handleEvent(const sf::Event& event) override;


	private:

		sf::Sprite			m_BackgroundSprite;
		sf::Text			m_Text;
		bool				m_ShowText;
		sf::Time			m_TextEffectTime;
};

#endif // BOOK_TITLESTATE_HPP

