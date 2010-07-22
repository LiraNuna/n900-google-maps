#ifndef TILE_H_
#define TILE_H_

#include <QtCore>
#include "bitmapcoordinate.h"

namespace googlemaps
{

class Tile
{
	public:
		static const unsigned int SIZE;

		Tile(const BitmapCoordinate &coord);

		Tile(int x, int y, int zoom);

		inline const BitmapCoordinate &index() {
			return idx;
		}

		QString id() const;

		QUrl url() const;

	protected:
		BitmapCoordinate idx;
};

}

#endif
