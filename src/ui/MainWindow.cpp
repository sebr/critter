#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "../Debug.h"
#include "../crucible/Project.h"
#include "../crucible/CrucibleConnectorBase.h"
#include "../crucible/actions/projects/LoadProjectsAction.h"
#include "../crucible/rest/ProjectsCommunicator.h"

MainWindow::MainWindow(CrucibleConnectorBase *connector, QWidget *parent) :
    QMainWindow(parent)
    , m_ui(new Ui::MainWindow)
    , m_critter(new Critter(this))
    , m_connector(connector)
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
    DEBUG_BLOCK

    ProjectsCommunicator *pc = new ProjectsCommunicator(this);
    pc->setServer(m_connector->server());
    pc->setUser(m_connector->user());
    pc->setPassword(m_connector->password());
    LoadProjectsAction *lpa = new LoadProjectsAction(pc, this);

    connect(lpa, SIGNAL(projectsReceived(QList<Project*>)), this, SLOT(loadProjects(QList<Project*>)));

    lpa->run();
}

void MainWindow::loadProjects(QList<Project*> projects) {
    DEBUG_BLOCK

    foreach(Project *p, projects) {
        m_ui->project->addItem(p->key() + ": " + p->name());
    }
}
