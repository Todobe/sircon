#ifndef SIRCON_FUNCTIONS_H
#define SIRCON_FUNCTIONS_H

#include "./include/ConfigArgs.h"
#include "./include/Graph.h"
#include <vector>
#include <map>

using namespace std;

class Generator {
public:
    map<int,vector<vector<int> > > RRSets;
    map<int,vector<int> > LvSets;
    Generator();
    static vector<int> generateRRSet(const Graph &G, int v, double p);
    bool generateRRSets(const Graph &G, int theta, double p);
    double Fv(const vector<int> &S, int v);

    bool generateLvSets(const Graph &G, double alpha2,double delta);
    bool Lv(const vector<int> &S, int v);

};

vector<int> RisGreedy(Graph &G,int theta, int k,double alpha, double delta);
vector<int> LonGreedy(Graph &G,int k, double alpha2, double delta);

vector<pair<double,double> > estimate(Graph &G,const vector<int> &R, const vector<int> &T,ConfigArgs &args);

#endif //SIRCON_FUNCTIONS_H
