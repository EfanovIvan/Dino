/*
 * ParserXML.cpp
 *
 *  Created on: 22 февр. 2019 г.
 *      Author: ivan
 */

#include <ParserXML.hpp>
#include <string>
#include <stdexcept>
ParserXML::ParserXML()
{}

ParserXML::ParserXML(std::string const& pathFile)
{
	loadFile(pathFile);
}
void ParserXML::loadFromFile(std::string const& pathFile)
{
	loadFile(pathFile);
}
TiXmlElement* ParserXML::getRootElement()
{
	return m_doc.RootElement();
}

void ParserXML::loadFile(std::string const& pathFile)
{
	m_doc.LoadFile(pathFile.c_str());
		if(!m_doc.LoadFile())
			throw std::runtime_error("bad parse");
}
void ParserXML::clear()
{
	m_doc.Clear();
}
