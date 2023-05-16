#include <bits/stdc++.h>
#define FOR(i,n) for(int i=0;i<n;i++)
#define sz size
#define pb push_back
#define all(x) begin(x), end(x)
using namespace std;
#define ll long long 
#define vi vector<int>
#define pii pair<int,int>
#define f first 
#define s second

vector<string> A;
map<string,int> mp;
vi G[100];
bool active[100];
int flow[100];
vi good_flow;
bool vist[100];
int ans = 0;
map<int,int>mp2;
int mp3[100];
map<string,int> fflow;
/*
int dp[70][31][1<<16];
int solve(int pos, int time_left, int bitmask){
    assert(bitmask<1<<16);
    if(time_left==0) return 0;
    if(dp[pos][time_left][bitmask]>=0) return dp[pos][time_left][bitmask];
    int best = 0;
    if(mp2.count(pos)>0 && !(bitmask&(1<<mp2[pos])) ){
        assert(mp2[pos]<=15 && mp2[pos]>=0);
        best = max(best,(time_left-1)*good_flow[mp2[pos]]+solve(pos,time_left-1,bitmask|(1<<mp2[pos]) ));
    }
    for(int v: G[pos]){
        //go to next place
        best = max(best,solve(v,time_left-1,bitmask));
    }
    return dp[pos][time_left][bitmask] = best;
}
*/
vector<vector<vector<vector<int>>>> dp2;
//short dp2[65][65][26][1<<15];
int solve2(int pos1,int pos2, int time_left, int bitmask){
    if(time_left==0) return 0;
    if(dp2[pos1][pos2][time_left][bitmask]>=0) return dp2[pos1][pos2][time_left][bitmask];
    //move 1 & 2 
    //turn on 1 & move 2
    int best = 0;
    //turn on 1 & turn on 2
    if(mp3[pos1]>=0 && !(bitmask&(1<<mp3[pos1])) 
    && mp3[pos2]>=0 && !(bitmask&(1<<mp3[pos2])) 
    ){
        int nflow = (time_left-1)*good_flow[mp3[pos1]] + (time_left-1)*good_flow[mp3[pos2]];
        if(pos1==pos2) nflow-=(time_left-1)*good_flow[mp3[pos1]];
        int val = solve2(pos1,pos2,time_left-1,bitmask|(1<<mp3[pos1])|(1<<mp3[pos2]) );
        best = max(best,val+nflow);
    }
    //move 2 & turn on 1 
    if(mp3[pos1]>=0 && !(bitmask&(1<<mp3[pos1]))){
        int nflow = (time_left-1)*good_flow[mp3[pos1]];
        int b1 = bitmask|(1<<mp3[pos1]);
        for(int v: G[pos2]){
            best = max(best,solve2(pos1,v,time_left-1,b1)+nflow);
        }
    }
    if(mp3[pos2]>=0 && !(bitmask&(1<<mp3[pos2]))){
        int nflow = (time_left-1)*good_flow[mp3[pos2]];
        int b1 = bitmask|(1<<mp3[pos2]);
        for(int v: G[pos1]){
            best = max(best,solve2(v,pos2,time_left-1,b1)+nflow);
        }
    }
    for(int v1: G[pos1]){
        for(int v2: G[pos2]){
            best = max(best,solve2(v1,v2,time_left-1,bitmask));
        }
    }
    return dp2[pos1][pos2][time_left][bitmask] = best;
    //return best;
}
void part1(){
    ifstream file;
    memset(vist,false,sizeof(vist));
    file.open("in");
    string in;
    while(getline(file,in)){
        stringstream ss(in);
        string g;
        string from;
        ss>>g>>from;
        if(mp.count(from)<=0){
            mp[from] = mp.size();
            A.pb(from);
        }
        ss>>g>>g>>g;
        int ff = stoi(g.substr(5,sz(g)-6));
        flow[mp[from]] = ff;
        fflow[from] = ff;
        ss>>g>>g>>g>>g;
        while(ss>>g){
            string to = g.substr(0,2);
            if(mp.count(to)<=0){
                mp[to] = mp.size();
                A.pb(to);
            }
            G[mp[from]].pb(mp[to]);
        }
    }
    memset(mp3,-1,sizeof(mp3));
    int cc = 0;
    for(auto s: fflow){
        if(s.s){
            cout<<s.f<<" "<<s.s<<endl;
            mp2[mp[s.f]] = mp2.size();
            mp3[mp[s.f]] = mp2[mp[s.f]];
            good_flow.pb(s.s);
            cc++;
        }
    }
    //memset(dp2,-1,sizeof(dp2));
    //int ans = solve(mp["AA"],30,0);
    //short dp2[65][65][26][1<<15];
    dp2.assign(67,vector<vector<vector<int>>>(67,vector<vector<int>>(27,vi(1<<16,-1))));
    int ans = solve2(mp["AA"],mp["AA"],26,0);
    cout<<ans<<endl;
    file.close();
}

void part2(){
    ifstream file;
    file.open("in");
    file.close();
}

int main()
{
    part1();
    //part2();
    return 0;
}
