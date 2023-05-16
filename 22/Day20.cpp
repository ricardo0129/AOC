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
#define pll pair<ll,ll>

void part1(){
    ifstream file;
    file.open("in");
    vector<pll> A;
    ll x;
    ll i = 0;
    while(file>>x){
        A.pb(make_pair(x,i));
        i++;
    }
    int n = A.size();
    FOR(i,n) A[i].f*=(ll)811589153;
    int mod = n-1;
    FOR(t,10){
        FOR(i,n){
            int idx = -1;
            FOR(j,n) 
                if(A[j].s==i) idx = j;
            int new_idx = (((idx+A[idx].f)%mod)+mod)%mod; 
            pll V = A[idx];
            assert(new_idx>=0 && new_idx<n);
            assert(idx!=-1);
            A.erase(A.begin()+idx);
            A.insert(A.begin()+new_idx,V);
            //FOR(i,n) cout<<A[i].f<<" ";
            //cout<<endl;
        }
    }
    int cc = 0;
    FOR(i,n) if(A[i].f==0) cc++;
    assert(cc==1);
    int j=-1;
    FOR(i,n) if(A[i].f==0) j = i;
    cout<<A[(j+1000)%n].f+A[(j+2000)%n].f+A[(j+3000)%n].f<<endl;
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
