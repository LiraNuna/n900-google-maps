#include "geom/point.h"

#ifndef BITMAPCOORDINATE_H_
#define BITMAPCOORDINATE_H_

namespace googlemaps
{

class BitmapCoordinate : public geom::Point
{
	public:
		BitmapCoordinate(int x, int y, int zoom);

		int zoom;
};

}

#endif
