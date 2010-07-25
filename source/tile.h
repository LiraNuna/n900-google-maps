#ifndef TILE_H_
#define TILE_H_

#include <QtCore>
#include "bitmapcoordinate.h"

class Tile
{
	public:
		static const int SIZE;

		Tile(const BitmapCoordinate &coord);

		Tile(int x, int y, int zoom);

		static Tile fromId(const QString &id);

		inline const BitmapCoordinate &index() {
			return idx;
		}

		inline int x() const {
			return idx.x();
		}

		inline int y() const {
			return idx.y();
		}

		inline int zoom() const {
			return idx.zoom();
		}

		QString id() const;

		QUrl url() const;

	protected:
		BitmapCoordinate idx;
};

#endif
