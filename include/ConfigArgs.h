#ifndef SIRCON_CONFIGARGS_H
#define SIRCON_CONFIGARGS_H
#include <string>
#include <fstream>
using namespace std;

int getRandInt(int l,int r);
double getRandFloat();

class ConfigArgs {
public:
    string network_file, output_file;
    string rumor_seed_file;
    int theta,MonteCarlosTimes; //Sampling times
    double beta,alpha,alpha2,delta;
    int TimeRound,TruthNodeCount,RumorNodeCount;
    int DelEdgeCount;
    string alg;
    int T;
    int detail,kdetail;
    ConfigArgs();
    bool Parse(int argc, char* argv[]);
    void print(ofstream &out);
};


#endif //SIRCON_CONFIGARGS_H
