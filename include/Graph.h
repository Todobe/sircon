
#ifndef SIRCON_GRAPH_H
#define SIRCON_GRAPH_H

#include <vector>
#include <string>
#include <cstdio>
#include "ConfigArgs.h"
using namespace std;

class Graph {
public:
    int nodeCount{}, edgeCount{};
    vector<vector<int > > to,fro;
    vector<double> eta;
    explicit Graph(const ConfigArgs &args);
    vector<pair<int,int> > simulate(const vector<int> &R, const vector<int> &T, double pR,double pT,int round);
};


#endif //SIRCON_GRAPH_H
