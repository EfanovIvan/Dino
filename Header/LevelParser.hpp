/*
 * LevelParser.hpp
 *
 *  Created on: 8 янв. 2019 г.
 *      Author: ivan
 */

#ifndef HEADER_LEVELPARSER_HPP_
#define HEADER_LEVELPARSER_HPP_
#include <string>
#include <tinyxml.h>
#include <tinystr.h>
#include <Level.hpp>
#include <stdexcept>
class LevelParser {
public:

	 LevelParser( char const*  pathFile, Level& level);

};

#endif /* HEADER_LEVELPARSER_HPP_ */
