#ifndef BITMAPCOORDINATE_H_
#define BITMAPCOORDINATE_H_

#include "coordinate.h"
#include <QPoint>

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

		BitmapCoordinate operator+ (const QPoint &) const;

		BitmapCoordinate operator- (const QPoint &) const;

	protected:
		int _zoom;
};

#endif
