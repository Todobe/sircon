#include "ConfigArgs.h"
#include "clipp.h"

#include <iostream>
#include <random>

using namespace std;
using namespace clipp;

std::mt19937 mtRand(random_device{}());

int getRandInt(int l, int r){
    uniform_int_distribution<int> uid(l, r);
    return uid(mtRand);
}

double getRandFloat(){
    uniform_real_distribution<> urd(0, 1);
    return urd(mtRand);
}


ConfigArgs::ConfigArgs() {
    network_file="network_file.txt";
    output_file = "output.txt";
    TimeRound=500;
    TruthNodeCount=10;
    RumorNodeCount=10;
    theta = 10000;
    MonteCarlosTimes=1000;
    beta=0.5;
    alpha=0.5;
    alpha2=0.5;
    delta=0.5;
}

bool ConfigArgs::Parse(int argc, char **argv) {
    auto cli = (
            value("network file", network_file),
            option("-o") & value("output file", output_file),
            option("-rumor") & value("rumor seed file",rumor_seed_file),
            option("-theta") & value("theta",theta)
            );
    if(!parse(argc, argv, cli)){
        cout<<make_man_page(cli,argv[0]);
        return false;
    }
    return true;
}