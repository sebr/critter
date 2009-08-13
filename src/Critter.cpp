
#include "Critter.h"
#include "Debug.h"

#include "crucible/CrucibleConnector.h"

#include <iostream>

QMutex Debug::mutex;
bool Debug::enabled = false;

Critter::Critter(QObject *parent)
    : QObject(parent)
    , m_crucibleConnector(new CrucibleConnector(this))
{
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
