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

bool Generator::generateIMMRRSets(const Graph &G, int theta, double p) {
    for(int i=0;i<theta;i++){
        int v= getRandInt(0,G.nodeCount);
        IMMRRSets.push_back(generateRRSet(G,v,p));
    }
    return true;
}

double Generator::FR(const Graph &G,const vector<int> &S, int u) {
    double cnt=0;
    for(auto RRSet:IMMRRSets){
        if(!binary_search(RRSet.begin(),RRSet.end(),u)) continue;
        int flag=1;
        for(auto node:S){
            if(binary_search(RRSet.begin(),RRSet.end(),node)){
                flag=0;
                break;
            }
        }
        cnt += flag;
    }
    return cnt*G.nodeCount/IMMRRSets.size();
}


vector<int> RisGreedy(Graph &G,int k, int theta, double alpha, double delta){
    vector<int> Sg;
    Generator RRSet;
    RRSet.generateRRSets(G,theta,delta);
    while(Sg.size()<k){
        int  max_u=0;
        double maxScore=0;
        for(int u=0;u<G.nodeCount;u++){
            double score=0;
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

vector<int> ImmGreedy(Graph &G, int k, int theta, double delta){
    vector<int> Sk;
    Generator RRSet;
    RRSet.generateIMMRRSets(G,theta,delta);
    while(Sk.size()<k){
        int max_u=0;
        double max_score=0;
        for(int u=0;u<G.nodeCount;u++){
            double score=RRSet.FR(G,Sk,u);
            if(score>max_score){
                max_score=score;
                max_u=u;
            }
        }
        Sk.push_back(max_u);
    }
    return Sk;
}

vector<int> MaxDegree(Graph &G ,int k){
    vector<int> T;
    vector<pair<int,int> > Deg_Node;
    for(int i=0;i<G.nodeCount;i++){
        Deg_Node.emplace_back(G.to[i].size(),i);
    }
    sort(Deg_Node.begin(),Deg_Node.end(),greater<pair<int,int> >());
    for(int i=0;i<k;i++){
        T.push_back(Deg_Node[i].second);
    }
    return T;
}

vector<pair<int,int> > EdgeDeletion(Graph &G, int k){
    vector<pair<int,int> > DelEdge;
    vector<double> u=G.leftEigVec;
    vector<double> v=G.rightEigVec;
    double min_ui=u[0], min_vi=v[0];
    for(auto ui:u) min_ui = min(min_ui,ui);
    for(auto vi:v) min_vi = min(min_vi,vi);
    if(min_ui < 0){
        for(double & ui : u) ui=-ui;
    }
    if(min_vi < 0){
        for(double & vi : v) vi=-vi;
    }
    vector<pair<double,pair<int,int> > > Score_Node;
    for(int i=0;i<G.nodeCount;i++){
        for(int j=0;j<G.to[i].size();j++){
            Score_Node.emplace_back(u[i]*v[G.to[i][j]],make_pair(i,G.to[i][j]));
        }
    }
    sort(Score_Node.begin(),Score_Node.end(),greater<pair<double,pair<int,int> > >());
    for(int i=0;i<k;i++){
        DelEdge.push_back(Score_Node[i].second);
    }
    sort(DelEdge.begin(),DelEdge.end());
    return DelEdge;
}


vector<pair<double,double> > estimate(Graph &G,const vector<int> &R, const vector<int> &T,const vector<pair<int,int> > &DelEdge, ConfigArgs &args){
    vector<pair<double,double> > res=vector<pair<double,double> >(args.TimeRound+1);
    for(int i=0;i<args.MonteCarlosTimes;i++){
        cout<<"Monte"<<i<<endl;
        vector<pair<int,int> > tmp=G.simulate(R,T,args.beta,args.delta,args.TimeRound,DelEdge);
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