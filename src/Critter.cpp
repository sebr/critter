
#include "Critter.h"
#include "Debug.h"

#include "crucible/CrucibleConnector.h"

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
    if (vm.count("create-review")) {
        if (!vm.count("author")) {
            error() << "No author specified";
            qApp->exit(1);
        }
        const QString author = QString::fromStdString(vm["author"].as<string>());
        debug() << "creating review with author" << author;
    }
}

void Critter::testConnection() {
    DEBUG_BLOCK
    m_crucibleConnector->testConnection();
}

void Critter::readStdIn() {
    std::string input_line;

    while (std::cin) {
        std::getline(std::cin, input_line);
        debug() << QString::fromStdString(input_line);
    }
}
