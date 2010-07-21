TEMPLATE = app
TARGET = n900-google-maps

QT += network opengl

maemo5 {
    DEFINES += Q_WS_MAEMO_5
}

unix {
	CONFIG += debug
	DEFINES += GL_GLEXT_PROTOTYPES
}

# Input
DEPENDPATH += . source
INCLUDEPATH += . source

SOURCES += source/*.cpp	source/googlemaps/*.cpp
HEADERS += source/*.h	source/googlemaps/*.h

# Output
OBJECTS_DIR += .build
MOC_DIR += .build
