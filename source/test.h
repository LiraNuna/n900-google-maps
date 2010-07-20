#include <QNetworkReply>
#include <QImage>
#include <cstdio>

#include "googlemapwidget.h"

class Listener : public QObject
{
	Q_OBJECT

	public slots:
		void finishedDownload(QNetworkReply* reply) {
			printf("Network reply!\n");
			GoogleMapWidget* map = new GoogleMapWidget();

			map->tile = QImage::fromData(reply->readAll());

			map->setFixedSize(800, 480);
			map->show();
		}
};
