
#ifndef LEVEL_HPP_
#define LEVEL_HPP_


#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <ResourceIdentifiers.hpp>
#include <State.hpp>
class LevelParser;

struct Object
{
	int GetPropertyInt(std::string name);//номер свойства объекта в нашем списке
	float GetPropertyFloat(std::string name);
	std::string GetPropertyString(std::string name);

	std::string name;//объявили переменную name типа string
	std::string type;//а здесь переменную type типа string
	sf::Rect<float> rect;//тип Rect с нецелыми значениями
	std::map<std::string, std::string> properties;//создаём ассоциатиный массив. ключ - строковый тип, значение - строковый

	sf::Sprite sprite;//объявили спрайт

};

struct Layer//слои
{
	int opacity;//непрозрачность слоя
	std::vector<sf::Sprite> tiles;//закидываем в вектор тайлы
};

class Level : public sf::Drawable//главный класс - уровень
{

	friend class LevelParser;


public:

	Object GetObject(std::string name);
	std::vector<Object> GetObjects(std::string name);//выдаем объект в наш уровень
	std::vector<Object> GetAllObjects();//выдаем все объекты в наш уровень
	sf::Vector2i GetTileSize();//получаем размер тайла
	virtual void draw(sf::RenderTarget& target,
									sf::RenderStates states)const override;
private:
	int m_mapWidth, m_mapHeight;
	int m_tileWidth, m_tileHeight;
	int m_firstTileID;//получаем айди первого тайла
	//sf::Rect<float> m_drawingBounds;//размер части карты которую рисуем
	sf::Texture m_tilesetImage;//текстура карты

	//std::vector<sf::Rect<int>> m_mapRects;
	sf::Image img;
	std::vector<Object> m_objects;//массив типа Объекты, который мы создали
	std::vector<Layer> m_layers;
};

///////////////////////////////////////


#endif /* LEVEL_HPP_ */
