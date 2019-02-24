#include <StateStack.hpp>
#include <State.hpp>



State::Context::Context(sf::RenderWindow& l_Window
						,TextureHolder& l_Textures
						,FontHolder&   l_Fonts
						,unsigned int& l_currentLevel
						,std::map<unsigned int, std::string>& levelsPath):
						m_Window(&l_Window)
						,m_Textures(&l_Textures)
						,m_Fonts(&l_Fonts)
						,m_CurrentLevel(&l_currentLevel)
						,m_LevelsPathFromXML(&levelsPath)
{

}


State::State(StateStack& stack, Context context):
			m_Stack(&stack)
		   ,m_Context(context)
{

}


void State::requestStackPush(StatesID stateId)
{
	m_Stack->pushState(stateId);
}

void State::requestStackPop()
{
	m_Stack->popState();
}

void State::requestStateClear()
{
	m_Stack->clearStates();
}

State::Context State::getContext() const
{
	return m_Context;
}


State::~State()
{

}
