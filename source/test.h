#include <QNetworkReply>
#include <QImage>
#include <cstdio>

#include "googlemapwidget.h"

class Listener : public QObject
{
	Q_OBJECT

	public slots:
		void finishedDownload(QNetworkReply* reply) {
			GoogleMapWidget* map = new GoogleMapWidget();
			map->setFixedSize(800, 480);
			map->show();

			map->tile = QImage::fromData(reply->readAll());
		}
};
