#ifndef BITMAPCOORDINATE_H_
#define BITMAPCOORDINATE_H_

#include <QPoint>

namespace googlemaps
{

class Coordinate;

class BitmapCoordinate : public QPoint
{
	public:
		BitmapCoordinate(int x, int y, int zoom);

		BitmapCoordinate(const Coordinate &coord, int zoom);

		double pixelsPerDegree() const;

		double pixelsPerRadian() const;

		int origin() const;

		inline int zoom() const {
			return _zoom;
		}

	protected:
		int _zoom;
};

}

#endif
