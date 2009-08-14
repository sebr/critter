#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "../Debug.h"
#include "../crucible/Project.h"
#include "../crucible/Repository.h"
#include "../crucible/User.h"
#include "../crucible/CrucibleConnectorBase.h"
#include "../crucible/actions/projects/LoadProjectsAction.h"
#include "../crucible/actions/repositories/LoadRepositoriesAction.h"
#include "../crucible/actions/users/LoadUsersAction.h"
#include "../crucible/rest/Communicators.h"

Q_DECLARE_METATYPE(Project*)
Q_DECLARE_METATYPE(Repository*)
Q_DECLARE_METATYPE(User*)

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

    UsersCommunicator *uc = new UsersCommunicator(this);
    uc->setServer(m_connector->server());
    uc->setUser(m_connector->user());
    uc->setPassword(m_connector->password());

    LoadUsersAction *lua = new LoadUsersAction(uc, this);
    connect(lua, SIGNAL(usersReceived(QList<User*>)), this, SLOT(loadUsers(QList<User*>)));
    lua->run();

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
        QVariant data; data.setValue(p);
        m_ui->project->addItem(p->key() + ": " + p->name(), data);
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
        QVariant data; data.setValue(r);
        m_ui->repository->addItem(r->name(), data);
    }
}

void MainWindow::loadUsers(QList<User*> users) {
    DEBUG_BLOCK

    m_ui->moderator->clear();
    m_ui->author->clear();

    if (users.isEmpty()) {
        m_ui->moderator->addItem("No users found");
        m_ui->moderator->setDisabled(true);
        m_ui->author->addItem("No users found");
        m_ui->author->setDisabled(true);
    } else {
        m_ui->moderator->setDisabled(false);
        m_ui->author->setDisabled(false);
    }

    int i = 0;
    foreach(User *u, users) {
        QVariant data; data.setValue(u);
        m_ui->moderator->insertItem(i, u->displayName(), data);
        m_ui->author->insertItem(i, u->displayName(), data);

        if (u->userName() == m_connector->user()) {
            m_ui->moderator->setCurrentIndex(i);
            m_ui->author->setCurrentIndex(i);
        }
        i++;
    }
}
