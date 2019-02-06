/*
 * level.cpp
 *
 *  Created on: 6 авг. 2018 г.
 *      Author: ivan
 */

#include <Level.hpp>
#include <iostream>
#include "tinyxml.h"
#include "tinystr.h"

using namespace std;
using namespace sf;

int Object::GetPropertyInt(string name)
{
    return atoi(properties[name].c_str());
}

float Object::GetPropertyFloat(string name)
{
    return (float)strtod(properties[name].c_str(), NULL);
}

string Object::GetPropertyString(string name)
{
    return properties[name];
}


Object Level::GetObject(string name)
{
    for (unsigned int i = 0; i < m_objects.size(); i++)
        if (m_objects[i].name == name)
            return m_objects[i];
}

vector<Object> Level::GetObjects(string name)
{
    vector<Object> vec;
    for (unsigned int i = 0; i < m_objects.size(); i++)
        if (m_objects[i].name == name)
        {
            vec.push_back(m_objects[i]);
        }
    return vec;
}
vector<Object> Level::GetAllObjects()
{
	return m_objects;
}

Vector2i Level::GetTileSize()
{
    return Vector2i(m_tileWidth, m_tileHeight);
}

void Level::Draw(RenderWindow &window)
{
    for (unsigned int layer = 0; layer < m_layers.size(); layer++)
        for (unsigned int tile = 0; tile < m_layers[layer].tiles.size();
        														tile++)
            window.draw(m_layers[layer].tiles[tile]);
   // std::cout << "render map\n";
}










