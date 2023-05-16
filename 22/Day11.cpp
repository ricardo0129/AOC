#include <bits/stdc++.h>
#include <vector>
#include <iostream> 
#include <fstream>
#include <set>
#define FOR(i,n) for(int i=0;i<n;i++)
#define pii pair<int,int>
#define vi vector<int>
#define sz size
#define f first
#define s second
#define pb push_back
using namespace std;
#define ll long long 
#define pll pair<ll,ll>

struct num{
    vector<ll> vals;
    vector<ll> mods;
    map<ll,int> modpos;
    num(){
    }
    void add(ll x){
        int n = mods.size();
        FOR(i,n){
            vals[i] = ((vals[i]%mods[i])+(x%mods[i]))%mods[i];
            assert(vals[i]>=0);
        }
    }
    void mult(ll x){
        int n = mods.size();
        FOR(i,n){
            vals[i] = ((vals[i]%mods[i])*(x%mods[i]))%mods[i];
            assert(vals[i]>=0);
        }
    }
    void square(){
        int n = mods.size();
        FOR(i,n){
            vals[i] = ((vals[i]%mods[i])*(vals[i]%mods[i]))%mods[i];
            assert(vals[i]>=0);
        }
    }
    void twice(){
        int n = mods.size();
        FOR(i,n){
            vals[i] = ((vals[i]%mods[i])+(vals[i]%mods[i]))%mods[i];
            assert(vals[i]>=0);
        }
    }
    bool test(ll div){
        return vals[modpos[div]]==0;
    }
    ll get(ll div){
        return vals[modpos[div]];
    }
};
struct monkey{
    queue<num> items;
    bool mult;
    ll off;
    ll divi;
    ll pass, fail;
    bool prev;
    int inspections;
    monkey(){
        inspections=0;
        prev = false;
        mult = false;
    }
    void add(num x){
        items.push(x);
    }
    pair<int,num> toss(){
        inspections++;
        num x = items.front(); items.pop();
        if(mult){
            if(prev) x.square();
            else x.mult(off);
        }
        else{
            if(prev) x.twice();
            else x.add(off);
        }
        //x/=3;
        ll to;
        if(x.test(divi)){
            to = pass;
        }
        else to = fail;
        return make_pair(to,x);
    }
};
void part1(){
    ifstream file;
    file.open("in");
    string in;
    vector<monkey> M;
    vector<vi> vals;
    while(file>>in>>in){
        file>>in>>in;
        monkey m1;
        vi all;
        while(file>>in){
            if(in[0]=='O') break;
            if(!isdigit(in[in.size()-1])) in.pop_back();
            //m1.add(stoi(in));
            all.pb(stoi(in));
        }
        file>>in>>in>>in>>in;
        if(in[0]=='*') m1.mult = true;
        file>>in;
        if(in[0]=='o'){
            m1.prev = true;
        }
        else 
            m1.off = stoi(in);
        file>>in>>in>>in>>in;
        m1.divi = stoi(in);
        file>>in>>in>>in>>in>>in>>in;
        m1.pass = stoi(in);
        file>>in>>in>>in>>in>>in>>in;
        m1.fail = stoi(in);
        M.pb(m1);
        vals.pb(all);
    }
    int idx = 0;
    for(vi xx: vals){
        for(int y: xx){
            num mm;
            FOR(i,M.size()){
                mm.modpos[M[i].divi] = mm.mods.size();
                mm.mods.pb(M[i].divi);
                mm.vals.pb(y);
            }
            M[idx].add(mm);
        }
        idx++;
    }
    FOR(i,10000){
        //FOR(j,M.size()) taking[j] = M[j].items.size();
        FOR(j,M.size()){
            while(M[j].items.size()){
                pair<int,num> item = M[j].toss();
                M[item.f].add(item.s);
            }
        }
    }
    vector<ll> tot;
    FOR(j,M.size()){
        tot.pb(M[j].inspections);
    }
    sort(tot.begin(),tot.end());
    int n = tot.size();
    for(ll x: tot) cout<<x<<endl;
    cout<<tot[n-1]*tot[n-2]<<endl;
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
