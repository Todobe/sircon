#include "Functions.h"
#include <queue>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <ctime>

Generator::Generator(const Graph &G){
    Cnt=vector<int>(G.nodeCount,0);
    UU=vector<vector<int> >(G.nodeCount);
};

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
            //RRSets[v].push_back(generateRRSet(G,v,p));
            vector<int> Lv;
            int Phi=int(G.T);
            map<int, int> vis;
            queue<int> que;
            que.push(v);
            vis[v]=0;
            Lv.push_back(v);
            while(!que.empty()){
                int cur=que.front();
                que.pop();
                for(auto u:G.fro[cur]){
                    if(vis.count(u)==0 && getRandFloat()<=p){
                        vis[u]=vis[cur]+1;
                        Lv.push_back(u);
                        if(vis[u]<Phi) {
                            que.push(u);
                        }
                    }
                }
            }
            sort(Lv.begin(),Lv.end());
            RRSets[v].push_back(Lv);
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
        Phi=min(Phi,int(G.T));
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
        for(auto node:Lv){
            Cnt[node]++;
            UU[node].push_back(v);
        }
        LvSets[v]=Lv;
    }
    VisLV=vector<bool>(G.nodeCount,false);
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
        for(auto node:IMMRRSets[i]){
            Cnt[node]++;
            UU[node].push_back(i);
        }
    }
    VisLV=vector<bool>(IMMRRSets.size(),false);
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

bool InterSection(const vector<int> &a, const vector<int> &b){
    int i=0,j=0;
    while(i<a.size() && j<b.size()){
        if(a[i]==b[j]) return true;
        if(a[i]<b[j]) i++;
        else if(a[i]>b[j]) j++;
    }
    return false;
}

vector<int> Generator::ReverseSampling(const Graph &G, set<pair<int,int> > &Et, set<pair<int,int> > &Ef, const vector<int> &Sr, int v, double p){
    vector<int> PStar,P;
    PStar.push_back(v);
    while(true){
        sort(PStar.begin(),PStar.end());
        if(InterSection(PStar,Sr)){
            return P;
        }
        for(auto node:PStar){
            P.push_back(node);
        }
        sort(P.begin(),P.end());
        auto it=unique(P.begin(),P.end());
        P.erase(it,P.end());
        vector<int> tmp=PStar;
        PStar.clear();
        for(auto u2:tmp){
            for(auto u1:G.fro[u2]){
                auto e=make_pair(u1,u2);
                if(Et.find(e)!=Et.end()){
                    PStar.push_back(u1);
                    continue;
                }
                if(Ef.find(e)!=Ef.end()){
                    continue;
                }
                if(getRandFloat()<=p){
                    PStar.push_back(u1);
                    Et.insert(e);
                }else{
                    Ef.insert(e);
                }
            }
        }

    }
}

bool Generator::HybridSampling(const Graph &G, const vector<int> &Sr, int theta, double p) {
    for(int i=0;i<theta;){
        set<pair<int,int> > Et,Ef;
        vector<int> Vr;
        queue<int> que;
        vector<bool> vis(G.nodeCount,false);
        for(auto node:Sr) {
            vis[node]=true;
            que.push(node);
        }
        while(!que.empty()){
            int cur=que.front();
            Vr.push_back(cur);
            que.pop();
            for(auto v:G.to[cur]){
                if(getRandFloat()<=p){
                    Et.insert(make_pair(cur,v));
                    if(!vis[v]){
                        vis[v]=true;
                        que.push(v);
                    }
                }else{
                    Ef.insert(make_pair(cur,v));
                }
            }
        }
        for(auto v:Vr){
            RSamples.push_back(ReverseSampling(G,Et,Ef,Sr,v,p));
            for(auto node:RSamples[i]){
                Cnt[node]++;
                UU[node].push_back(i);
            }
            i++;
        }
    }
    VisLV=vector<bool>(RSamples.size(),false);
    return true;
}


vector<int> RisGreedy(Graph &G,int k, int theta, double alpha, double delta, vector<double> & algTime){
    algTime.clear();
    vector<int> Sg;
    Generator RRSet(G);
    RRSet.generateRRSets(G,theta,delta);
    clock_t start_time=clock();
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
        algTime.push_back((clock()-start_time)/CLOCKS_PER_SEC);
    }
    return Sg;
}

vector<int> LonGreedy(Graph &G,int k, double alpha2, double delta, vector<double> & algTime){
    algTime.clear();
    clock_t start_time=clock();
    vector<int> SL;
    Generator LvSet(G);
    LvSet.generateLvSets(G,alpha2,delta);
    while(SL.size()<k){
        int max_u=0,max_score=0;
        for(int u=0;u<G.nodeCount;u++){
            int score=LvSet.Cnt[u];
            if(score>max_score){
                max_score = score;
                max_u=u;
            }

        }
        for(auto v:LvSet.UU[max_u]){
            if(LvSet.VisLV[v]) continue;
            LvSet.VisLV[v]=true;
            for(auto u:LvSet.LvSets[v]){
                LvSet.Cnt[u]--;
            }
        }
        LvSet.Cnt[max_u]=-1;
        SL.push_back(max_u);
        algTime.push_back((clock()-start_time)/CLOCKS_PER_SEC);
    }
    return SL;
}

vector<int> ImmGreedy(Graph &G, int k, int theta, double delta, vector<double> & algTime){
    algTime.clear();
    clock_t start_time=clock();
    vector<int> Sk;
    Generator RRSet(G);
    RRSet.generateIMMRRSets(G,theta,delta);
    while(Sk.size()<k){
        int max_u=0;
        double max_score=0;
        for(int u=0;u<G.nodeCount;u++){
            double score=RRSet.Cnt[u];
            if(score>max_score){
                max_score=score;
                max_u=u;
            }
        }
        for(auto v:RRSet.UU[max_u]){
            if(RRSet.VisLV[v]) continue;
            RRSet.VisLV[v]=true;
            for(auto u:RRSet.IMMRRSets[v]){
                RRSet.Cnt[u]--;
            }
        }
        RRSet.Cnt[max_u]=-1;
        Sk.push_back(max_u);
        algTime.push_back((clock()-start_time)/CLOCKS_PER_SEC);
    }
    return Sk;
}

vector<int> MaxDegree(Graph &G ,int k, vector<double> & algTime){
    algTime.clear();
    clock_t start_time=clock();
    vector<int> T;
    vector<pair<int,int> > Deg_Node;
    for(int i=0;i<G.nodeCount;i++){
        Deg_Node.emplace_back(G.to[i].size(),i);
    }
    sort(Deg_Node.begin(),Deg_Node.end(),greater<pair<int,int> >());
    for(int i=0;i<k;i++){
        T.push_back(Deg_Node[i].second);
        algTime.push_back((clock()-start_time)/CLOCKS_PER_SEC);
    }
    return T;
}


vector<int> PageRank(Graph &G, int k, vector<double> &algTime, double d){
    algTime.clear();
    clock_t start_time=clock();
    vector<double> Pr(G.nodeCount),tPr(G.nodeCount,0);
    for(int i=0;i<G.nodeCount;i++)  Pr[i]=1.0/G.nodeCount;
    const double eps=1e-9;
    double sum=1;
    while(sum>eps) {
        sum=0;
        for (int i = 0; i < G.nodeCount; i++) {
            for (auto v: G.to[i]) {
                tPr[v] += Pr[i] / G.to[i].size();
            }
        }
        for(int i=0; i< G.nodeCount;i++){
            tPr[i]=d*tPr[i]+(1-d)/G.nodeCount;
            sum+=abs(tPr[i]-Pr[i]);
            Pr[i]=tPr[i];
            tPr[i]=0;
        }
    }
    vector<int> T;
    vector<pair<double,int> > Pr_Node;
    for(int i=0;i<G.nodeCount;i++){
        Pr_Node.emplace_back(Pr[i],i);
    }
    sort(Pr_Node.begin(),Pr_Node.end(),greater<pair<double,int> >());
    for(int i=0;i<k;i++){
        T.push_back(Pr_Node[i].second);
        algTime.push_back((clock()-start_time)/CLOCKS_PER_SEC);
    }
    return T;
}


vector<int> HMP(Graph &G, int k, const vector<int> &R, int theta, double beta, vector<double> &algTime){
    algTime.clear();
    clock_t start_time=clock();
    vector<int> Sk;
    Generator Rl(G);
    Rl.HybridSampling(G,R,theta,beta);
    while(Sk.size()<k){
        int max_u=0;
        double max_score=0;
        for(int u=0;u<G.nodeCount;u++){
            double score=Rl.Cnt[u];
            if(score>max_score){
                max_score=score;
                max_u=u;
            }
        }
        for(auto v:Rl.UU[max_u]){
            if(Rl.VisLV[v]) continue;
            Rl.VisLV[v]=true;
            for(auto u:Rl.RSamples[v]){
                Rl.Cnt[u]--;
            }
        }
        Rl.Cnt[max_u]=-1;
        Sk.push_back(max_u);
        algTime.push_back((clock()-start_time)/CLOCKS_PER_SEC);
    }
    return Sk;

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


vector<pair<double,double> > estimate(Graph &G,const vector<int> &R, const vector<int> &T,const vector<pair<int,int> > &DelEdge, ConfigArgs &args, double &simTime){
    clock_t start_time = clock();
    vector<pair<double,double> > res=vector<pair<double,double> >(args.TimeRound+1);
    for(int i=0;i<args.MonteCarlosTimes;i++){
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
    clock_t end_time = clock();
    simTime += (end_time - start_time)/CLOCKS_PER_SEC;
    return res;
}