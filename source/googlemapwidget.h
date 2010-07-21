#ifndef GOOGLEMAPWIDGET_H_
#define GOOGLEMAPWIDGET_H_

#include <QtCore>
#include <QtOpenGL>

class GoogleMapWidget : public QGLWidget
{
	Q_OBJECT

	public:
		GoogleMapWidget(QWidget *parent = 0);

		QImage tile;

		QPoint translation;
		QPoint dragStart;

	protected slots:
		void initializeGL();

		void resizeGL(int width, int height);

		void paintGL();

		void mousePressEvent(QMouseEvent* );

		void mouseMoveEvent(QMouseEvent* );

	private:
		GLuint textureId;
		GLuint shaderProgram;
};

#endif
