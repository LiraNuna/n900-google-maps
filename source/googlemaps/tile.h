#ifndef TILE_H_
#define TILE_H_

#include <QImage>
#include <QUrl>
#include "bitmapcoordinate.h"

namespace googlemaps
{

class Tile : public QImage
{
	public:
		static const unsigned int SIZE;

		Tile(const BitmapCoordinate &coord);

		Tile(int x, int y, int zoom);

		inline const BitmapCoordinate &index() {
			return idx;
		}

		QString id();

		QUrl url();

	protected:
		BitmapCoordinate idx;
};

}

#endif
