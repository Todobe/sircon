#ifndef SIRCON_CONFIGARGS_H
#define SIRCON_CONFIGARGS_H
#include <string>
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
    ConfigArgs();
    bool Parse(int argc, char* argv[]);
};


#endif //SIRCON_CONFIGARGS_H
