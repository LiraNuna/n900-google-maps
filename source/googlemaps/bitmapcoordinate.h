#ifndef BITMAPCOORDINATE_H_
#define BITMAPCOORDINATE_H_

#include "geom/point.h"

namespace googlemaps
{

class Coordinate;

class BitmapCoordinate : public geom::Point
{
	public:
		BitmapCoordinate(int x, int y, int zoom);

		BitmapCoordinate(const Coordinate &coord, int zoom);

		double pixelsPerDegree() const;

		double pixelsPerRadian() const;

		int origin() const;

		int zoom;
};

}

#endif
