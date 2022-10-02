#include "./include/ConfigArgs.h"
#include "./include/Graph.h"
#include "Functions.h"
#include <algorithm>
#include <iostream>

vector<int> GenerateRumorSet(Graph &G,int RumorNodesCount){
    vector<int> res;
    while(res.size()<RumorNodesCount){
        int node=getRandInt(0,G.nodeCount);
        if(find(res.begin(),res.end(),node)==res.end()){
            res.push_back(node);
        }
    }
    return res;
}

int main(int argc, char* argv[]){
    ConfigArgs args=ConfigArgs();
    if(!args.Parse(argc,argv)) return 0;
    Graph G=Graph(args);

    vector<int> T = LonGreedy(G,args.TruthNodeCount,args.alpha2,args.delta);
    vector<pair<double,double> > res= estimate(G, GenerateRumorSet(G,args.RumorNodeCount),T,args);

    for(auto t:T) cout<<t<<endl;
    for(auto & re : res){
        cout<<re.first<<" "<<re.second<<endl;
    }
    return 0;
}