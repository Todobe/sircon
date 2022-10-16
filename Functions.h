#ifndef SIRCON_FUNCTIONS_H
#define SIRCON_FUNCTIONS_H

#include "./include/ConfigArgs.h"
#include "./include/Graph.h"
#include <vector>
#include <map>
#include <set>

using namespace std;

class Generator {
public:
    vector<bool> VisLV;
    vector<int> Cnt;
    vector<vector<int> > UU;

    map<int,vector<vector<int> > > RRSets; //For Ris
    map<int,vector<int> > LvSets; // For Lon
    vector<vector<int> > IMMRRSets; //For Imm
    vector<vector<int> > RSamples; //For HMP
    explicit Generator(const Graph &G);
    static vector<int> generateRRSet(const Graph &G, int v, double p);
    bool generateRRSets(const Graph &G, int theta, double p);
    double Fv(const vector<int> &S, int v);

    bool generateLvSets(const Graph &G, double alpha2,double delta);
    bool Lv(const vector<int> &S, int v);

    bool generateIMMRRSets(const Graph &G, int theta, double p);
    double FR(const Graph &G, const vector<int> &S, int u);

    static vector<int> ReverseSampling(const Graph &G, set<pair<int,int> > &Et, set<pair<int,int> > &Ef, const vector<int> &Sr, int v, double p);
    bool HybridSampling(const Graph &G, const vector<int> &Sr, int theta, double p);

};

vector<int> RisGreedy(Graph &G, int k, int theta, double alpha, double delta, vector<double> & algTime);
vector<int> LonGreedy(Graph &G, int k, double alpha2, double delta, vector<double> &algTime);
vector<int> ImmGreedy(Graph &G, int k, int theta, double delta, vector<double> &algTime);
vector<int> MaxDegree(Graph &G ,int k,vector<double> &algTime);
vector<int> PageRank(Graph &G, int k, vector<double> &algTime, double d=0.8);
vector<int> HMP(Graph &G, int k, const vector<int> &R, int theta, double beta, vector<double> &algTime);

vector<pair<int,int> > EdgeDeletion(Graph &G, int k);

vector<pair<double,double> > estimate(Graph &G,const vector<int> &R, const vector<int> &T, const vector<pair<int,int> > &DelEdge, ConfigArgs &args, double &simTime);

#endif //SIRCON_FUNCTIONS_H
