#include "googlemapwidget.h"

const GLint tileVertexies[] = {
	  0, 256,
	256, 256,
	  0,   0,
	256,   0,
};

const GLint tileTexCoords[] = {
	0, 0,
	1, 0,
	0, 1,
	1, 1,
};

const GLfloat identityMatrix[] = {
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1,
};

GoogleMapWidget::GoogleMapWidget(QWidget *parent):
	QGLWidget(parent),
	tile(1, 1, QImage::Format_ARGB32)
{

}

void GoogleMapWidget::initializeGL()
{
	glLoadMatrixf(identityMatrix);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(2, GL_INT, 0, tileVertexies);
	glTexCoordPointer(2, GL_INT, 0, tileTexCoords);
}

void GoogleMapWidget::resizeGL(int width, int height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(identityMatrix);

	glViewport(0, 0, width, height);
	glOrtho(0, width, height, 0, 0, 1);
}

void GoogleMapWidget::paintGL()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(identityMatrix);

	glClear(GL_COLOR_BUFFER_BIT);

	if(!tile.isNull())
		bindTexture(tile);

	glTranslatef(translation.x(), translation.y(), 0);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
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
