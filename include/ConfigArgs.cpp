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
    network_file="./data/Video_game_network.txt";
    rumor_seed_file = "";
    output_file = "output.txt";
    TimeRound=500;
    TruthNodeCount=10;
    RumorNodeCount=10;
    theta = 100;
    MonteCarlosTimes=1000;
    beta=0.5;
    alpha=0.5;
    alpha2=0.5;
    delta=0.5;
    DelEdgeCount=20;
    alg="Ris-Deg";

}

bool ConfigArgs::Parse(int argc, char **argv) {
    auto cli = (
            value("network file", network_file),
            option("-o") & value("output file", output_file),
            option("-rs") & value("rumor seed file",rumor_seed_file),
            option("-T") & value("time round", TimeRound),
            option("-r") & value("rumor seed count",RumorNodeCount),
            option("-theta") & value("theta",theta),
            option("-k") & value("k truth node count",TruthNodeCount),
            option("-alpha") & value("alpha",alpha),
            option("-alpha2") & value("alpha2", alpha2),
            option("-MC") & value("MonteCarlosTimes", MonteCarlosTimes),
            option("-beta") & value("beta", beta),
            option("-delta") & value("delta", delta),
            option("-edge") & value("delete edge count",DelEdgeCount),
            option("-alg") & value("algorithm:[Ris-Eig,Ris-Deg,Lon-Eig,Lon-Deg,Imm,EdgeDel,Deg]",alg)
            );
    if(!parse(argc, argv, cli)){
        cout<<make_man_page(cli,argv[0]);
        return false;
    }
    return true;
}

void ConfigArgs::print(std::ofstream &out) {
    out<<"algorithm:"<<alg<<endl;
    out<<"T:"<<TimeRound<<" RumorSeed:"<<RumorNodeCount<<" TruthSeed:"<<TruthNodeCount<<endl;
    out<<"theta: "<<theta<<" alpha:"<<alpha<<" alpha2:"<<alpha2<<" beta:"<<beta<<" delta:"<<delta<<endl;
    out<<"MonteCarlosTimes:"<<MonteCarlosTimes<<" delEdge"<<DelEdgeCount<<endl;
}