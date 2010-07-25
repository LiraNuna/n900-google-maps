#ifndef GOOGLEMAPWIDGET_H_
#define GOOGLEMAPWIDGET_H_

#include <QtCore>
#include <QtOpenGL>
#include "layer.h"

class GoogleMapWidget : public QGLWidget
{
	Q_OBJECT

	public:
		GoogleMapWidget(QWidget *parent = 0);

		QImage tile;

	protected:
		QPoint translation;
		QPoint dragStart;

		QGLShaderProgram renderer;

		QVector<QVector2D > vbo;

	protected slots:
		void initializeGL();

		void resizeGL(int width, int height);

		void paintGL();

		void mousePressEvent(QMouseEvent* );

		void mouseMoveEvent(QMouseEvent* );

	private:
		GLuint textureId;

		int gridWidth;
		int gridHeight;

		QVector<QVector2D > generateTile(const QVector2D &position);
};

#endif
