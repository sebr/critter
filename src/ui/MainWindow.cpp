#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "../Debug.h"
#include "../crucible/Project.h"
#include "../crucible/Repository.h"
#include "../crucible/CrucibleConnectorBase.h"
#include "../crucible/actions/projects/LoadProjectsAction.h"
#include "../crucible/actions/repositories/LoadRepositoriesAction.h"
#include "../crucible/rest/ProjectsCommunicator.h"
#include "../crucible/rest/RepositoryCommunicator.h"

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

    RepositoryCommunicator *rc = new RepositoryCommunicator(this);
    rc->setServer(m_connector->server());
    rc->setUser(m_connector->user());
    rc->setPassword(m_connector->password());

    LoadRepositoriesAction *lra = new LoadRepositoriesAction(rc, this);
    connect(lra, SIGNAL(repositoriesReceived(QList<Repository*>)), this, SLOT(loadRepositories(QList<Repository*>)));
    lra->run();

}

void MainWindow::loadProjects(QList<Project*> projects) {
    DEBUG_BLOCK

    m_ui->project->clear();

    if (projects.isEmpty()) {
        m_ui->project->addItem("No projects found");
        m_ui->project->setDisabled(true);
    } else {
        m_ui->project->setDisabled(false);
    }

    foreach(Project *p, projects) {
        m_ui->project->addItem(p->key() + ": " + p->name());
    }
}

void MainWindow::loadRepositories(QList<Repository*> repos) {
    DEBUG_BLOCK

    m_ui->repository->clear();

    if (repos.isEmpty()) {
        m_ui->repository->addItem("No repositories found");
        m_ui->repository->setDisabled(true);
    } else {
        m_ui->repository->setDisabled(false);
    }

    foreach(Repository *r, repos) {
        m_ui->repository->addItem(r->name());
    }
}
