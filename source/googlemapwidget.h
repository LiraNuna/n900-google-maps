#ifndef GOOGLEMAPWIDGET_H_
#define GOOGLEMAPWIDGET_H_

#include <QtOpenGL>

#include "layer.h"
#include "bitmapcoordinate.h"

class GoogleMapWidget : public QGLWidget
{
	Q_OBJECT

	public:
		GoogleMapWidget(QWidget *parent = 0);

		void setCenter(const BitmapCoordinate &bcoord);

	protected:
		QPoint dragStart;
		QPoint canvasSize;

		Layer tileCache;
		BitmapCoordinate center;
		QGLShaderProgram renderer;
		QHash<QString, int> boundTiles;

		QVector<QVector2D > vbo;


	protected slots:
		void initializeGL();

		void resizeGL(int width, int height);

		void paintGL();

		void tileUpdated(const QString &id);

		void mousePressEvent(QMouseEvent* );

		void mouseMoveEvent(QMouseEvent* );

	private:
		GLuint textureId;

		int gridWidth;
		int gridHeight;

		QVector<QVector2D > generateTile(const QVector2D &position);
};

#endif
