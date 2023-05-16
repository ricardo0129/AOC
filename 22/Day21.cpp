#include <bits/stdc++.h>
#define FOR(i,n) for(int i=0;i<n;i++)
#define sz size
#define pb push_back
#define all(x) begin(x), end(x)
using namespace std;
#define ll long long 
#define pii pair<int,int>
#define vi vector<int> 
map<string,int> mp;
vector<string> A;
const int N = 2000;
ll val[N];
vi indeg;
int opp[N];
vi G[N];
ll Left[N];
ll Right[N];
void part1(){
    ifstream file;
    file.open("in");
    string in;
    queue<int> q;
    map<char,int> tree;
    indeg.resize(N);
    tree['+'] = 1; tree['-'] = 2; 
    tree['*'] = 3; tree['/'] = 4;
    memset(val,-1,sizeof val);
    while(getline(file,in)){
        stringstream ss(in);
        string name;
        ss>>name; name.pop_back();
        if(mp.count(name)<=0){
            mp[name] = mp.size();
            A.pb(name);
        }
        string first;
        ss>>first;
        if(isdigit(first[0])){
            val[mp[name]] = stoi(first);
            q.push(mp[name]);
        }
        else{
            char operation;
            string second;
            ss>>operation>>second;
            if(mp.count(first)<=0)
                mp[first] = mp.size();
            if(mp.count(second)<=0)
                mp[second] = mp.size();
            Left[mp[name]] = mp[first];
            Right[mp[name]] = mp[second];
            opp[mp[name]] = tree[operation];
            indeg[mp[name]]+=2;
            G[mp[first]].pb(mp[name]);
            G[mp[second]].pb(mp[name]);
        }
    }
    queue<int> q2 = q;
    vi indeg2 = indeg;
    ll l = -1e17, r = 1e17;
    bool quit = false;
    while(!quit){
        q = q2;
        indeg = indeg2;
        ll m = (r-l)/2+l;
        val[mp["humn"]] = m;
        while(!q.empty()){
            int u = q.front(); q.pop();
            if(u==mp["root"]){
                if(val[Left[u]]==val[Right[u]]){
                    cout<<m<<endl;
                    quit = true;
                }
                else if(val[Left[u]]>val[Right[u]]){
                    l = m+1;
                }
                else{
                    r = m-1;
                }
                break;
            }
            if(opp[u]!=0){
                ll l = val[Left[u]]; ll r = val[Right[u]];
                if(opp[u]==1) val[u] = l+r;
                else if(opp[u]==2) val[u] = l-r;
                else if(opp[u]==3) val[u] = l*r;
                else if(opp[u]==4) val[u] = l/r;
            }
            for(int v: G[u]){
                indeg[v]--;
                if(indeg[v]==0) q.push(v);
            }
        }
    }
    //cout<<val[mp["root"]]<<endl;
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
