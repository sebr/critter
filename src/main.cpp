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
#include "crucible/CrucibleConnectorBase.h"
#include "ui/MainWindow.h"

#include <QCoreApplication>
#include <QDebug>

#include <boost/program_options.hpp>
#include <iostream>

namespace po = boost::program_options;
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QCoreApplication::setOrganizationName("Atlassian");
    QCoreApplication::setOrganizationDomain("atlassian.com");
    QCoreApplication::setApplicationName("Critter");

    // Read arguments
    po::options_description generic("General options");
    generic.add_options()
        ("help", "produces this help message")
        ("debug,d", "enable debug output")
        ;

    po::options_description main("Mandatory options");
    main.add_options()
        ("create,c", "creating a review")
        ("update,u", po::value<string>(), "the review to update. if not specified, a new review is created")
        ;

    po::options_description config("Crucible options");
    config.add_options()
        ("server,S", po::value<string>(), "crucible server")
        ;

    po::options_description review("Review options");
    review.add_options()
        ("start,s", "start the review")
        ("changeset", po::value< vector<string> >()->multitoken(), "create a review from the specified changeset ids")
        ("patch,p", po::value<string>(), "patch to upload to the specified review")
        ("title", po::value<string>(), "the review title")
        ("objectives", po::value<string>(), "the review objectives")
        ("author", po::value<string>(), "when creating, the author of the review")
        ("creator", po::value<string>(), "when creating, the creator of the review (if not set, defaults to author)")
        ("moderator", po::value<string>(), "when creating, the moderator of the review (if not set, defaults to author)")
        ("project", po::value<string>(), "when creating, the project to add the review to (if not set, defaults to \"CR\")")
        ("repository", po::value<string>(), "the repository for changesets")
        ("reviewers", po::value< vector<string> >()->multitoken(), "list of reviewers for the review")
        ;

    po::options_description visible("Allowed options");
    visible.add(generic).add(main).add(config).add(review);

    po::variables_map vm;
    try {
        po::store(po::parse_command_line(argc, argv, visible), vm);
        po::notify(vm);
    } catch (exception) {
        std::cout << "Invalid arguments\n\n"
                  << visible << "\n";
        a.exit(1);
        return 1;
    }

    const bool isCreateReview = vm.count("create");
    const bool isUpdateReview = vm.count("update");
    const bool showHelp = vm.count("help") ||
                          (isCreateReview && isUpdateReview) ||
                          (!isCreateReview && !isUpdateReview);

    if (showHelp) {
        std::cout << visible << "\n";
        a.exit(1);
        return 1;
    }

//    bool showGui = false;
//    if (showGui) {
//        MainWindow *w = new MainWindow();
//        if (vm.count("server")) {
//            QString overrideServer = QString::fromStdString(vm["server"].as<string>());
            //w->setServer(overrideServer);
//        }
//        w->show();
//    } else {
        Critter *critter = new Critter();
        critter->setOptions(vm);
        critter->exec();
//    }

    return a.exec();
}
