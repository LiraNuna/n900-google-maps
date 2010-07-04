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

			if(reply->attribute(QNetworkRequest::SourceIsFromCacheAttribute).toBool())
				printf("Reply is from cache\n");

			printf("%s\n", reply->rawHeader("Cache-Control").data());

			map->tile = QImage::fromData(reply->readAll());
		}
};
