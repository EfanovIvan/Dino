#include <SFML/Graphics/RenderWindow.hpp>
#include <StateStack.hpp>
#include <TitleState.hpp>
#include <string>
#include <Utility.hpp>
#include <ResourceHolder.hpp>
TitleState::TitleState(StateStack& stack, Context context)
						: State(stack, context)
						, m_Text()
						, m_ShowText(true)
						, m_TextEffectTime(sf::Time::Zero)
{
	m_BackgroundSprite.setTexture(
			context.m_Textures->get(Textures::TitleScreen));
	m_Text.setFont(context.m_Fonts->get(Fonts::Main));
	m_Text.setString("Press any key to start");
	centerOrigin(m_Text);
	m_Text.setPosition(context.m_Window->
				getView().getSize()/ 2.f);

}

void TitleState::draw()
{
	sf::RenderWindow& window = *getContext().m_Window;
	window.draw(m_BackgroundSprite);

	if (m_ShowText)
		window.draw(m_Text);
}

bool TitleState::update(sf::Time dt)
{
	m_TextEffectTime += dt;

	if (m_TextEffectTime >= sf::seconds(0.5f))
	{
		m_ShowText = !m_ShowText;
		m_TextEffectTime = sf::Time::Zero;
	}

	return true;
}

bool TitleState::handleEvent(const sf::Event& event)
{
	// If any key is pressed, trigger the next screen
	if (event.type == sf::Event::KeyReleased)
	{
		requestStackPop();
		requestStackPush(StatesID::Menu);
	}

	return true;
}
