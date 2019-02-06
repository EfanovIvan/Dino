#ifndef STATESTACK_HPP_
#define STATESTACK_HPP_
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <functional>
#include <memory>
//local file
#include <State.hpp>

class StateStack : private sf::NonCopyable
{
	public:
		enum Action
		{
			Push,
			Pop,
			Clear
		};
	public:
		explicit StateStack(State::Context context);
		template<typename T>
		void registerState(StatesID stateID);
		
		void update(sf::Time dt);
		void draw();
		void handleEvent(const sf::Event& event);
		void pushState(StatesID stateID);
		void popState();
		void clearStates();
		bool isEmpty() const;
		
	private:
		State::Ptr createState(StatesID stateID);
		void applyPendingChanges();
		
	private:
		struct PendingChange
		{
			explicit PendingChange(Action action,
					StatesID stateID = StatesID::None );
			Action 	action;
			StatesID 	stateID;
		};
		
	private:
		std::vector<State::Ptr> 						m_Stack;
		std::vector<PendingChange> 						m_PendingList;
		State::Context 									m_Context;
		std::map<StatesID, std::function<State::Ptr()>>	m_Factories;

};

template<typename T>
void StateStack::registerState(StatesID state)
{
	m_Factories[state] = [this] ()
	{
		return State::Ptr(new T(*this, m_Context));
	};

}








#endif //STATESTACK_HPP_
