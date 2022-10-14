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
            if(res.size()<args.RumorNodeCount) res.push_back(node);
        }
        rumorFile.close();
    }
    return res;
}

int main(int argc, char* argv[]){
    ConfigArgs args=ConfigArgs();
    if(!args.Parse(argc,argv)) return 0;
    ofstream out;
    out.open(args.output_file,ios::app);
    if(!out.is_open()){
        cout << "No such file: " << args.output_file << " or permission denied." << endl;
        exit(0);
    }
    args.print(out);

    Graph G=Graph(args,out);

    vector<int> T;
    vector<int> R;
    vector<double> kTime;
    vector<pair<int,int> > E;
    vector<pair<double,double> > res;
    vector<pair<double,double> > avg_res;


    clock_t start_time=clock();
    if(args.alg=="Ris-Eig" || args.alg=="Ris-Deg") {
        T = RisGreedy(G, args.TruthNodeCount, args.theta, args.alpha, args.delta,kTime);
    }else if(args.alg=="Lon-Eig" || args.alg=="Lon-Deg"){
        T = LonGreedy(G,args.TruthNodeCount,args.alpha2,args.delta,kTime);
    }else if(args.alg=="Imm"){
        T = ImmGreedy(G,args.TruthNodeCount,args.theta,args.delta,kTime);
    }else if(args.alg=="EdgeDel"){
        E = EdgeDeletion(G,args.DelEdgeCount);
    }else if(args.alg=="Deg"){
        T = MaxDegree(G, args.TruthNodeCount,kTime);
    }else{
        freopen("input.txt","r",stdin);
        int x;
        while(cin>>x){
            T.push_back(x);
        }
        fclose(stdin);
    }
    double totalTime=1.0*(clock()-start_time)/CLOCKS_PER_SEC;
    out<<"Total Time:"<<totalTime<<endl;

    if(args.alg!="Deg") {
        out << "k-Times:" << endl;
        out << 0 << " ";
        for (int i = 0; i < kTime.size(); i++) {
            out << kTime[i] << " ";
        }
        out << endl;
    }

    R = GenerateRumorSet(G,args);
    out<<"RumorSize:"<<R.size()<<endl;
    for(auto node:R){
        out<<node<<" ";
    }
    out<<endl;
    out<<"TruthSize:"<<T.size()<<endl;
    for(auto node:T){
        out<<node<<" ";
    }
    out<<endl;
    out<<"MonteCarlos Result:"<<endl;
    double simTime=0;

    if(args.kdetail) {
        vector<int> evalT;
        for (int i = 0; i <= T.size(); i++) {
            res = estimate(G, R, evalT, E, args, simTime);
            double res_r = 0;
            double res_t = 0;
            if (args.detail) out << "(rumor)k=" << i << ": ";
            for (int t = 0; t <= args.TimeRound; t++) {
                if (args.detail) out << res[t].first << " ";
                res_r += res[t].first;
            }
            if (args.detail) out << endl;
            if (args.detail) out << "(truth)k=" << i << ": ";
            for (int t = 0; t <= args.TimeRound; t++) {
                if (args.detail) out << res[t].second << " ";
                res_t += res[t].second;
            }
            if (args.detail) out << endl;
            avg_res.emplace_back(res_r / (args.TimeRound + 1), res_t / (args.TimeRound + 1));
            if (i != T.size()) evalT.push_back(T[i]);
        }
    }else{
        res = estimate(G, R, T, E, args, simTime);
        double res_r = 0;
        double res_t = 0;
        if (args.detail) out << "(rumor)k=" << T.size() << ": ";
        for (int t = 0; t <= args.TimeRound; t++) {
            if (args.detail) out << res[t].first << " ";
            res_r += res[t].first;
        }
        if (args.detail) out << endl;
        if (args.detail) out << "(truth)k=" << T.size() << ": ";
        for (int t = 0; t <= args.TimeRound; t++) {
            if (args.detail) out << res[t].second << " ";
            res_t += res[t].second;
        }
        if (args.detail) out << endl;
        avg_res.emplace_back(res_r / (args.TimeRound + 1), res_t / (args.TimeRound + 1));
    }
    out << "k-rumor:" << endl;
    for (int i = 0; i < avg_res.size(); i++) {
        out << avg_res[i].first << endl;
    }
    out << "k-truth:" << endl;
    for (int i = 0; i < avg_res.size(); i++) {
        out << avg_res[i].second << endl;
    }
    out << "Simulation Time:" << simTime << "s." << endl;
    out.close();
    return 0;
}