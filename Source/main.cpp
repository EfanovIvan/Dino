
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <Box2D.h>
#include <tinyxml.h>
#include <StateStack.hpp>
#include <State.hpp>
#include <TitleState.hpp>
#include <MenuState.hpp>
#include <memory>
#include <ResourceHolder.hpp>
#include <ResourceIdentifiers.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <GameState.hpp>
#include <PauseState.hpp>
#include <tinyxml.h>
#include <tinystr.h>
#include <ParserXML.hpp>
std::map<unsigned int, std::string>
loadLevelXMLPath(std::string const& pathXMLFile);
int main()
{
	const sf::Time	TimePerFrame =sf::seconds(1.f/60.f);

	sf::RenderWindow m_RenWindow(sf::VideoMode(1000, 850),
										"States", sf::Style::Close);
	m_RenWindow.setVerticalSyncEnabled(true);
	TextureHolder textures;
	FontHolder fonts;
	textures.load(Textures::TitleScreen,"Media/background.png" );
	textures.load(Textures::MainGero,"Media/DinoTIleset.png" );
	fonts.load(Fonts::Main,"Media/RAVIE.TTF" );
	auto LevelsXMLPath = loadLevelXMLPath("XMLfiles/levels.xml");
	auto s = std::make_unique<StateStack>(State::Context(m_RenWindow,
										textures, fonts, LevelsXMLPath ));
	//StateStack *s = new StateStack(State::Context(m_RenWindow));
	sf::Event event;
	s->registerState<TitleState>(StatesID::Title);
	s->registerState<MenuState>(StatesID::Menu);
	s->registerState<GameState>(StatesID::Game);
	s->registerState<PauseState>(StatesID::Pause);
	s->pushState(StatesID::Title);

	sf::Clock clock;
		sf::Time timeSinceLastUpdate = sf::Time::Zero;

	try
	{
		while (m_RenWindow.isOpen())
		{
			sf::Time dt = clock.restart();
			timeSinceLastUpdate += dt;
			while (timeSinceLastUpdate > TimePerFrame)
			{
				timeSinceLastUpdate -= TimePerFrame;

					while (m_RenWindow.pollEvent(event))
					{
						s->handleEvent(event);

						if (event.type == sf::Event::Closed)
							m_RenWindow.close();
					}
					s->update(TimePerFrame);

				// Check inside this loop, because stack might be empty before update() call
				if (s->isEmpty())
					m_RenWindow.close();
			}

			//updateStatistics(dt);
			m_RenWindow.clear();

			s->draw();

//			m_RenWindow.setView(mWindow.getDefaultView());
//			m_RenWindow.draw(mStatisticsText);

			m_RenWindow.display();
		}
	}
	catch(std::runtime_error& runtime)
	{
		std::cout << runtime.what();
	}
	return 0;
}
std::map<unsigned int, std::string>
loadLevelXMLPath(std::string const& pathXMLFile)
{
	std::map<unsigned int, std::string> levels;
	ParserXML parser(pathXMLFile);
	TiXmlElement *root = parser.getRootElement();
	TiXmlElement* level = root->FirstChildElement();
	while(level)
	{
		std::string str = level->Attribute("name");
		levels[std::atoi(level->Attribute("id"))] = str;
		level = level->NextSiblingElement();

	}
	return levels;
}

