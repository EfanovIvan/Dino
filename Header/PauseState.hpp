/*
 * PauseState.hpp
 *
 *  Created on: 10 февр. 2019 г.
 *      Author: ivan
 */

#ifndef HEADER_PAUSESTATE_HPP_
#define HEADER_PAUSESTATE_HPP_

#include <State.hpp>

class PauseState: public State
{
public:
						PauseState(StateStack& stack, Context context);

	virtual void		draw() override;
	virtual bool		update(sf::Time dt) override;
	virtual bool		handleEvent(const sf::Event& event) override;


private:
	sf::Sprite			mBackgroundSprite;
	sf::Text			mPausedText;
	sf::Text			mInstructionText;

};

#endif /* HEADER_PAUSESTATE_HPP_ */
