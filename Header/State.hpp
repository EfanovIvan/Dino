#ifndef STATE_HPP_
#define STATE_HPP_
#include <memory>
#include <SFML/Graphics.hpp>
#include <ResourceIdentifiers.hpp>
enum class StatesID
	{
		None,
		Title,
		Menu,
		Game,
		Loading,
		Pause
	};

namespace sf
{
	class RendirWindow;
}
class StateStack;

class State
{
	public:
	
	using Ptr = std::unique_ptr<State>;
	
	struct Context
	{
		
		Context(sf::RenderWindow& l_Window
				,TextureHolder& l_Textures
				,FontHolder&   l_Fonts
				,std::map<unsigned int, std::string>& levelsPath);

		sf::RenderWindow*  m_Window;
		TextureHolder   *  m_Textures;
		FontHolder      *  m_Fonts;
		unsigned int       m_CurrentLevel;
		std::map<unsigned int, std::string> *m_LevelsPathFromXML;
	};
	public:
	
	 State(StateStack& stack, Context context);
	 virtual ~State();
	 virtual void draw()  = 0;
	 virtual bool update(sf::Time dt) = 0;
	 virtual bool handleEvent(const sf::Event& event) = 0;
	 
	 protected:
	 
	 	void				requestStackPush(StatesID stateId);
		void				requestStackPop();
		void				requestStateClear();

		Context				getContext() const;
	 
	 private:
	 StateStack* m_Stack;
	 Context     m_Context;
	 

};





#endif // STATE_HPP_
