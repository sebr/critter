#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../Critter.h"

#include <QMainWindow>
#include <QList>

namespace Ui {
    class MainWindow;
}

class CrucibleConnectorBase;
class Project;
class Repository;
class User;

class MainWindow : public QMainWindow {
        Q_OBJECT

    public:
        MainWindow(CrucibleConnectorBase *connector, QWidget *parent = 0);
        ~MainWindow();

    protected:
        void changeEvent(QEvent *e);

    private slots:
        void loadProjects(QList<Project*> projects);
        void loadRepositories(QList<Repository*> repos);
        void loadUsers(QList<User*> users);

    private:
        void loadData();

        Ui::MainWindow *m_ui;

        Critter *m_critter;
        CrucibleConnectorBase *m_connector;
};

#endif // MAINWINDOW_H
