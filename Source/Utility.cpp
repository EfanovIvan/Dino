#include <Utility.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include <cmath>
#include <future>
#include <thread>

void centerOrigin(sf::Sprite& sprite)
{
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}

void centerOrigin(sf::Text& text)
{
	sf::FloatRect bounds = text.getLocalBounds();
	text.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}
std::string getElapsedTimeLevel(unsigned int i)
{
	int minut =  0;
	int second = 0;
	while(i > 60)
	{
		minut++;
		i -=60;
	}
	second = i;
	if(minut < 10 && second < 10)
	 	return std::string("0" + std::to_string(minut)
	 	 + ":" + "0" + std::to_string(second));
	if(minut < 10 && second >= 10)
		return std::string("0" + std::to_string(minut)
	 	 + ":"  + std::to_string(second));
	 if(minut >= 10 && second >= 10)
		return std::string(std::to_string(minut)
	 	 + ":"  + std::to_string(second));
}
