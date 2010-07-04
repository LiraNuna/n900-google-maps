TEMPLATE = app
TARGET = n900-google-maps

QT += network opengl
CONFIG += debug

# Input
DEPENDPATH += . source
INCLUDEPATH += . source

SOURCES += source/*.cpp	source/googlemaps/*.cpp	source/geom/*.cpp
HEADERS += source/*.h	source/googlemaps/*.h 	source/geom/*.h

# Output
OBJECTS_DIR += .build
MOC_DIR += .build
