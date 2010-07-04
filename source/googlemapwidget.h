#include <QGLWidget>
#include <QMouseEvent>
#include <QPoint>

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
		void initializeGL();

		void resizeGL(int width, int height);

		void paintGL();

		void mousePressEvent(QMouseEvent* event);

		void mouseMoveEvent(QMouseEvent* event);
};

#endif
