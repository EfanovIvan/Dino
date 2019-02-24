
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
#include <PassedLevel.hpp>
#include <GameOver.hpp>
std::map<unsigned int, std::string>
loadLevelXMLPath(std::string const& pathXMLFile);
int main()
{
	const sf::Time	TimePerFrame =sf::seconds(1.f/60.f);

	sf::RenderWindow m_RenWindow(sf::VideoMode(1000, 850),
										"Dino", sf::Style::Close);
	m_RenWindow.setVerticalSyncEnabled(true);
	TextureHolder textures;
	FontHolder fonts;
	textures.load(Textures::TitleScreen,"Media/background.png" );
	textures.load(Textures::MainGero,"Media/DinoTIleset.png" );
	fonts.load(Fonts::Main,"Media/RAVIE.TTF" );
	unsigned int currentLevel = 1;
	auto LevelsXMLPath = loadLevelXMLPath("XMLfiles/levels.xml");
	auto stateStack = std::make_unique<StateStack>(State::Context
										(m_RenWindow,
										textures, fonts,currentLevel,
										LevelsXMLPath ));
	sf::Event event;
	stateStack->registerState<TitleState>(StatesID::Title);
	stateStack->registerState<MenuState>(StatesID::Menu);
	stateStack->registerState<GameState>(StatesID::Game);
	stateStack->registerState<PauseState>(StatesID::Pause);
	stateStack->registerState<PassedLevel>(StatesID::PassedLevel);
	stateStack->registerState<GameOver>(StatesID::GameOver);
	stateStack->pushState(StatesID::Title);

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
						stateStack->handleEvent(event);

						if (event.type == sf::Event::Closed)
							m_RenWindow.close();
					}
					stateStack->update(TimePerFrame);

				// Check inside this loop, because stack might be empty before update() call
				if (stateStack->isEmpty())
					m_RenWindow.close();
			}

			//updateStatistics(dt);
			m_RenWindow.clear();

			stateStack->draw();

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

