/*
 * ParserXML.hpp
 *
 *  Created on: 22 февр. 2019 г.
 *      Author: ivan
 */

#ifndef HEADER_PARSERXML_HPP_
#define HEADER_PARSERXML_HPP_
#include <string>
#include <tinyxml.h>
#include <tinystr.h>
class ParserXML
{
public:
	ParserXML();
	ParserXML(std::string const& pathFile);
	void loadFromFile(std::string const& pathFile);
	TiXmlElement* getRootElement();
	void clear();
private:
	void loadFile(std::string const&pathFile);

private:
	TiXmlDocument m_doc;
};

#endif /* HEADER_PARSERXML_HPP_ */
