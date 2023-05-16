#include <vector>
#include <iostream> 
#include <fstream>
#include <set>
#define FOR(i,n) for(int i=0;i<n;i++)
#define sz size
#define s second
#define f first
#define pb push_back
#define pii pair<int,int>
using namespace std;
#define ll long long 

void updateTail(pii& head, pii& tail){
    if(abs(head.f-tail.f)<=1 && abs(head.s-tail.s)<=1) return;
    if(abs(head.f-tail.f)==0){
        if(tail.s>head.s) tail.s--;
        else tail.s++;
    }
    else if(abs(head.s-tail.s)==0){
        if(tail.f>head.f) tail.f--;
        else tail.f++;
    }
    else{
        int close = 10000000;
        vector<pii> dir = { {-1,-1},{1,1},{-1,1},{1,-1}};
        pii move;
        for(pii x: dir){
            int dd = abs(head.f-(tail.f+x.f))+abs(head.s-(tail.s+x.s));
            if(dd<=close){
                close = dd;
                move = x;
            }
        }
        tail.f+=move.f;
        tail.s+=move.s;
    }
}

void part1(){
    ifstream file;
    file.open("in");
    const int N = 1000;
    vector<vector<bool>> grid(N,vector<bool>(N,false));
    pii head = {N/2,N/2};
    pii tail = {N/2,N/2};
    grid[N/2][N/2] = true;
    char d;
    int times;
    while(file>>d>>times){
        if(d=='R'){
            FOR(k,times){
               head.s++; 
               updateTail(head,tail);
    assert(head.f>=0 && head.f<N && head.s>=0 && head.s<N && tail.f>=0 && tail.f<N && tail.s>=0 && tail.s<N);
               grid[tail.f][tail.s] = true;
            }
        }
        else if(d=='L'){
            FOR(k,times){
                head.s--;
                updateTail(head,tail);
    assert(head.f>=0 && head.f<N && head.s>=0 && head.s<N && tail.f>=0 && tail.f<N && tail.s>=0 && tail.s<N);
                grid[tail.f][tail.s] = true;
            }
        }
        else if(d=='D'){
            FOR(k,times){
                head.f++;
                updateTail(head,tail);
    assert(head.f>=0 && head.f<N && head.s>=0 && head.s<N && tail.f>=0 && tail.f<N && tail.s>=0 && tail.s<N);
                grid[tail.f][tail.s] = true;
            }
        }
        else if(d=='U'){
            FOR(k,times){
                head.f--;
                updateTail(head,tail);
    assert(head.f>=0 && head.f<N && head.s>=0 && head.s<N && tail.f>=0 && tail.f<N && tail.s>=0 && tail.s<N);
                grid[tail.f][tail.s] = true;
            }

        }
    }
    int ans = 0;
    FOR(i,N) FOR(j,N) ans+=grid[i][j];
    cout<<ans<<endl;
    file.close();
}

void part2(){
    ifstream file;
    file.open("in");
    const int N = 5000;
    vector<vector<bool>> grid(N,vector<bool>(N,false));
    pii head = {N/2,N/2};
    vector<pii> tail = vector<pii>(9,make_pair(N/2,N/2));
    grid[N/2][N/2] = true;
    char d;
    int times;
    while(file>>d>>times){
        if(d=='R'){
            FOR(k,times){
               head.s++; 
               updateTail(head,tail[0]);
               for(int i=1;i<9;i++) updateTail(tail[i-1],tail[i]);
               grid[tail[8].f][tail[8].s] = true;
            }
        }
        else if(d=='L'){
            FOR(k,times){
                head.s--;
                updateTail(head,tail[0]);
                for(int i=1;i<9;i++) updateTail(tail[i-1],tail[i]);
                grid[tail[8].f][tail[8].s] = true;
            }
        }
        else if(d=='D'){
            FOR(k,times){
                head.f++;
                updateTail(head,tail[0]);
                for(int i=1;i<9;i++) updateTail(tail[i-1],tail[i]);
                grid[tail[8].f][tail[8].s] = true;
            }
        }
        else if(d=='U'){
            FOR(k,times){
                head.f--;
                updateTail(head,tail[0]);
                for(int i=1;i<9;i++) updateTail(tail[i-1],tail[i]);
                grid[tail[8].f][tail[8].s] = true;
            }

        }
    }
    int ans = 0;
    FOR(i,N) FOR(j,N) ans+=grid[i][j];
    cout<<ans<<endl;
    file.close();
}

int main()
{
    //part1();
    part2();
    return 0;
}
