#include "googlemapwidget.h"
#include <cstdio>

GoogleMapWidget::GoogleMapWidget(QWidget *parent):
	QGLWidget(parent)
{

}

void GoogleMapWidget::initializeGL()
{
	glViewport(0, 0, 800, 480);

	const char* fragShaderSrc = "\
		uniform sampler2D textureId;\
		\
		varying lowp vec2 texCoords;\
		\
		void main(void)\
		{\
			gl_FragColor = texture2D(textureId, texCoords);\
		}";

	const char* vertShaderSrc = "\
		attribute vec4	position;\
		attribute vec4	texture;\
		\
		uniform vec4	translation;\
		\
		varying vec2	texCoords;\
		\
		const mat4 modelViewProjectionMatrix = mat4(\
			2.0/(800.0 - 0.0), 0.0, 0.0, -(800.0 + 0.0)/(800.0 - 0.0),\
			0.0, 2.0/(0.0 - 480.0), 0.0, -(0.0 + 480.0)/(0.0 - 480.0),\
			0.0, 0.0, -2.0/(1.0 - 0.0), -(1.0 + 0.0)/(1.0 - 0.0),\
			0.0, 0.0, 0.0, 1.0\
		);\
		\
		void main(void)\
		{\
			gl_Position = (position + translation) * modelViewProjectionMatrix;\
			texCoords = texture.st;\
		}";

	GLuint fragShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragShaderId, 1, &fragShaderSrc, NULL);
	glCompileShader(fragShaderId);

	GLuint vertShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertShaderId, 1, &vertShaderSrc, NULL);
	glCompileShader(vertShaderId);

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, fragShaderId);
	glAttachShader(shaderProgram, vertShaderId);
	glBindAttribLocation(shaderProgram, 0, "position");
    glBindAttribLocation(shaderProgram, 1, "texture");
	glLinkProgram(shaderProgram);

	glUseProgram(shaderProgram);

	const GLfloat quadVertices[] = {
		  0, 256,
		  0,   0,
		  0,   0,
		  0,   1,
		256, 256,
		  1,   0,
		256,   0,
		  1,   1,
	};

	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLuint), 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLuint), (void*)(2 * sizeof(GLuint)));

	textureId = bindTexture(tile);

	glUniform4f(glGetUniformLocation(shaderProgram, "translation"), 0, 0, 0, 0);
}

void GoogleMapWidget::paintGL()
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	glBindTexture(GL_TEXTURE_2D, textureId);
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

	glUniform4f(glGetUniformLocation(shaderProgram, "translation"), translation.x(), translation.y(), 0, 0);

	glDraw();
}
