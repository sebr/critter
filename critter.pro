# -------------------------------------------------
# Project created by QtCreator 2009-08-12T19:39:22
# -------------------------------------------------
QT += network \
#    gui
    xml
TARGET = critter
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
SOURCES += src/main.cpp \
    src/Critter.cpp \
    src/crucible/CrucibleConnector.cpp \
    src/crucible/rest/RestCommunicator.cpp \
    src/crucible/Review.cpp \
    src/crucible/actions/AbstractAction.cpp \
    src/crucible/actions/reviews/AddReviewersAction.cpp \
    src/crucible/actions/reviews/CreateReviewAction.cpp \
    src/crucible/actions/reviews/StartReviewAction.cpp \
    src/crucible/actions/reviews/AddChangesetsAction.cpp \
    src/crucible/actions/reviews/AddPatchesAction.cpp \
#    src/ui/MainWindow.cpp \
    src/crucible/actions/fisheye/FishEyeChangesetWaitingAction.cpp \
    src/crucible/actions/projects/LoadProjectsAction.cpp \
    src/crucible/actions/repositories/LoadRepositoriesAction.cpp \
    src/crucible/actions/users/LoadUsersAction.cpp \
    src/Settings.cpp \
    src/crucible/dispatcher/SynchronousJobDispatcher.cpp
HEADERS += src/Critter.h \
    src/Debug.h \
    src/crucible/CrucibleConnector.h \
    src/crucible/rest/RestCommunicator.h \
    src/crucible/Review.h \
    src/crucible/actions/AbstractAction.h \
    src/crucible/actions/reviews/AddReviewersAction.h \
    src/crucible/actions/reviews/CreateReviewAction.h \
    src/crucible/actions/reviews/StartReviewAction.h \
    src/crucible/actions/reviews/AddChangesetsAction.h \
    src/crucible/actions/reviews/AddPatchesAction.h \
    src/crucible/actions/projects/LoadProjectsAction.h \
    src/crucible/actions/reviews/AbstractReviewAction.h \
    src/crucible/actions/fisheye/FishEyeChangesetWaitingAction.h \
    src/crucible/actions/repositories/LoadRepositoriesAction.h \
#    src/ui/MainWindow.h \
    src/crucible/CrucibleConnectorBase.h \
    src/crucible/Project.h \
    src/crucible/Repository.h \
    src/crucible/rest/Communicators.h \
    src/crucible/actions/users/LoadUsersAction.h \
    src/crucible/User.h \
    src/Settings.h \
    src/crucible/dispatcher/SynchronousJobDispatcher.h
LIBS += -lboost_program_options-mt
MOC_DIR = build
OBJECTS_DIR = build
UI_DIR = build
FORMS += src/ui/MainWindow.ui
