#include <QImage>

#ifndef TILE_H_
#define TILE_H_

namespace googlemaps
{

class Tile : public QImage
{
	public:
		static const unsigned int SIZE;
};

}

#endif
