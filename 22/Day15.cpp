#include <bits/stdc++.h>
#include <vector>
#include <iostream> 
#include <fstream>
#include <set>
#define FOR(i,n) for(int i=0;i<n;i++)
#define sz size
#define pb push_back
using namespace std;
#define ll long long 
#define pii pair<int,int>
#define f first
#define s second
vector<pii> sensor;
vector<pii> beacon;
int checkrow(int row){
    int n = sz(sensor);
    vector<pii> intervals;
    FOR(i,n){
        int dist = abs(sensor[i].f-beacon[i].f)+abs(sensor[i].s-beacon[i].s);
        assert(dist>0);
        if(abs(row-sensor[i].s)<=dist){
            int delta = dist-abs(row-sensor[i].s);
            int l = sensor[i].f-delta;
            int r = sensor[i].f+delta;
            intervals.pb(make_pair(l,r));
        }
    }
    sort(intervals.begin(),intervals.end(),[](pii a, pii b){
        if(a.f==b.f) return a.s>b.s;
        return a.f<b.f;
    });
    int ans = 0;
    int l = intervals[0].f, r = intervals[0].s;
    for(int i=1;i<sz(intervals);i++){
       if(l<=intervals[i].f && intervals[i].f<=r) r = max(r,intervals[i].s);
       else{
            l = intervals[i].f;
            //skiping [r+1,l-1]
            if(0<=r+1 && r+1<=4000000) return r+1;
            r = intervals[i].s;
       }
    }
    ans+=r-l+1;
    set<pii> unique;
    FOR(i,sz(beacon)){
        if(beacon[i].s==row){
            unique.insert(beacon[i]);
        }
    }
    ans-=unique.size();
    return -1;
}
void part1(){
    ifstream file;
    file.open("in");
    string in;
    string g;
    while(getline(file,in)){
        stringstream ss(in);
        ss>>g>>g>>g;
        int x = stoi(g.substr(2,g.size()-3));
        ss>>g;
        int y = stoi(g.substr(2,g.size()-3));
        ss>>g>>g>>g>>g>>g;
        int bx = stoi(g.substr(2,g.size()-3));
        ss>>g;
        int by = stoi(g.substr(2,g.size()-2));
        sensor.pb(make_pair(x,y));
        beacon.pb(make_pair(bx,by));
    }
    FOR(i,4000000){
        int x = checkrow(i);
        if(x!=-1){
            cout<<i<<" "<<x<<endl;
            cout<<x*(ll)4000000+i<<endl;
        }
    }
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
