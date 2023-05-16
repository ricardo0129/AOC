#include <bits/stdc++.h>
#define FOR(i,n) for(int i=0;i<n;i++)
#define sz size
#define pb push_back
#define all(x) begin(x), end(x)
using namespace std;
#define ll long long 
#define pii pair<int,int>
#define s second
#define f first
#define vi vector<int>

vector<pii> dir[4];
pii dir2[4] = {{-1,0},{1,0},{0,-1},{0,1}};
pii dir8[8] = {{-1,0},{1,0},{0,-1},{0,1},{1,1},{1,-1},{-1,1},{-1,-1}};
string in;
vector<string> G;
set<pii> taken;
struct Elf{
    int x, y;
    queue<int> pq;
    int proposed;
    Elf(int x = 0, int y = 0) : x(x), y(y) {
        FOR(i,4)
            pq.push(i);
    } 
    bool check(int m){
        FOR(i,3){
            int i2 = x+dir[m][i].f;
            int j2 = y+dir[m][i].s;
            if(taken.count({i2,j2})>0) return false;
        }
        return true;
    }
    void flip(){
        int x = pq.front(); pq.pop();
        pq.push(x);
    }
    pii getMove(){
        int move = -1;
        FOR(i,4){
            int m = pq.front(); pq.pop();
            if(check(m) && move==-1) move = m;
            pq.push(m);
        }       
        proposed = move;
        if(move==-1) return make_pair(x,y);
        return make_pair(x+dir2[move].f,y+dir2[move].s);
    }
    bool adjacent(){
        FOR(i,8){
            int i2 = x+dir8[i].f;
            int j2 = y+dir8[i].s;
            if(taken.count({i2,j2})>0) return true;
        }
        return false;
    }
};
vector<Elf> E;
void printG(){
    int l = INT_MAX, r = INT_MIN;
    int u = INT_MAX, d = INT_MIN;
    FOR(i,sz(E)){
        l = min(l,E[i].y);
        r = max(r,E[i].y);
        u = min(u,E[i].x);
        d = max(d,E[i].x);
    }
    for(int i=u-2;i<=d+2;i++){
        for(int j=l-2;j<=r+2;j++){
            if(taken.count({i,j})) cout<<"#";
            else cout<<".";
        }
        cout<<endl;
    }
    
}
void part1(){
    dir[0] = {{-1,-1},{-1,0},{-1,1}}; dir[1] = {{1,-1},{1,0},{1,1}};
    dir[2] = {{0,-1},{1,-1},{-1,-1}}; dir[3] = {{-1,1},{1,1},{0,1}};
    ifstream file;
    file.open("in");
    while(getline(file,in)){
        G.pb(in);
    }
    FOR(i,sz(G)){
        FOR(j,sz(G[i])){
            if(G[i][j]=='#'){
                E.pb(Elf(i,j));
                taken.insert(make_pair(i,j));
            }
        }
    }
    printG();
    FOR(i,10000000){
        set<pii> next;
        map<pii,int> mp;
        vector<pii> decided;
        vector<pii> prev;
        map<pii,int> to;
        FOR(j,sz(E)) prev.pb(make_pair(E[j].x,E[j].y));
        FOR(j,sz(E)){
            if(!E[j].adjacent()){
                decided.pb(make_pair(E[j].x,E[j].y));
                E[j].proposed = -1;
                mp[make_pair(E[j].x,E[j].y)]++;
            }
            else{
                pii g = E[j].getMove();
                decided.pb(g);
                mp[g]++;
            }
        }
        FOR(j,sz(E)){
            if(E[j].adjacent()){
                if(mp[decided[j]]==1){
                    E[j].x = decided[j].f;
                    E[j].y = decided[j].s;
                }
            }
        }
        FOR(j,sz(E)) 
            to[make_pair(E[j].x,E[j].y)]++;
        next.clear();
        FOR(j,sz(E)) next.insert(make_pair(E[j].x,E[j].y));
        assert(sz(next)==sz(E));
        if(taken==next){
            cout<<i+1<<endl;
            break;
        }
        taken = next;
        FOR(j,sz(E)) E[j].flip();
    }
    int l = INT_MAX, r = INT_MIN;
    int u = INT_MAX, d = INT_MIN;
    FOR(i,sz(E)){
        l = min(l,E[i].y);
        r = max(r,E[i].y);
        u = min(u,E[i].x);
        d = max(d,E[i].x);
    }
    int ans = (r-l+1)*(d-u+1)-sz(E);
    FOR(i,sz(E)) E[i].flip();
    printG();
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
