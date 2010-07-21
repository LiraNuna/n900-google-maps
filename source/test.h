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

#ifdef Q_WS_MAEMO_5
			map->setAttribute(Qt::WA_Maemo5AutoOrientation, true);
			map->showFullScreen();
#else
			map->setFixedSize(800, 480);
			map->show();
#endif
		}
};
