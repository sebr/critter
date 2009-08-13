
#include "Critter.h"

#include <QDebug>
#include <QCoreApplication>

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

    po::options_description config("Configuration options");
    config.add_options()
//        ("test-connection,t", "test and debug server connection")
        ("create-review,c", "creating a review")
        ("edit-review,e", "update an existing review")
        ("start-review,s", "start the review when creating it")
        ("changeset", po::value< vector<string> >()->multitoken(), "create a review from the specified changeset ids")
        ("upload,u", po::value< vector<string> >()->multitoken(), "files to upload to the specified review")
        ("patch,p", po::value< vector<string> >()->multitoken(), "patches to upload to the specified review")
        ("review,r", po::value<string>(), "the review to update. if not specified, a new review is created")
        ;

    po::options_description review("Review options");
    review.add_options()
        ("author", po::value<string>(), "when creating, the author of the review")
        ("creator", po::value<string>(), "when creating, the creator of the review (if not set, defaults to author)")
        ("moderator", po::value<string>(), "when creating, the moderator of the review (if not set, defaults to author)")
        ("project", po::value<string>(), "when creating, the project to add the review to. Defaults to \"CR\"")
        ("repository", po::value<string>(), "the repository for changesets")
        ;

    po::options_description visible("Allowed options");
    visible.add(generic).add(config).add(review);

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, visible), vm);
    po::notify(vm);

    if (vm.count("help")) {
        std::cout << visible << "\n";
        a.exit(1);
        return 1;
    }

    Critter *critter = new Critter();
    critter->parseOptions(vm);

    return a.exec();
}
