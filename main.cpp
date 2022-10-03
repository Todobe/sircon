#include "./include/ConfigArgs.h"
#include "./include/Graph.h"
#include "Functions.h"
#include <algorithm>
#include <iostream>
#include <ctime>
#include <fstream>

vector<int> GenerateRumorSet(Graph &G,ConfigArgs &args){
    vector<int> res;
    if(args.rumor_seed_file.empty()) {
        for (int i = 0; i < args.RumorNodeCount; i++) {
            res.push_back(i);
        }
        while (res.size() < args.RumorNodeCount) {
            int node = getRandInt(0, G.nodeCount);
            if (find(res.begin(), res.end(), node) == res.end()) {
                res.push_back(node);
            }
        }
    }else{
        ifstream rumorFile;
        rumorFile.open(args.rumor_seed_file,ios::in);
        if(!rumorFile.is_open()){
            cout << "No such file: " << args.rumor_seed_file << " or permission denied." << endl;
            exit(0);
        }
        int node;
        while(rumorFile>>node){
            res.push_back(node);
        }
        rumorFile.close();
    }
    return res;
}

int main(int argc, char* argv[]){
    ConfigArgs args=ConfigArgs();
    if(!args.Parse(argc,argv)) return 0;
    Graph G=Graph(args);
    vector<int> T;
    vector<pair<int,int> > E;

    ofstream out;
    out.open(args.output_file,ios::app);
    if(!out.is_open()){
        cout << "No such file: " << args.output_file << " or permission denied." << endl;
        exit(0);
    }
    args.print(out);
    clock_t start_clk = clock();
    if(args.alg=="Ris-Eig" || args.alg=="Ris-Deg") {
        T = RisGreedy(G, args.TruthNodeCount, args.theta, args.alpha, args.delta);
    }else if(args.alg=="Lon-Eig" || args.alg=="Lon-Deg"){
        T = LonGreedy(G,args.TruthNodeCount,args.alpha2,args.delta);
    }else if(args.alg=="Imm"){
        T = ImmGreedy(G,args.TruthNodeCount,args.theta,args.delta);
    }else if(args.alg=="EdgeDel"){
        E = EdgeDeletion(G,args.DelEdgeCount);
    }else{
        T = MaxDegree(G, args.theta);
    }
    clock_t end_clk = clock();
    double AlgTime = (end_clk - start_clk)/CLOCKS_PER_SEC;
    out<<"Algorithm Time:"<<AlgTime<<"s."<<endl;
    out<<"MonteCarlos Result:"<<endl;
    start_clk = clock();
    vector<int> R = GenerateRumorSet(G,args);
    out<<"RumorSize:"<<R.size()<<endl;
    if(R.size()<20){
        for(auto node:R){
            out<<node<<" ";
        }
        out<<endl;
    }
    vector<pair<double, double> > res = estimate(G, R, T, E, args);
    int step=args.TimeRound/10;
    for(int i=0;i<res.size();i+=step){
        out<<res[i].first<<" "<<res[i].second<<endl;
    }
    end_clk = clock();
    double SimTime=(end_clk - start_clk) / CLOCKS_PER_SEC;
    out<<"Simulation Time:"<<SimTime<<"s."<<endl;
    out.close();
    return 0;
}