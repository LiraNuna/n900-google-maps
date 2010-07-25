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

	static const GLfloat quadVertices[] = {
		  0, 256,
		  0,   0,
		  0,   0,
		  0,   1,
		256, 256,
		  1,   0,
		256,   0,
		  1,   1,
	};

	renderer.enableAttributeArray("position");
	renderer.setAttributeArray("position", quadVertices + 0, 2, sizeof(GLfloat) * 4);

	renderer.enableAttributeArray("texture");
	renderer.setAttributeArray("texture", quadVertices + 2, 2, sizeof(GLfloat) * 4);

	textureId = bindTexture(tile);
}

void GoogleMapWidget::resizeGL(int width, int height)
{
	glViewport(0, 0, width, height);

	renderer.setUniformValue("size", width, height);

	/* TODO: Reconstruct vbo */
}

void GoogleMapWidget::paintGL()
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void GoogleMapWidget::mousePressEvent(QMouseEvent* event)
{
	dragStart = event->pos();
}

void GoogleMapWidget::mouseMoveEvent(QMouseEvent* event)
{
	translation += event->pos() - dragStart;
	dragStart = event->pos();

	renderer.setUniformValue("translation", translation.x(), translation.y(), 0, 0);

	glDraw();
}

