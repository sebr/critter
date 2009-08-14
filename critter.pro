# -------------------------------------------------
# Project created by QtCreator 2009-08-12T19:39:22
# -------------------------------------------------
QT += network \
    xml \
    gui
TARGET = critter
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
SOURCES += src/main.cpp \
    src/Critter.cpp \
    src/crucible/CrucibleConnector.cpp \
    src/crucible/rest/RestCommunicator.cpp \
    src/crucible/rest/ReviewsCommunicator.cpp \
    src/crucible/Review.cpp \
    src/crucible/actions/AbstractAction.cpp \
    src/crucible/actions/reviews/AddReviewersAction.cpp \
    src/crucible/actions/reviews/CreateReviewAction.cpp \
    src/crucible/actions/reviews/StartReviewAction.cpp \
    src/crucible/actions/reviews/AddChangesetsAction.cpp \
    src/crucible/actions/reviews/AddPatchesAction.cpp \
    src/ui/MainWindow.cpp \
    src/crucible/rest/ProjectsCommunicator.cpp \
    src/crucible/actions/projects/LoadProjectsAction.cpp
HEADERS += src/Critter.h \
    src/Debug.h \
    src/crucible/CrucibleConnector.h \
    src/crucible/rest/RestCommunicator.h \
    src/crucible/rest/ReviewsCommunicator.h \
    src/crucible/Review.h \
    src/crucible/actions/AbstractAction.h \
    src/crucible/actions/reviews/AddReviewersAction.h \
    src/crucible/actions/reviews/CreateReviewAction.h \
    src/crucible/actions/reviews/StartReviewAction.h \
    src/crucible/actions/reviews/AddChangesetsAction.h \
    src/crucible/actions/reviews/AddPatchesAction.h \
    src/ui/MainWindow.h \
    src/crucible/rest/ProjectsCommunicator.h \
    src/crucible/actions/projects/LoadProjectsAction.h \
    src/crucible/actions/reviews/AbstractReviewAction.h \
    src/crucible/Project.h \
    src/crucible/CrucibleConnectorBase.h
LIBS += -lboost_program_options
MOC_DIR = build
OBJECTS_DIR = build
UI_DIR = build
FORMS += src/ui/MainWindow.ui
