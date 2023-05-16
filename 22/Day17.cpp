#include <bits/stdc++.h>
#define FOR(i,n) for(int i=0;i<n;i++)
#define sz size
#define pb push_back
#define all(x) begin(x), end(x)
using namespace std;
#define ll long long 
#define pii pair<int,int>
#define vi vector<int>
#define f first
#define s second

set<pii> taken;
struct shape{
    int heigh,width;
    vector<vi> body;
    pii pos;
    shape(){}
    shape(int h, int w){
        heigh = h;
        width = w;
        body.assign(h,vi(w,false));
    }
    void addTile(int x, int y){
        body[y][x] = true;
    }
    void addPos(int x, int y){
        pos = make_pair(x,y);
    }
    void stopped(){
        for(int i=0;i<heigh;i++){
            for(int j=0;j<width;j++){
                if(!body[i][j]) continue;
                pii p = make_pair(pos.f+j,pos.s-i);
                taken.insert(p);
            }
        }
    }
    bool checkCollision(){
        for(int i=0;i<heigh;i++){
            for(int j=0;j<width;j++){
                if(!body[i][j]) continue;
                pii p = make_pair(pos.f+j,pos.s-i);
                if(taken.count(p)>0) return  true;
            }
        }
        return false;
    }
    bool moveHorizontal(int dir){
        pos.f+=dir;
        if(pos.f+width>7 || pos.f<0){
            pos.f-=dir;
            return false;
        }
        if(checkCollision()){
            pos.f-=dir;
            return false;
        }
        return true;
    }
    bool moveVertical(int dir){
        pos.s+=dir;
        if(pos.s-heigh<-1){
            pos.s-=dir;
            return false;
        }
        if(checkCollision()){
            pos.s-=dir;
            return false;
        }
        return true;
    }
    void print(){
        for(int i=0;i<heigh;i++){
            for(int j=0;j<width;j++){
                if(!body[i][j]) cout<<".";
                else cout<<"#";
            }
            cout<<endl;
        }
    }
};
void part1(){
    ifstream file;
    file.open("in");
    string in;
    file>>in;
    shape A[5];
    //l shape
    int floor = 0;
    A[0] = shape(1,4);
    A[0].addTile(0,0); A[0].addTile(1,0); A[0].addTile(2,0); A[0].addTile(3,0);
    A[0].print();

    A[1] = shape(3,3);
    A[1].addTile(1,0); A[1].addTile(0,1); A[1].addTile(1,1);
    A[1].addTile(2,1); A[1].addTile(1,2);
    A[1].print();

    A[2] = shape(3,3);
    A[2].addTile(2,0); A[2].addTile(2,1); A[2].addTile(0,2);
    A[2].addTile(1,2); A[2].addTile(2,2);
    A[2].print();

    A[3] = shape(4,1);
    A[3].addTile(0,0); A[3].addTile(0,1); A[3].addTile(0,2); A[3].addTile(0,3);
    A[3].print();

    A[4] = shape(2,2);
    A[4].addTile(0,0); A[4].addTile(0,1); A[4].addTile(1,0); A[4].addTile(1,1);
    A[4].print();
    int idx = 0;
    vector<pii> All;
    unordered_map<string,int> hash;
    const int N = 100400;
    pii prev = make_pair(0,0);
    vector<pii> states;
    int initial_floor;
    FOR(i,N){
        shape S = A[i%5];
        S.addPos(2,floor+3+S.heigh-1);
        //cout<<"START ("<<S.pos.f<<" "<<S.pos.s<<")"<<endl;
        while(true){
            if(in[idx]=='>')
                S.moveHorizontal(1);
            else
                S.moveHorizontal(-1);
            idx = (idx+1)%sz(in);
            if(!S.moveVertical(-1))
                break;
        }
        S.stopped();
        int before = floor;
        //285
        //2040
        if(i==285) initial_floor = floor;
        floor = max(floor,S.pos.s+1);
        assert(abs(S.pos.s-prev.s)<=50);
        prev = S.pos;
        All.pb(make_pair(i%5,floor-before));
        if(floor>=10){
            string in=to_string(i%5);
            for(int j=floor;j>=floor-10;j--){
                FOR(i,7){
                    if(taken.count(make_pair(i,j))){
                        in+="#";
                    }
                    else in+=".";
                }
            }
            if(hash.count(in)<=0) hash[in] = sz(hash);
            //if(sz(hash)>=1896)
            //cout<<i<<" "<<hash[in]<<" "<<floor-before<<endl;
            if(hash[in]==269) cout<<i<<endl;
            if(i>=285 && i<2040){
                states.pb(make_pair(hash[in],floor-before));
            }
        }
    }
    ll ans = initial_floor;
    ll start = 285;
    ll delta = 1000000000000-start;
    ll times = delta/(2039-285+1);
    ll tot = 0;
    FOR(i,sz(states)) tot+=states[i].s;
    ans+=tot*times;
    FOR(i,delta%sz(states)){
    ans+=states[i].s;
    }
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
