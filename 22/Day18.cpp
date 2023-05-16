#include <bits/stdc++.h>
#define FOR(i,n) for(int i=0;i<n;i++)
#define sz size
#define pb push_back
#define all(x) begin(x), end(x)
using namespace std;
#define ll long long 
#define pii pair<int,int>
#define vi vector<int>
template<class T>
struct Point {
	typedef Point P;
	T x, y,z;
	explicit Point(T x=0, T y=0, T z=0) : x(x), y(y), z(z) {}
	bool operator<(P p) const { return tie(x,y,z) < tie(p.x,p.y,p.z); }
	P operator+(P p) const { return P(x+p.x, y+p.y,z+p.z); }
};

typedef Point<ll> P;
int dx[] = {0,0,1,-1,0,0};
int dy[] = {1,-1,0,0,0,0};
int dz[] = {0,0,0,0,1,-1};

void part1(){
    ifstream file;
    file.open("in");
    string in;
    set<P> points;
    while(getline(file,in)){
        int p = 0;
        vi A;
        FOR(i,sz(in)){
            if(in[i]==','){
                int x = stoi(in.substr(p,i-p));
                A.pb(x);
                p = i+1;
            }
        }
        A.pb(stoi(in.substr(p,sz(in)-p)));
        points.insert(P(A[0],A[1],A[2]));
    }
    int n = sz(points);
    /*
    int ans = 6*n;
    for(P p: points){
        FOR(i,6){
            P neighboor = p+P(dx[i],dy[i],dz[i]);
            if(points.count(neighboor)>0) ans--; 
        }
    }
    */
    auto valid = [&](P p){
        return p.x>=-30 && p.x<=30 && p.y>=-30 && p.y<=30 && p.z>=-30 && p.z<=30;
    };
    int ans = 0;
    vector<P> starting;
    starting.pb(P(0,29,29));
    for(P start : starting){
        set<P> vist;
        queue<P> q;
        q.push(start);
        vist.insert(start);
        while(!q.empty()){
            P p = q.front(); q.pop();
            FOR(i,6){
                P neighboor = p+P(dx[i],dy[i],dz[i]);
                if(points.count(neighboor)>0) ans++; 
                else if(valid(neighboor) && vist.count(neighboor)<=0){
                    q.push(neighboor);
                    vist.insert(neighboor);
                }
            }
        }
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
