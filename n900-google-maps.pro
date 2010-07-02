TEMPLATE = app
TARGET = n900-google-maps

QT += network
CONFIG += debug

# Input
DEPENDPATH += . source
INCLUDEPATH += . source

SOURCES += source/*
HEADERS += source/*.h

# Output
OBJECTS_DIR += .build
MOC_DIR += .build
