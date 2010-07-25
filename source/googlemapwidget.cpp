#include "googlemapwidget.h"
#include <cstdio>

GoogleMapWidget::GoogleMapWidget(QWidget *parent):
	QGLWidget(parent)
{

}

void GoogleMapWidget::initializeGL()
{
	renderer.addShaderFromSourceCode(QGLShader::Fragment,
		"uniform sampler2D textureId;"

		"varying lowp vec2 texCoords;"

		"void main(void)"
		"{"
			"gl_FragColor = texture2D(textureId, texCoords);"
		"}"
	);

	renderer.addShaderFromSourceCode(QGLShader::Vertex,
		"attribute vec4	position;"
		"attribute vec4	texture;"

		"uniform vec2 size;"
		"uniform vec4 translation;"

		"varying vec2 texCoords;"

		"mat4 modelViewProjectionMatrix = mat4("
			"2.0 / size.x, 0.0, 0.0, -1.0,"
			"0.0, -2.0 / size.y, 0.0, 1.0,"
			"0.0, 0.0,-2.0,-1.0,"
			"0.0, 0.0, 0.0, 1.0"
		");"

		"void main(void)"
		"{"
			"gl_Position = (position + translation) * modelViewProjectionMatrix;"
			"texCoords = texture.st;"
		"}"
	);

	if(!renderer.link())
		qDebug() << renderer.log();

	renderer.bind();

	renderer.enableAttributeArray("position");
	renderer.enableAttributeArray("texture");

	textureId = bindTexture(tile);
}

void GoogleMapWidget::resizeGL(int width, int height)
{
		// New viewport
	glViewport(0, 0, width, height);

		// Let the shader know the size
		// TODO: Send a new matrix
	renderer.setUniformValue("size", width, height);

		// Tile for each side + tiles on screen
	gridWidth  = 1 + ((width  / Tile::SIZE) + 1) + 1;
	gridHeight = 1 + ((height / Tile::SIZE) + 1) + 1;

		// Clear all vertices
	vbo.clear();

		// Reserve exact size for the VBO, since we know the size in advance
		// 4 Vertices per tile
	vbo.reserve((gridWidth * 4) * (gridHeight * 4));

		// Generate the grid starting from outside the screen
	for(int y=-1; y<gridWidth-1; ++y) {
		for(int x=-1; x<gridWidth-1; ++x)
			vbo << generateTile(QVector2D(x, y));
	}

		// Set the generated VBO data
	renderer.setAttributeArray("position", vbo.constData() + 0, sizeof(QVector2D) * 2);
	renderer.setAttributeArray("texture",  vbo.constData() + 1, sizeof(QVector2D) * 2);
}

void GoogleMapWidget::paintGL()
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	for(int i=0; i<gridWidth*gridHeight; ++i) {
		glBindTexture(GL_TEXTURE_2D, textureId);
		glDrawArrays(GL_TRIANGLE_STRIP, i * 4, 4);
	}
}

void GoogleMapWidget::mousePressEvent(QMouseEvent* event)
{
	dragStart = event->pos();
}

void GoogleMapWidget::mouseMoveEvent(QMouseEvent* event)
{
	translation += event->pos() - dragStart;
	dragStart = event->pos();

	renderer.setUniformValue("translation", translation.x() % Tile::SIZE, translation.y() % Tile::SIZE, 0, 0);

	glDraw();
}

QVector<QVector2D > GoogleMapWidget::generateTile(const QVector2D &position)
{
	const QVector2D pixelPosition = position * Tile::SIZE;

	return QVector<QVector2D >() <<
		QVector2D(pixelPosition.x(), 			  pixelPosition.y() + Tile::SIZE) << QVector2D(0, 0) <<
		QVector2D(pixelPosition.x(), 			  pixelPosition.y()				) << QVector2D(0, 1) <<
		QVector2D(pixelPosition.x() + Tile::SIZE, pixelPosition.y() + Tile::SIZE) << QVector2D(1, 0) <<
		QVector2D(pixelPosition.x() + Tile::SIZE, pixelPosition.y()				) << QVector2D(1, 1);
}
