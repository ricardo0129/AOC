#include <vector>
#include <bits/stdc++.h>
#include <iostream> 
#include <fstream>
#include <set>
#define FOR(i,n) for(int i=0;i<n;i++)
#define sz size
#define pb push_back
using namespace std;
#define ll long long 

struct cpu{
    int clock = 1;
    int reg = 1; 
    map<int,int> mp;
    void noop(){
        mp[clock] = reg;
        clock+=1;
    }
    void addx(int v){
        mp[clock] = reg;
        mp[clock+1] = reg;
        reg+=v;
        clock+=2;
    }
    ll get(int cyc){
        if(cyc==clock) return reg;
        return cyc*mp[cyc];
    }
    ll valAt(int cyc){
        if(cyc==clock) return reg;
        return mp[cyc];
    }
};  
void part1(){
    ifstream file;
    file.open("in");
    cpu comp;

    string in;
    while(file>>in){
        if(in=="noop") comp.noop();
        else{
            int v; file>>v;
            comp.addx(v);
        }
    }
    int ans = 0;
    int vals[] = {20,60,100,140,180,220};
    for(int i=0;i<6;i++) 
        ans+=comp.get(vals[i]);
    cout<<ans<<endl;
    file.close();
}

void part2(){
    ifstream file;
    file.open("in");
    cpu comp;

    string in;
    while(file>>in){
        if(in=="noop") comp.noop();
        else{
            int v; file>>v;
            comp.addx(v);
        }
    }
    vector<string> ans(6,string(40,'0'));
    for(int i=0;i<6;i++){
        for(int j=0;j<40;j++){
            int clock = i*40+j+1;
            bool on = false;
            int pos = comp.valAt(clock)+i*40+1;
            if(pos==clock || pos-1==clock || pos+1==clock) on = true;
            ans[i][j] = on?'#':'.';
        }
    } 

    for(string s: ans) cout<<s<<endl;
    file.close();
}

int main()
{
    //part1();
    part2();
    return 0;
}
