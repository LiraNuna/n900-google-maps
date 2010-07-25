#include <QtCore>
#include <QtNetwork>

#include "googlemapwidget.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	GoogleMapWidget map;

#ifdef Q_WS_MAEMO_5
	map.setAttribute(Qt::WA_Maemo5AutoOrientation, true);
	map.showFullScreen();
#else
	map.setFixedSize(800, 480);
	map.show();
#endif

	return app.exec();
}
