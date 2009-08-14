#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "../crucible/rest/ProjectsCommunicator.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
    , m_ui(new Ui::MainWindow)
    , m_critter(new Critter(this))
{
    m_ui->setupUi(this);

    connect(m_ui->actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));

    loadData();
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::loadData() {
    ProjectsCommunicator *pC = new ProjectsCommunicator(this);

}
