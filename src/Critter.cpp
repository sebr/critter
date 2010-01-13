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

#include "Critter.h"
#include "Debug.h"
#include "Settings.h"

#include "crucible/CrucibleConnector.h"
#include "crucible/Review.h"

#include <QApplication>
#include <QDir>
#include <QFileInfo>
#include <QFile>
#include <QTimer>

#include <iostream>

namespace po = boost::program_options;
using namespace std;

QMutex Debug::mutex;
bool Debug::enabled = false;

Critter::Critter(QObject *parent)
    : QObject(parent)
    , m_crucibleConnector(0)
{
    Settings *settings = new Settings(this);
    m_crucibleConnector = new CrucibleConnector(settings, this);
}

void Critter::setOptions(po::variables_map vm) {
    m_vm = vm;
}

/*
 * This method exists to initialize the event loop
 */
void Critter::exec() {
    QTimer::singleShot(0, this, SLOT(parseOptions()));
}

void Critter::parseOptions() {
    if (!m_crucibleConnector) {
        error() << "No crucible connector!";
        qApp->quit();
        return;
    }

    bool readFromStdIn = true;
    const bool isCreateReview = m_vm.count("create");
    const bool isUpdateReview = m_vm.count("update");

    if (m_vm.count("server")) {
        QString overrideServer = QString::fromStdString(m_vm["server"].as<string>());
        debug() << "Server override:" << overrideServer;
        m_crucibleConnector->setServer(overrideServer);
    }

    Review *review = new Review(this);

    if (isCreateReview) {
        QString author = m_crucibleConnector->user();
        if (m_vm.count("author")) {
            author = QString::fromStdString(m_vm["author"].as<string>());
        }
        review->setAuthor(author);
    }

    m_crucibleConnector->setReview(review);

    if (isUpdateReview) {
        const QString id = QString::fromStdString(m_vm["update"].as<string>());
        review->setId(id);
    }

    if (m_vm.count("title")) {
        const QString name = QString::fromStdString(m_vm["title"].as<string>());
        review->setName(name);
    }

    if (m_vm.count("objectives")) {
        const QString objectives = QString::fromStdString(m_vm["objectives"].as<string>());
        review->setDescription(objectives);
    }

    if (m_vm.count("project")) {
        const QString project = QString::fromStdString(m_vm["project"].as<string>());
        review->setProject(project);
    } else {
        review->setProject("CR");
    }

    if (m_vm.count("start")) {
        review->setShouldStart(true);
    }

    if (m_vm.count("creator")) {
        const QString creator = QString::fromStdString(m_vm["creator"].as<string>());
        review->setCreator(creator);
    }
    if (m_vm.count("moderator")) {
        const QString &moderator = QString::fromStdString(m_vm["moderator"].as<string>());
        review->setModerator(moderator);
    }

    if (m_vm.count("reviewers")) {
        const QVector<string> reviewers = QVector<string>::fromStdVector(m_vm["reviewers"].as< vector<string> >());
        foreach(string rev, reviewers) {
            review->addReviewer(QString::fromStdString(rev));
        }
    }
    
    if (m_vm.count("repository")) {
        const QString repo = QString::fromStdString(m_vm["repository"].as<string>());
        review->setRepository(repo);
    }

    if (m_vm.count("changeset")) {
        readFromStdIn = false;
        const QVector<string> changesets = QVector<string>::fromStdVector(m_vm["changeset"].as< vector<string> >());
        foreach(string cs, changesets) {
            review->addChangeset(QString::fromStdString(cs));
        }
    }

    if (m_vm.count("patch")) {
        readFromStdIn = false;
        const QString &patchFile = QString::fromStdString(m_vm["patch"].as<string>());
        QByteArray patchData = loadPatch(patchFile);
        if (!patchData.isEmpty()) {
            review->addPatch(patchData);
        }
    }

    if (readFromStdIn) {
        readStdIn(review);
    }

    if (isCreateReview) {
        m_crucibleConnector->createReview();
    } else if (isUpdateReview) {
        m_crucibleConnector->updateReview();
    }
    connect(m_crucibleConnector, SIGNAL(finished()), qApp, SLOT(quit()));
}

void Critter::testConnection() {
    DEBUG_NOTIMPLEMENTED
//    m_crucibleConnector->testConnection();
}

QByteArray Critter::loadPatch(const QString &filename) const
{
    QFileInfo fi(QDir::current(), filename);

//      debug() << "loading patch data from" << fi.filePath();

    QFile patch(fi.filePath());

    bool open = patch.open(QIODevice::ReadOnly);
    if (!open) {
        error() << "Could not open patch" << fi.filePath() << "Check file permissions";
        return QByteArray();
    }

    return patch.readAll();
}

void Critter::readStdIn(Review *review) {
    debug() << "reading from stdin";
    std::string input_line;

    QByteArray ba;

    bool isPatch = false;
    QString commitRevision;
    bool firstLine = true;

    while (!std::getline(std::cin, input_line).eof()) {
        const QString s = QString::fromStdString(input_line);
        debug() << "   (read)" << s;
        if (firstLine) {
            if (s.startsWith("diff") || s.startsWith("Index:")) {
                isPatch = true;
            }
            firstLine = false;
        }
        if (s.startsWith("Committed")) {
            commitRevision = QString(s);
            commitRevision.replace(QRegExp(".*(\\d+).*"), "\\1");
        }
        ba.append(s);
    }

    if (isPatch) {
        review->addPatch(ba);
    }

    if (!commitRevision.isEmpty()) {
        debug() << "   (found)" << commitRevision;
        review->addChangeset(commitRevision);
    }
}
