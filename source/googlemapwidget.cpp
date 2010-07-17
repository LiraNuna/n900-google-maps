#include "googlemapwidget.h"

GoogleMapWidget::GoogleMapWidget(QWidget *parent):
	QGLWidget(parent)
{

}

void GoogleMapWidget::paintGL()
{
	QPainter painter(this);

	for(int x=0; x<6; ++x) {
		for(int y=0; y<6; ++y) {
			QRect rect = tile.rect().translated(x * 256, y * 256);
			painter.drawImage(rect.translated(translation), tile);
		}
	}

	painter.end();
}

void GoogleMapWidget::mousePressEvent(QMouseEvent* event)
{
	dragStart = QPoint(event->x(), event->y());
}

void GoogleMapWidget::mouseMoveEvent(QMouseEvent* event)
{
	translation += event->pos() - dragStart;
	dragStart = event->pos();

	update();
}
