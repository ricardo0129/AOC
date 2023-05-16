#include <bits/stdc++.h>
#include <vector>
#include <iostream> 
#include <fstream>
#include <set>
#define FOR(i,n) for(int i=0;i<n;i++)
#define sz size
#define pii pair<int,int>
#define f first
#define s second
#define pb push_back
using namespace std;
#define ll long long 

int dx[] = {0,1,-1,0};
int dy[] = {1,0,0,-1};
void part1(){
    ifstream file;
    file.open("in");
    vector<string> g;
    string in;
    pii start;
    pii dest;
    map<pii,int> dist;
    while(file>>in){
        g.pb(in);
    }
    int r = g.size(); int c = g[0].size();
    FOR(i,r){
        FOR(j,c){
            if(g[i][j]=='S'){
                start = make_pair(i,j);
                g[i][j] = 'a';
            }
            if(g[i][j]=='E'){
                dest = make_pair(i,j);
                g[i][j] = 'z';
            }
        }
    }
    auto valid = [&](int i, int j){
        return i>=0 && i<r && j>=0 && j<c;   
    };
    dist[start] = 0;
    queue<pii> q;
    q.push(start);
    while(!q.empty()){
       pii ff = q.front(); q.pop(); 
       FOR(k,4){
            int i = ff.f+dx[k]; 
            int j = ff.s+dy[k];
            if(valid(i,j) && dist.count(make_pair(i,j))<=0 && (g[i][j]-g[ff.f][ff.s]<=1) ){
                dist[make_pair(i,j)] = dist[ff]+1;
                q.push(make_pair(i,j));
            }
       }
    }
    cout<<dist[dest]<<endl;

    file.close();
}

void part2(){
    ifstream file;
    file.open("in");
    vector<string> g;
    string in;
    pii start;
    pii dest;
    map<pii,int> dist;
    while(file>>in){
        g.pb(in);
    }
    int r = g.size(); int c = g[0].size();
    vector<pii> possible;
    FOR(i,r){
        FOR(j,c){
            if(g[i][j]=='S'){
                g[i][j] = 'a';
            }
            if(g[i][j]=='E'){
                start= make_pair(i,j);
                g[i][j] = 'z';
            }
            if(g[i][j]=='a'){
                possible.pb(make_pair(i,j));
            }
        }
    }
    auto valid = [&](int i, int j){
        return i>=0 && i<r && j>=0 && j<c;   
    };
    dist[start] = 0;
    queue<pii> q;
    q.push(start);
    while(!q.empty()){
       pii ff = q.front(); q.pop(); 
       FOR(k,4){
            int i = ff.f+dx[k]; 
            int j = ff.s+dy[k];
            if(valid(i,j) && dist.count(make_pair(i,j))<=0 && (g[ff.f][ff.s]-g[i][j]<=1) ){
                dist[make_pair(i,j)] = dist[ff]+1;
                q.push(make_pair(i,j));
            }
       }
    }
    int ans = INT_MAX;
    for(pii x: possible)
        if(dist.count(x)) ans = min(ans,dist[x]);
    cout<<ans<<endl;
}

int main()
{
    //part1();
    part2();
    return 0;
}
