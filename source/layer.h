#ifndef LAYER_H_
#define LAYER_H_

#include <QtCore>
#include <QtNetwork>
#include <QImage>
#include "tile.h"

class Layer : public QObject
{
	Q_OBJECT

	public:
		Layer(const QString &name, bool realTime = false);

		QImage getBitmap(const QString &tileId);

	protected:
		void fillTilesBitmap();

		QString name;
		bool realTime;

		QNetworkAccessManager* network;

		QHash<QString, QImage> tiles;
		QHash<QUrl, QString> pendingTiles;

	protected slots:
		void downloadFinished(QNetworkReply* reply);

	signals:
		void tileUpdated(const Tile &);
};

#endif
