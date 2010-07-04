TEMPLATE = app
TARGET = n900-google-maps

QT += network opengl
CONFIG += debug

# Input
DEPENDPATH += . source
INCLUDEPATH += . source

SOURCES += source/*
HEADERS += source/*.h

# Output
OBJECTS_DIR += .build
MOC_DIR += .build
