#include <QtCore>
#include <QtNetwork>
#include "tile.h"

#ifndef LAYER_H_
#define LAYER_H_

namespace googlemaps
{

class Layer : public QObject
{
	Q_OBJECT

	public:
		Layer(const QString &name, bool realTime = false);

		void draw(QPainter *paintDevice, const Coordinate &center);

		QImage getBitmap(const Tile &tile);

	protected:
		void fillTilesBitmap();

		QString name;
		bool realTime;

		QList<Tile *> tiles;
		QNetworkAccessManager* network;

		QHash<Tile, QImage> allTiles;
		QHash<QUrl, Tile> pendingTiles;

	protected slots:
		void downloadFinished(QNetworkReply* reply);

	signals:
		void tileUpdated(const Tile &);
};

}

#endif
