#include "tile.h"

const int Tile::SIZE = 256;

Tile::Tile(const BitmapCoordinate &coord):
	idx(coord.x() / SIZE, coord.y() / SIZE, coord.zoom())
{

}

Tile::Tile(int x, int y, int zoom):
	idx(x, y, zoom)
{

}

Tile Tile::fromId(const QString &id)
{
	int x = 0;
	int y = 0;

	for(int i=0; i<id.length(); ++i) {
		char c = id[i].toAscii() - 't';

		x = (x << 1) | (c & 1);
		y = (y << 1) | ((c & 3) >> 1);
	}

	return Tile(x, y, id.length());
}

QString Tile::id() const
{
	QString id;

	QPoint copy = idx;
	for(int i=0; i<idx.zoom(); ++i) {
		id.insert(0, "tvuw"[(copy.x() & 1) + ((copy.y() & 1) * 2)]);

		copy.rx() >>= 1;
		copy.ry() >>= 1;
	}

	return id;
}

QUrl Tile::url() const
{
	/*
	 * %1 = Layer name and options (TODO)
	 * %2 = X coordinate of the tile
	 * %3 = Y coordinate of the tile
	 * %4 = Zoom
	 */
	return QString("http://mt0.google.com/vt/lyrs=%1&x=%2&y=%3&z=%4")
			// TODO: Layers
		.arg("m@128")
			// X coordinate of tile
		.arg(idx.x())
			// Y coordinate of tile
		.arg(idx.y())
			// Zoom
		.arg(idx.zoom());
}
