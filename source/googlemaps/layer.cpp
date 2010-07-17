#include "layer.h"

	// This serves both allTiles indirectly as well as pendingTiles
uint qHash(const QUrl &url)
{
	return qHash(url.toString());
}

uint qHash(const googlemaps::Tile &tile)
{
		// Since a URL for the tile is unique, use that as a hash
	return qHash(tile.url());
}

namespace googlemaps
{

Layer::Layer(const QString &name, bool realTime):
	QObject(NULL),
	name(name), realTime(realTime)
{
		// Network access will also take care of caching if wanted
	network = new QNetworkAccessManager();

		// Create separate network cache for each layer.
		// If tiles are not realtime (such as Traffic data)
	if(!realTime) {
		QNetworkDiskCache *cache = new QNetworkDiskCache(network);
		cache->setCacheDirectory("cache/" + name);
		network->setCache(cache);
	}

		// When a tile finishes downloading, fill up the cache
	connect(network, SIGNAL(finished(QNetworkReply*)), this, SLOT(downloadFinished(QNetworkReply*)));
}

void Layer::downloadFinished(QNetworkReply* reply)
{
	const QUrl &url = reply->url();
	const Tile &tile = pendingTiles.value(url, Tile(BitmapCoordinate(0, 0, 0)));

		// Keep the image in cache
	allTiles.insert(tile, QImage::fromData(reply->readAll()));

		// No more a pending tile
	pendingTiles.remove(url);

		// Notify listeners that a tile had been updated.
	emit tileUpdated(tile);
}

QImage Layer::getBitmap(const Tile &tile)
{
		// Image had been cached, return it
	if(allTiles.contains(tile))
		return allTiles[tile];

		// Image had not yet been loaded, send a request
	QUrl tileUrl = tile.url();
	QNetworkRequest request = QNetworkRequest(tileUrl);

		// Unless the layer is a realtime one, prefer cache
	request.setAttribute(QNetworkRequest::CacheLoadControlAttribute,
			realTime ? QNetworkRequest::AlwaysNetwork : QNetworkRequest::PreferCache);

		// Keep the pending tile for the slot
	pendingTiles.insert(tileUrl, tile);

		// Perform the request. If it's cached, the cached file will be loaded.
	network->get(request);

		// Send a blank image (will return as QImage.isNull() == true)
	return QImage();
}

}
