#include <StateStack.hpp>
#include <cassert>

StateStack::StateStack(State::Context context):
	m_Stack(),
	m_PendingList(),
	m_Context(context),
	m_Factories() 
	{}
	
void StateStack::update(sf::Time dt)
{
// Iterate from top to bottom, stop as soon as update() returns false
	for(auto itr = m_Stack.rbegin(); itr != m_Stack.rend(); ++itr)
	{
		if(!(*itr)-> update(dt))
			break;
	}
	applyPendingChanges();
}

void StateStack::draw()
{
// Draw all active states from bottom to top
	for(auto itr = m_Stack.rbegin(); itr != m_Stack.rend(); ++itr)
	{
		(*itr)->draw();
	}
}

void StateStack::handleEvent(const sf::Event& event)
{
// Iterate from top to bottom, stop as soon as handleEvent() returns false
	for(auto itr = m_Stack.rbegin(); itr != m_Stack.rend(); ++itr)
	{
		if(!(*itr)-> handleEvent(event))
			break;
	}	
	applyPendingChanges();
}

void StateStack::pushState(StatesID stateID)
{
	m_PendingList.push_back(PendingChange(Push, stateID));
}

void StateStack::popState()
{
	m_PendingList.push_back(PendingChange(Pop));
}

void StateStack::clearStates()
{
	m_PendingList.push_back(PendingChange(Clear));
}

bool StateStack::isEmpty() const
{
	return m_Stack.empty();
}

State::Ptr StateStack::createState(StatesID stateID)
{
	auto found = m_Factories.find(stateID);
	assert(found != m_Factories.end());

	return found->second();
}

void StateStack::applyPendingChanges()
{
	for(auto itr = m_PendingList.begin();
			itr != m_PendingList.end(); ++itr)
	{
		switch (itr->action)
		{
			case Push:
				m_Stack.push_back(createState(itr->stateID));
				break;

			case Pop:
				m_Stack.pop_back();
				break;

			case Clear:
				m_Stack.clear();
				break;
		}
	}

	m_PendingList.clear();
}

StateStack::PendingChange::PendingChange(Action action, StatesID stateID)
: action(action)
, stateID(stateID)
{
}
