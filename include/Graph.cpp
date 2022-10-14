#include "Graph.h"

#include <iostream>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

Graph::Graph(const ConfigArgs &args, ofstream &out) {
    ifstream netFile;
    netFile.open(args.network_file,ios::in);
    if(!netFile.is_open()){
        cout << "No such file: " << args.network_file << " or permission denied." << endl;
        exit(0);
    }
    netFile>>nodeCount>>edgeCount;
    to = vector<vector<int > >(nodeCount);
    fro = vector<vector<int > >(nodeCount);
    for(int i=0;i<edgeCount;i++){
        int u,v;
        netFile>>u>>v;
        to[u].push_back(v);
        fro[v].push_back(u);
    }

    netFile>>eigenValue;
    leftEigVec = vector<double>(nodeCount);
    rightEigVec = vector<double>(nodeCount);
    for(int i=0;i<nodeCount;i++){
        netFile>>leftEigVec[i];
    }
    for(int i=0;i<nodeCount;i++){
        netFile>>rightEigVec[i];
    }
    eta=vector<double>(nodeCount);
    if(args.alg=="Ris-Deg" || args.alg=="Lon-Deg") {
        for (int i = 0; i < nodeCount; i++) {
            eta[i] = args.beta * fro[i].size() / (1 + args.beta * fro[i].size());
        }
    }else{
        for (int i = 0; i < nodeCount; i++) {
            eta[i] = args.beta * eigenValue / (1 + args.beta * eigenValue);
        }
    }
    T=args.T;
    out<<"Read graph from "<<args.network_file<<" done. Total "<<nodeCount<<" nodes, "<<edgeCount<<" edges."<<endl;
}

vector<pair<int, int> > Graph::simulate(const vector<int> &R, const vector<int> &T, double pR, double pT,int round,const vector<pair<int,int> > &DelEdge) {
    vector<pair<int,int> > res;
    vector<int> stat(nodeCount,0);
    set<int> changedNodes;
    queue<int> queR,queT;
    int cnt[3]={nodeCount,0,0};
    for(auto tNode:T){
        cnt[stat[tNode]]--; cnt[2]++;
        stat[tNode]=2;
        changedNodes.insert(tNode);
    }
    for(auto rNode:R){
        cnt[stat[rNode]]--; cnt[1]++;
        stat[rNode]=1;
        changedNodes.insert(rNode);
    }
    res.emplace_back(cnt[1],cnt[2]);
    for(int rnd=1;rnd<=round;rnd++){
        for(auto node:changedNodes){
            if(stat[node]==1) queR.push(node);
            else queT.push(node);
        }
        changedNodes.clear();
        while(!queR.empty()){
            auto cur=queR.front();
            queR.pop();
            for(auto v:to[cur]){
                if(binary_search(DelEdge.begin(),DelEdge.end(),make_pair(cur,v))) continue;
                if(binary_search(DelEdge.begin(),DelEdge.end(), make_pair(v,cur))) continue;
                if(stat[v]!=1 && getRandFloat()<pR){
                    changedNodes.insert(v);
                    cnt[stat[v]]--; cnt[1]++;
                    stat[v]=1;
                }
            }
        }
        while(!queT.empty()){
            auto cur=queT.front();
            queT.pop();
            for(auto v:to[cur]){
                if(stat[v]!=2 && getRandFloat()<pT){
                    changedNodes.insert(v);
                    cnt[stat[v]]--; cnt[2]++;
                    stat[v]=2;
                }
            }
        }
        res.emplace_back(cnt[1],cnt[2]);
    }
    return res;
}
