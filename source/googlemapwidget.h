#include <QGLWidget>
#include <QMouseEvent>
#include <QPoint>
#include <QImage>

#ifndef GOOGLEMAPWIDGET_H_
#define GOOGLEMAPWIDGET_H_

class GoogleMapWidget : public QGLWidget
{
	Q_OBJECT

	public:
		GoogleMapWidget(QWidget *parent = 0);

		QImage tile;

		QPoint translation;
		QPoint dragStart;

	protected:
		void paintGL();

		void mousePressEvent(QMouseEvent* );

		void mouseMoveEvent(QMouseEvent* );
};

#endif
