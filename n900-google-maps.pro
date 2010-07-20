TEMPLATE = app
TARGET = n900-google-maps

QT += network opengl

# Input
DEPENDPATH += . source
INCLUDEPATH += . source

SOURCES += source/*.cpp	source/googlemaps/*.cpp
HEADERS += source/*.h	source/googlemaps/*.h

# Output
OBJECTS_DIR += .build
MOC_DIR += .build
