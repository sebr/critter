
#include "Critter.h"
#include "Debug.h"

#include "crucible/CrucibleConnector.h"
#include "crucible/Review.h"

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
    , m_crucibleConnector(new CrucibleConnector(this))
{
}

void Critter::parseOptions(po::variables_map vm) {
    bool isCreateReview = vm.count("create-review");
    bool isUpdateReview = vm.count("review");

    if (isCreateReview && isUpdateReview) {
        error() << "You can't create and update a review at the same time!";
        qApp->exit(1);
    }

    if (isCreateReview || isUpdateReview) {

        if (isCreateReview && !vm.count("author")) {
            error() << "No author specified";
            qApp->exit(1);
        }

        const QString author = QString::fromStdString(vm["author"].as<string>());

        Review *review = new Review(this);
        review->setAuthor(author);

        if (isUpdateReview) {
            const QString id = QString::fromStdString(vm["review"].as<string>());
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

        if (vm.count("creator")) {
            const QString creator = QString::fromStdString(vm["creator"].as<string>());
            review->setCreator(creator);
        }
        if (vm.count("moderator")) {
            const QString &moderator = QString::fromStdString(vm["moderator"].as<string>());
            review->setModerator(moderator);
        }

        if (vm.count("changeset")) {
            const QVector<string> changesets = QVector<string>::fromStdVector(vm["changeset"].as< vector<string> >());
            foreach(string cs, changesets) {
                review->addChangeset(QString::fromStdString(cs));
            }

            if (vm.count("repository")) {
                const QString repo = QString::fromStdString(vm["repository"].as<string>());
                review->setRepository(repo);
            } else {
                error() << "No repository specified";
                qApp->exit(1);
            }
        }

        if (vm.count("patch")) {
            const QString &patchFile = QString::fromStdString(vm["patch"].as<string>());
            QByteArray patchData = loadPatch(patchFile);
            if (!patchData.isEmpty()) {
                review->addPatch(patchData);
            }
        }

        if (isCreateReview) {
            m_crucibleConnector->createReview(review);
        } else if (isUpdateReview) {
//            m_crucibleConnector->updateReview(review);
        }
    }
}

void Critter::testConnection() {
    DEBUG_BLOCK
    m_crucibleConnector->testConnection();
}

QByteArray Critter::loadPatch(const QString &filename) const
{
    DEBUG_BLOCK

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

void Critter::readStdIn() {
    std::string input_line;

    while (std::cin) {
        std::getline(std::cin, input_line);
        debug() << QString::fromStdString(input_line);
    }
}
