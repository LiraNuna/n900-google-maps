#include <QApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkDiskCache>
#include <QImage>

#include <cmath>

#include "test.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	Listener test;

	QNetworkAccessManager* man = new QNetworkAccessManager();
	QObject::connect(man, SIGNAL(finished(QNetworkReply*)), &test, SLOT(finishedDownload(QNetworkReply*)));

	QNetworkDiskCache *diskCache = new QNetworkDiskCache();
	diskCache->setCacheDirectory("cache");
	man->setCache(diskCache);

	QNetworkRequest request(QUrl("http://mt1.google.com/vt/lyrs=m@128&x=1310&y=3167&z=13"));
	request.setAttribute(QNetworkRequest::CacheLoadControlAttribute, QNetworkRequest::PreferCache);
	man->get(request);

	return app.exec();
}
