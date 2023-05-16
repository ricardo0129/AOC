#include <bits/stdc++.h>
#define FOR(i,n) for(int i=0;i<n;i++)
#define sz size
#define pb push_back
#define all(x) begin(x), end(x)
using namespace std;
#define ll long long 
#define pii pair<int,int>
#define f first
#define s second

map<char,ll> val;
ll convert(string in){
    ll curr = 0;
    ll p=0;
    for(int i=sz(in)-1;i>=0;i--){
        curr+=(ll)pow(5,p++)*val[in[i]];
    }
    return curr;
}
map<ll,string> l;
map<ll,string> r;
void revert(ll curr,string v,map<ll,string>& mp,int big){
    if(sz(v)==big){
        reverse(v.begin(),v.end());
        mp[curr] = v;
        return;
    }
    for(auto x: val){
        revert(curr+(ll)pow(5,(int)sz(v))*x.s,v+string(1,x.f),mp,big);
    }
}
void part1(){
    val['0'] = 0; val['1'] = 1; val['2'] = 2; val['-'] = -1; val['='] = -2;
    ifstream file;
    file.open("in");
    string in;
    ll ans = 0;
    while(getline(file,in)){
        ans+=convert(in);
    }
    cout<<ans<<endl;
    revert(0,"",l,10);
    revert(0,string(10,'x'),r,20);
    ans = 4890;
    for(auto x: l){
        ll diff = ans-x.f;
        if(r.count(diff)>0){
            cout<<x.s<<" "<<r[diff]<<endl;
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
