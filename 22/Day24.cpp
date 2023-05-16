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
#define vi vector<int> 

const int INF = 1e7+9;
pii source,sink;
vector<vector<vi>> taken;
int r, c;
vector<string> G;
int m;
vector<pii> dirs = {{0,0},{1,0},{-1,0},{0,1},{0,-1}};
int dp[40][110][1000][3];
int solve(int i, int j, int turn,int task){
    if(turn>=1000) return INF;
    if(task==0 && i==sink.f && j==sink.s) return solve(i,j,turn,1);
    if(task==1 && i==0 && j==1) return solve(i,j,turn,2);
    if(task==2 && i==sink.f && j==sink.s) return 0;
    if(dp[i][j][turn][task]!=-1) return dp[i][j][turn][task];
    assert(!taken[i][j][turn%m]);
    int best = INF;
    FOR(k,sz(dirs)){
        int i2 = i+dirs[k].f;
        int j2 = j+dirs[k].s;
        if(i2>=0 && i2<=r-1 && G[i2][j2]!='#' && !taken[i2][j2][(turn+1)%m]){
            best = min(best,solve(i2,j2,turn+1,task)+1);
        }
    }
    return dp[i][j][turn][task] = best;
}
int gcd(int a, int b){
    if(b==0) return a;
    return gcd(b,a%b);
}
int lcm(int a, int b){
    return a*b/gcd(a,b);
}
void part1(){
    ifstream file;
    file.open("in");
    string in;
    while(file>>in) G.pb(in);
    r = sz(G); c = sz(G[0]);
    vector<pii> blizzard;
    FOR(i,r) FOR(j,c){
        if(G[i][j]!='#' && G[i][j]!='.'){
            blizzard.pb({i,j});
        }
    }
    map<char,pii> dir;
    dir['>'] = {0,1}; dir['<'] = {0,-1}; dir['^'] = {-1,0}; dir['v'] = {1,0};
    m = lcm(r,c);
    cout<<r<<" "<<c<<endl;
    taken.resize(r,vector<vi>(c,vi(m,0)));

    for(pii b: blizzard){
        pii curr = b;
        pii d = dir[G[b.f][b.s]];
        FOR(i,m){
            taken[curr.f][curr.s][i] = 1;
            curr.f+=d.f; curr.s+=d.s;
            if(curr.f==r-1) curr.f = 1;
            if(curr.f==0) curr.f = r-2;
            if(curr.s==0) curr.s = c-2;
            if(curr.s==c-1) curr.s = 1;
        }
    }
    source = make_pair(0,1);
    sink = make_pair(r-1,c-2);
    memset(dp,-1,sizeof(dp));
    int ans = solve(source.f,source.s,0,0);
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
