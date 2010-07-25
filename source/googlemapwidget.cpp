#include "tile.h"
#include "googlemapwidget.h"

GoogleMapWidget::GoogleMapWidget(QWidget *parent):
	QGLWidget(parent), tileCache("m@128"), center(Coordinate(37.743749,-122.416867), 17)
{
	connect(&tileCache, SIGNAL(tileUpdated(QString)), this, SLOT(tileUpdated(QString)));
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
}

void GoogleMapWidget::resizeGL(int width, int height)
{
		// New viewport
	glViewport(0, 0, width, height);

		// Let the shader know the size
		// TODO: Send a new matrix
	renderer.setUniformValue("size", width, height);

		// Tile for each side + tiles on screen
	gridWidth  = ((width  / Tile::SIZE) + 1) + 1;
	gridHeight = ((height / Tile::SIZE) + 1) + 1;

		// Clear all vertices
	vbo.clear();

		// Reserve exact size for the VBO, since we know the size in advance
		// 4 Vertices per tile
	vbo.reserve((gridWidth * 4) * (gridHeight * 4));

		// Generate the grid starting from outside the screen
	for(int y=0; y<gridHeight; ++y) {
		for(int x=0; x<gridWidth; ++x)
			vbo << generateTile(QVector2D(x, y));
	}

		// Set the generated VBO data
	renderer.setAttributeArray("position", vbo.constData() + 0, sizeof(QVector2D) * 2);
	renderer.setAttributeArray("texture",  vbo.constData() + 1, sizeof(QVector2D) * 2);

		// Recenter screen
	setCenter(center);
}

void GoogleMapWidget::paintGL()
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	BitmapCoordinate tileIterator = center - QPoint(width() / 2, height() / 2);
	for(int y=0; y<gridHeight; ++y) {
		for(int x=0; x<gridWidth; ++x) {
			GLint bindId = 0;
			QString tileId = Tile(tileIterator).id();

			if(boundTiles.contains(tileId))
				bindId = boundTiles.value(tileId);
			else if(!tileCache.isTileLoading(tileId))
				tileCache.retrieveBitmap(tileId);

			if(bindId != 0) {
				glBindTexture(GL_TEXTURE_2D, bindId);
				glDrawArrays(GL_TRIANGLE_STRIP, (x + (y * gridWidth)) * 4, 4);
			}

			tileIterator.rx() += Tile::SIZE;
		}

		tileIterator.ry() += Tile::SIZE;
		tileIterator.rx() -= Tile::SIZE * gridWidth;
	}
}

void GoogleMapWidget::tileUpdated(const QString &id)
{
	boundTiles.insert(id, bindTexture(tileCache.getBitmap(id), GL_TEXTURE_2D, GL_RGBA, QGLContext::InvertedYBindOption));

	update();
}

void GoogleMapWidget::mousePressEvent(QMouseEvent* event)
{
	dragStart = event->pos();
}

void GoogleMapWidget::mouseMoveEvent(QMouseEvent* event)
{
	setCenter(center - (event->pos() - dragStart));
	dragStart = event->pos();
}

void GoogleMapWidget::setCenter(const BitmapCoordinate &bcoord)
{
	center = bcoord;

	renderer.setUniformValue("translation", (-center.x() + (width() / 2)) % Tile::SIZE, (-center.y() + (height() / 2)) % Tile::SIZE, 0, 0);

	update();
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
