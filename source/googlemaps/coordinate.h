#ifndef COORDINATE_H_
#define COORDINATE_H_

namespace googlemaps {

class BitmapCoordinate;

class Coordinate
{
	public:
		Coordinate(double lat, double lng);

		Coordinate(const BitmapCoordinate &coord);

		double latitude;
		double longitude;
};

}

#endif
