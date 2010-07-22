#include <cmath>
#include "coordinate.h"
#include "bitmapcoordinate.h"

Coordinate::Coordinate(double lat, double lng):
	latitude(lat), longitude(lng)
{

}

Coordinate::Coordinate(const BitmapCoordinate &coord)
{
	double x = (coord.y() - coord.origin()) / coord.pixelsPerRadian();
	double y = (coord.x() - coord.origin()) / coord.pixelsPerDegree();

	latitude  = (2 * atan(exp(-x)) - (M_PI / 2)) / (M_PI / 180);
	longitude = y;
}
