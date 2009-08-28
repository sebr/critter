
#include "Critter.h"
#include "Debug.h"

#include "crucible/CrucibleConnector.h"
#include "crucible/Review.h"

#include <QApplication>
#include <QDir>
#include <QFileInfo>
#include <QFile>

#include <iostream>

namespace po = boost::program_options;
using namespace std;

QMutex Debug::mutex;
bool Debug::enabled = false;

Critter::Critter(QObject *parent)
    : QObject(parent)
    , m_crucibleConnector(0)
{
}

Critter::Critter(CrucibleConnectorBase *connector, QObject *parent)
    : QObject(parent)
{
    m_crucibleConnector = new CrucibleConnector(connector);
}

void Critter::parseOptions(po::variables_map vm) {
    if (!m_crucibleConnector) {
        warning() << "No crucible connector!";
        return;
    }

    const bool isCreateReview = vm.count("create");
    const bool isUpdateReview = vm.count("update");
    bool readFromStdIn = true;

    if (isCreateReview && isUpdateReview) {
        error() << "You can't create and update a review at the same time!";
        qApp->exit(1);
    }

    Review *review = new Review(this);

    if (isCreateReview) {
        QString author = m_crucibleConnector->user();
        if (vm.count("author")) {
            author = QString::fromStdString(vm["author"].as<string>());
        }
        review->setAuthor(author);
    }

    m_crucibleConnector->setReview(review);

    if (isUpdateReview) {
        const QString id = QString::fromStdString(vm["update"].as<string>());
        review->setId(id);
    }

    if (vm.count("title")) {
        const QString name = QString::fromStdString(vm["title"].as<string>());
        review->setName(name);
    }

    if (vm.count("objectives")) {
        const QString objectives = QString::fromStdString(vm["objectives"].as<string>());
        review->setDescription(objectives);
    }

    if (vm.count("project")) {
        const QString project = QString::fromStdString(vm["project"].as<string>());
        review->setProject(project);
    } else {
        review->setProject("CR");
    }

    if (vm.count("start")) {
        review->setShouldStart(true);
    }

    if (vm.count("creator")) {
        const QString creator = QString::fromStdString(vm["creator"].as<string>());
        review->setCreator(creator);
    }
    if (vm.count("moderator")) {
        const QString &moderator = QString::fromStdString(vm["moderator"].as<string>());
        review->setModerator(moderator);
    }

    if (vm.count("reviewers")) {
        const QVector<string> reviewers = QVector<string>::fromStdVector(vm["reviewers"].as< vector<string> >());
        foreach(string rev, reviewers) {
            review->addReviewer(QString::fromStdString(rev));
        }
    }
    
    if (vm.count("repository")) {
        const QString repo = QString::fromStdString(vm["repository"].as<string>());
        review->setRepository(repo);
    }

    if (vm.count("changeset")) {
        readFromStdIn = false;
        const QVector<string> changesets = QVector<string>::fromStdVector(vm["changeset"].as< vector<string> >());
        foreach(string cs, changesets) {
            review->addChangeset(QString::fromStdString(cs));
        }
    }

    if (vm.count("patch")) {
        readFromStdIn = false;
        const QString &patchFile = QString::fromStdString(vm["patch"].as<string>());
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
}

void Critter::testConnection() {
    DEBUG_NOTIMPLEMENTED
//    m_crucibleConnector->testConnection();
}

QByteArray Critter::loadPatch(const QString &filename) const
{
    QFileInfo fi(QDir::current(), filename);

    debug() << "loading patch data from" << fi.filePath();

    QFile patch(fi.filePath());

    bool open = patch.open(QIODevice::ReadOnly);
    if (!open) {
        error() << "Could not open patch" << fi.filePath() << "Check file permissions";
        return QByteArray();
    }

    return patch.readAll();
}

void Critter::readStdIn(Review *review) {
    std::string input_line;

    QByteArray ba;

    bool isPatch = false;
    QString commitRevision = false;
    bool firstLine = true;

    while (!std::getline(std::cin, input_line).eof()) {
        const QString s = QString::fromStdString(input_line) + "\n";
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
        review->addChangeset(commitRevision);
    }
}
