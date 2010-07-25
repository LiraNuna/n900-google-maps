#include "layer.h"

	// This serves both allTiles indirectly as well as pendingTiles
uint qHash(const QUrl &url)
{
	return qHash(url.toString());
}

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
	const QString &tileId = pendingTiles.value(url);

		// Keep the image in cache
	tiles.insert(tileId, QImage::fromData(reply->readAll()));

		// No more a pending tile
	pendingTiles.remove(url);

		// Notify listeners that a tile had been updated.
	emit tileUpdated(Tile::fromId(tileId));
}

QImage Layer::getBitmap(const QString &tileId)
{
		// Image had been cached, return it
	if(isTileLoaded(tileId))
		return tiles[tileId];

		// Image had not yet been loaded, send a request
	retrieveBitmap(tileId);

		// Send a blank image (will return as QImage.isNull() == true)
	return QImage();
}

void Layer::retrieveBitmap(const QString &tileId)
{
	QUrl tileUrl = Tile::fromId(tileId).url();
	QNetworkRequest request = QNetworkRequest(tileUrl);

		// Unless the layer is a realtime one, prefer cache
	request.setAttribute(QNetworkRequest::CacheLoadControlAttribute,
			realTime ? QNetworkRequest::AlwaysNetwork : QNetworkRequest::PreferCache);

		// Keep the pending tile for the slot
	pendingTiles.insert(tileUrl, tileId);

		// Perform the request. If it's cached, the cached file will be loaded.
	network->get(request);
}

bool Layer::isTileLoaded(const QString &id)
{
	return tiles.contains(id);
}

bool Layer::isTileLoading(const QString &id)
{
	return pendingTiles.values().contains(id);
}
