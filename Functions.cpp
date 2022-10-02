#include "Functions.h"
#include <queue>
#include <algorithm>
#include <cmath>
#include <iostream>

Generator::Generator()= default;


vector<int> Generator::generateRRSet(const Graph &G,int v,double p) {
    map<int,bool> vis;
    vector<int> res;
    queue<int> que;
    que.push(v);
    res.push_back(v);
    vis[v]=true;
    while(!que.empty()){
        int cur=que.front();
        que.pop();
        for(auto u :G.fro[cur]){
            if(!vis[u] && getRandFloat()<=p){
                que.push(u);
                vis[u]=true;
                res.push_back(u);
            }
        }
    }
    sort(res.begin(),res.end());
    return res;
}

bool Generator::generateRRSets(const Graph &G, int theta, double p) {
    for(int v=0;v<G.nodeCount;v++){
        RRSets[v]=vector<vector<int> >(theta);
        for(int i=0;i<theta;i++){
            RRSets[v].push_back(generateRRSet(G,v,p));
        }
    }
    return true;
}

double Generator::Fv(const vector<int> &S, int v) {
    int cnt = 0;
    for(auto Rv:RRSets[v]){
        bool flag=false;
        for(auto node:S){
            if(binary_search(Rv.begin(),Rv.end(),node)){
                flag=true;
                break;
            }
        }
        if(flag) cnt++;
    }
    return 1.0*cnt/RRSets[v].size();
}

bool Generator::generateLvSets(const Graph &G, double alpha2, double delta) {
    for(int v=0;v<G.nodeCount;v++){
        vector<int> Lv;
        int Phi=floor(log(alpha2*G.eta[v])/log(delta));
        map<int, int> vis;
        queue<int> que;
        que.push(v);
        vis[v]=0;
        Lv.push_back(v);
        while(!que.empty()){
            int cur=que.front();
            que.pop();
            for(auto u:G.fro[cur]){
                if(vis.count(u)==0){
                    vis[u]=vis[cur]+1;
                    Lv.push_back(u);
                    if(vis[u]<Phi) {
                        que.push(u);
                    }
                }
            }
        }
        sort(Lv.begin(),Lv.end());
        LvSets[v]=Lv;
    }
    return true;
}

bool Generator::Lv(const vector<int> &S, int v) {
    for(auto node:S){
        if(binary_search(LvSets[v].begin(),LvSets[v].end(),node)) return true;
    }
    return false;
}


vector<int> RisGreedy(Graph &G,int theta, int k,double alpha, double delta){
    vector<int> Sg;
    Generator RRSet;
    RRSet.generateRRSets(G,theta,delta);
    while(Sg.size()<k){
        int  max_u=0, maxScore=0;
        for(int u=0;u<G.nodeCount;u++){
            int score=0;
            Sg.push_back(u);
            for(int v=0;v<G.nodeCount;v++){
                score+=RRSet.Fv(Sg,v) >= alpha*G.eta[v] ? 1 : 0;
            }
            Sg.pop_back();
            if(score>maxScore){
                maxScore = score;
                max_u=u;
            }
        }
        Sg.push_back(max_u);
    }
    return Sg;
}

vector<int> LonGreedy(Graph &G,int k, double alpha2, double delta){
    vector<int> SL;
    Generator LvSet;
    LvSet.generateLvSets(G,alpha2,delta);
    while(SL.size()<k){
        cout<<SL.size()<<endl;
        int max_u=0,max_score=0;
        for(int u=0;u<G.nodeCount;u++){
            SL.push_back(u);
            int score=0;
            for(int v=0;v<G.nodeCount;v++){
                score+=LvSet.Lv(SL,v);
            }
            if(score>max_score){
                max_score = score;
                max_u=u;
            }
            SL.pop_back();
        }
        SL.push_back(max_u);
    }
    return SL;
}

vector<pair<double,double> > estimate(Graph &G,const vector<int> &R, const vector<int> &T,ConfigArgs &args){
    vector<pair<double,double> > res=vector<pair<double,double> >(args.TimeRound+1);
    for(int i=0;i<args.MonteCarlosTimes;i++){
        cout<<"Monte"<<i<<endl;
        vector<pair<int,int> > tmp=G.simulate(R,T,args.beta,args.delta,args.TimeRound);
        for(int j=0;j<res.size();j++){
            res[j].first+=tmp[j].first;
            res[j].second+=tmp[j].second;
        }
    }
    for(auto & re : res){
        re.first/=args.MonteCarlosTimes;
        re.second/=args.MonteCarlosTimes;
    }
    return res;
}