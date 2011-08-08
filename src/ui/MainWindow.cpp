/****************************************************************************
 **
 ** Copyright (c) 2009, Seb Ruiz <sruiz@atlassian.com>
 ** All rights reserved.
 **
 ** Redistribution and use in source and binary forms, with or without
 ** modification, are permitted provided that the following conditions are met:
 **
 ** Redistributions of source code must retain the above copyright notice, this
 ** list of conditions and the following disclaimer. Redistributions in binary
 ** form must reproduce the above copyright notice, this list of conditions and
 ** the following disclaimer in the documentation and/or other materials provided
 ** with the distribution.
 **
 ** Neither Atlassian nor the names of its contributors may be used to endorse or
 ** promote products derived from this software without specific prior written permission.
 **
 ** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ** ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 ** WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 ** IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 ** INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 ** BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 ** OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 ** WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 ** ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
 ** OF SUCH DAMAGE.
 **
 ****************************************************************************/

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "../Debug.h"
#include "../Settings.h"
#include "../crucible/Project.h"
#include "../crucible/Repository.h"
#include "../crucible/User.h"
#include "../crucible/CrucibleConnector.h"
#include "../crucible/actions/projects/LoadProjectsAction.h"
#include "../crucible/actions/repositories/LoadRepositoriesAction.h"
#include "../crucible/actions/users/LoadUsersAction.h"
#include "../crucible/rest/Communicators.h"

#include <QListWidgetItem>

Q_DECLARE_METATYPE(Project*)
Q_DECLARE_METATYPE(Repository*)
Q_DECLARE_METATYPE(User*)

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
    , m_ui(new Ui::MainWindow)
    , m_critter(new Critter(this))
{
    Settings *settings = new Settings(this);
    m_connector = new CrucibleConnector(settings, this);
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
    m_ui->moderator->clear();
    m_ui->author->clear();
    m_ui->reviewers->clear();

    if (users.isEmpty()) {
        m_ui->moderator->addItem("No users found");
        m_ui->moderator->setDisabled(true);
        m_ui->author->addItem("No users found");
        m_ui->author->setDisabled(true);

        m_ui->reviewers->addItem("No users found");

        m_ui->reviewers->setDisabled(true);
    } else {
        m_ui->moderator->setDisabled(false);
        m_ui->author->setDisabled(false);
        m_ui->reviewers->setDisabled(false);
    }

    int i = 0;
    foreach(User *u, users) {
        QVariant data; data.setValue(u);

        const QString text = u->displayName().isEmpty() ? u->userName() : u->displayName();

        m_ui->moderator->insertItem(i, text, data);
        m_ui->author->insertItem(i, text, data);

        if (u->userName() == m_connector->user()) {
            m_ui->moderator->setCurrentIndex(i);
            m_ui->author->setCurrentIndex(i);
        } else {
            QListWidgetItem *item = new QListWidgetItem(m_ui->reviewers);
            item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
            item->setCheckState(Qt::Unchecked);
            item->setText(text);
            m_ui->reviewers->addItem(item);
        }
        i++;
    }
}
