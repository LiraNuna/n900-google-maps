#include "bitmapcoordinate.h"

#ifndef COORDINATE_H_
#define COORDINATE_H_

namespace googlemaps {

class Coordinate
{
	public:
		Coordinate(double lat, double lng, double alt = 0.0);

		BitmapCoordinate toBitmapCoordinate();

		double latitude;
		double longitude;
		double altitude;
};

}

#endif
