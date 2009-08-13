# -------------------------------------------------
# Project created by QtCreator 2009-08-12T19:39:22
# -------------------------------------------------
QT += network \
    xml
QT -= gui
TARGET = critter
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
SOURCES += src/main.cpp \
    src/Critter.cpp \
    src/crucible/CrucibleConnector.cpp \
    src/crucible/RestCommunicator.cpp \
    src/crucible/Review.cpp
HEADERS += src/Critter.h \
    src/Debug.h \
    src/crucible/CrucibleConnector.h \
    src/crucible/RestCommunicator.h \
    src/crucible/Review.h
LIBS += -lboost_program_options
MOC_DIR = build
OBJECTS_DIR = build
