/*
 * LevelParser.cpp
 *
 *  Created on: 8 янв. 2019 г.
 *      Author: ivan
 */

#include <LevelParser.hpp>
#include <cstdlib>
 LevelParser::LevelParser( char const*  pathFile, Level& level)
 {



	     TiXmlDocument levelFile(pathFile);

	 	// Загружаем XML-карту
	     if(!levelFile.LoadFile())
	     {
	         std::cout << "Loading level \""
	        		 << pathFile << "\" failed." << std::endl;
	     }

	 	// Работаем с контейнером map
	     TiXmlElement *map;
	     map = levelFile.FirstChildElement("map");

	 	// Пример карты: <map version="1.0" orientation="orthogonal"
	 	// width="10" height="10" tilewidth="34" tileheight="34">
	     level.m_mapWidth = atoi(map->Attribute("width"));
	     level.m_mapHeight = atoi(map->Attribute("height"));
	     level.m_tileWidth = atoi(map->Attribute("tilewidth"));
	     level.m_tileHeight = atoi(map->Attribute("tileheight"));

	 	// Берем описание тайлсета и идентификатор первого тайла
	     TiXmlElement *tilesetElement;
	     tilesetElement = map->FirstChildElement("tileset");
	     level.m_firstTileID = atoi(tilesetElement->Attribute("firstgid"));

	 	// source - путь до картинки в контейнере image
	     TiXmlElement *image;
	     image = tilesetElement->FirstChildElement("image");
	     std::string imagepath = std::string("Media/") +
	    		 image->Attribute("source");

	 	// Пытаемся загрузить тайлсет
	 	sf::Image img;

	     if(!img.loadFromFile(imagepath))
	     {
	         std::cout << "Failed to load tile sheet." << std::endl;
	     }

	 	// Очищаем карту от света (109, 159, 185)
	 	// Вообще-то в тайлсете может быть фон любого цвета, но я не нашел решения, как 16-ричную строку
	 	// вроде "6d9fb9" преобразовать в цвет
	     img.createMaskFromColor(sf::Color(109, 159, 185));

	 	// Грузим текстуру из изображения
	 	level.m_tilesetImage.loadFromImage(img);

	 	// Расплывчатость запрещена
	     level.m_tilesetImage.setSmooth(false);

	 	// Получаем количество столбцов и строк тайлсета
	 	int columns = level.m_tilesetImage.getSize().x / level.m_tileWidth;
	    int rows = level.m_tilesetImage.getSize().y / level.m_tileHeight;

	 	// Вектор из прямоугольников изображений (TextureRect)

	     std::vector<sf::Rect<int>> subRects;
	     subRects.reserve(columns * rows);

	 	for(int y = 0; y < rows; y++)
	 	for(int x = 0; x < columns; x++)
	 	{
	 		sf::Rect<int> rect;

	 		rect.top = y * level.m_tileHeight;
	 		rect.height = level.m_tileHeight;
	 		rect.left = x * level.m_tileWidth;
	 		rect.width = level.m_tileWidth;

	 		subRects.push_back(rect);
	 	}



	 	// Работа со слоями
	     TiXmlElement *layerElement;
	     layerElement = map->FirstChildElement("layer");
	     while(layerElement)
	     {
	         Layer layer;

	 		// Если присутствует opacity, то задаем прозрачность слоя, иначе он полностью непрозрачен
	         if (layerElement->Attribute("opacity") != NULL)
	         {
	             float opacity = strtod(layerElement->Attribute("opacity"), NULL);
	             layer.opacity = 255 * opacity;
	         }
	         else
	         {
	             layer.opacity = 255;
	         }

	 		// Контейнер <data>
	         TiXmlElement *layerDataElement;
	         layerDataElement = layerElement->FirstChildElement("data");

	         if(layerDataElement == NULL)
	         {
	             std::cout << "Bad map. No layer information found." << std::endl;
	         }

	 		// Контейнер <tile> - описание тайлов каждого слоя
	         TiXmlElement *tileElement;
	         tileElement = layerDataElement->FirstChildElement("tile");

	         if(tileElement == NULL)
	         {
	             std::cout << "Bad map. No tile information found." << std::endl;

	         }

	         int x = 0;
	         int y = 0;

	         while(tileElement)
	         {
	         	//if(tileElement->Value())
	         		//tileElement = tileElement->NextSiblingElement("tile");
	         	int tileGID;
	         	if(tileElement->Attribute("gid"))
	         		tileGID = atoi(tileElement->Attribute("gid"));
	         	else tileGID = 0;

	             int subRectToUse = tileGID - level.m_firstTileID;

	 			// Устанавливаем TextureRect каждого тайла
	             if (subRectToUse >= 0)
	             {
	                 sf::Sprite sprite;
	                 sprite.setTexture(level.m_tilesetImage);
	                 sprite.scale(1.004, 1.0);
	 				sprite.setTextureRect(subRects[subRectToUse]);
	                 sprite.setPosition(x * level.m_tileWidth,
	                		 y * level.m_tileHeight);
	                 sprite.setColor(sf::Color(255, 255, 255, layer.opacity));

	                 layer.tiles.push_back(sprite);
	             }

	             tileElement = tileElement->NextSiblingElement("tile");

	             x++;
	             if (x >= level.m_mapWidth)
	             {
	                 x = 0;
	                 y++;
	                 if(y >= level.m_mapHeight)
	                     y = 0;
	             }
	         }

	         level.m_layers.push_back(layer);

	         layerElement = layerElement->NextSiblingElement("layer");
	     }

	      //Работа с объектами
	     TiXmlElement *objectGroupElement;

	 	// Если есть слои объектов
	     if (map->FirstChildElement("objectgroup") != NULL)
	     {
	         objectGroupElement = map->FirstChildElement("objectgroup");
	         while (objectGroupElement)
	         {
	 			// Контейнер <object>
	             TiXmlElement *objectElement;
	             objectElement = objectGroupElement->FirstChildElement("object");

	 			while(objectElement)
	             {
	 				//находим фон для каждого уровня

	 				  if(objectElement->Attribute("name")
	 						  	  	  	  	  == std::string("BG"))
	 					{
	 					  if(!level.m_TextureBG.loadFromFile(
	 							 objectElement->Attribute("type")))
	 						 throw std::runtime_error
							 ("can't load file for textur");
	 					  level.m_BG.setTexture(level.m_TextureBG);
	 					 level.m_BG.setOrigin(level.m_TextureBG.getSize().x/2,
	 							level.m_TextureBG.getSize().y/2);
	 					  break;

	 					}
	 				// Получаем все данные - тип, имя, позиция, etc
	                 std::string objectType;
	                 if (objectElement->Attribute("type") != NULL)
	                 {
	                     objectType = objectElement->Attribute("type");
	                 }
	                 std::string objectName;
	                 if (objectElement->Attribute("name") != NULL)
	                 {
	                     objectName = objectElement->Attribute("name");
	                 }
	                 int x = atoi(objectElement->Attribute("x"));
	                 int y = atoi(objectElement->Attribute("y"));

	 				int width, height;

	 				sf::Sprite sprite;
	                 sprite.setTexture(level.m_tilesetImage);
	 				sprite.setTextureRect(sf::Rect<int>(0,0,0,0));
	                 sprite.setPosition(x, y);

	 				if (objectElement->Attribute("width") != NULL)
	 				{
	 					width = atoi(objectElement->Attribute("width"));
	 					height = atoi(objectElement->Attribute("height"));
	 				}
	 				else
	 				{
	 					width = subRects[atoi(objectElement->
	 							Attribute("gid")) - level.m_firstTileID].width;
	 					height = subRects[atoi(objectElement->
	 							Attribute("gid")) - level.m_firstTileID].height;
	 					sprite.setTextureRect(subRects[atoi(objectElement->
	 							Attribute("gid")) - level.m_firstTileID]);
	 				}

	 				// Экземпляр объекта
	                 Object object;
	                 object.name = objectName;
	                 object.type = objectType;
	 				object.sprite = sprite;

	                 sf::Rect <float> objectRect;
	                 objectRect.top = y;
	                 objectRect.left = x;
	 				objectRect.height = height;
	 				objectRect.width = width;
	                 object.rect = objectRect;

	 				// "Переменные" объекта
	                 TiXmlElement *properties;
	                 properties = objectElement->FirstChildElement("properties");
	                 if (properties != NULL)
	                 {
	                     TiXmlElement *prop;
	                     prop = properties->FirstChildElement("property");
	                     if (prop != NULL)
	                     {
	                         while(prop)
	                         {
	                             std::string propertyName = prop->Attribute("name");
	                             std::string propertyValue = prop->Attribute("value");

	                             object.properties[propertyName] = propertyValue;

	                             prop = prop->NextSiblingElement("property");
	                         }
	                     }
	                 }

	 				// Пихаем объект в вектор
	                 level.m_objects.push_back(object);

	                 objectElement = objectElement->NextSiblingElement("object");
	             }
	             objectGroupElement = objectGroupElement->NextSiblingElement("objectgroup");
	         }
	     }
	     else
	     {
	         std::cout << "No object layers found..." << std::endl;
	     }


 }
