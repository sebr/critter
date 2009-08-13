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
    src/crucible/Review.cpp \
    src/crucible/actions/AbstractAction.cpp \
    src/crucible/actions/AddReviewersAction.cpp \
    src/crucible/actions/CreateReviewAction.cpp \
    src/crucible/actions/StartReviewAction.cpp \
    src/crucible/actions/AddChangesetsAction.cpp \
    src/crucible/actions/AddPatchesAction.cpp
HEADERS += src/Critter.h \
    src/Debug.h \
    src/crucible/CrucibleConnector.h \
    src/crucible/RestCommunicator.h \
    src/crucible/Review.h \
    src/crucible/actions/AbstractAction.h \
    src/crucible/actions/AddReviewersAction.h \
    src/crucible/actions/CreateReviewAction.h \
    src/crucible/actions/StartReviewAction.h \
    src/crucible/actions/AddChangesetsAction.h \
    src/crucible/actions/AddPatchesAction.h
LIBS += -lboost_program_options
MOC_DIR = build
OBJECTS_DIR = build
