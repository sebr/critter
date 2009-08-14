#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "../Critter.h"

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent *e);

private:
    void loadData();

    Ui::MainWindow *m_ui;

    Critter *m_critter;
};

#endif // MAINWINDOW_H
