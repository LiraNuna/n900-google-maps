#include "googlemapwidget.h"
#include <QPainter>
#include <QRect>
#include <QPoint>

GoogleMapWidget::GoogleMapWidget(QWidget *parent):
	QGLWidget(parent),
	tile(1, 1, QImage::Format_ARGB32)
{

}

void GoogleMapWidget::paintGL()
{
	QPainter painter(this);

	painter.drawImage(tile.rect().translated(translation), tile);
}

void GoogleMapWidget::mousePressEvent(QMouseEvent* event)
{
	dragStart = QPoint(event->x(), event->y());
}

void GoogleMapWidget::mouseMoveEvent(QMouseEvent* event)
{
	translation += event->pos() - dragStart;
	dragStart = event->pos();

	updateGL();
}
