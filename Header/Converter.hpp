/*
 * converter.hpp
 *
 *  Created on: 29 янв. 2019 г.
 *      Author: ivan
 */

#ifndef HEADER_CONVERTER_HPP_
#define HEADER_CONVERTER_HPP_
namespace converter
{
	constexpr double PIXELS_PER_METERS = 32.0;
	constexpr double PI = 3.14159265358979323846;
	template<typename T>
	constexpr T pixelsToMeters(const T& x){return x/32.0;};
	template<typename T>
	constexpr T metersToPixels(const T& x){return x*32.0;};
	template<typename T>
	constexpr T degToRad(const T& x){return 3.14159*x/180.0;};
	template<typename T>
	constexpr T radToDeg(const T& x){return 180.0*x/3.14159;}
}




#endif /* HEADER_CONVERTER_HPP_ */
