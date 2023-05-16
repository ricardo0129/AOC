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

pii left(pii a){
    return make_pair(-a.s,a.f);
}
pii right(pii a){
    return make_pair(a.s,-a.f);
}
vector<pii> V = {{0,1},{0,-1},{1,0},{-1,0}};
void part1(){
    ifstream file;
    int times = 0;
    file.open("in");
    vector<string> A;
    string in;
    while(getline(file,in)){
        A.pb(in);
    }
    string moves = A.back();
    A.pop_back(); A.pop_back();
    int prev = 0;
    vector<pair<int,char>> M;
    FOR(i,sz(moves)){
        if(moves[i]=='R' || moves[i]=='L'){
            int x = stoi(moves.substr(prev,i-prev));
            M.pb(make_pair(x,moves[i]));
            prev = i+1;
        }
        if(i==sz(moves)-1){
            int x = stoi(moves.substr(prev,sz(moves)-prev));
            M.pb(make_pair(x,'E'));
        }
    }

    /*
    for(int xx=0;xx<sz(A);xx++){
    for(int yy=0;yy<sz(A[xx]);yy++){
        if(A[xx][yy]!='.') continue;
        for(pii dd: V){
            */
    int cols = 0;
    int rows = sz(A);
    FOR(i,sz(A)) cols = max(cols,(int)sz(A[i]));
    //FOR(i,sz(A)) A[i] = A[i]+string(cols-sz(A[i]),' ');
    //for each row store first & last column
    vi first_row(rows,-1), last_row(rows,-1);
    vi first_col(cols,-1), last_col(cols,-1);
    pii start={-1,-1};
    FOR(i,rows){
        FOR(j,sz(A[i])){
            if(A[i][j]=='.' || A[i][j]=='#'){
                if(start.f==-1) start = {i,j};
                if(first_row[i]==-1) first_row[i] = j;
                last_row[i] = j;
            }
        }
    }
    int k=0;
    FOR(i,cols){
        FOR(j,rows){
            if(sz(A[j])<=i) continue;
            if(A[j][i]=='.' || A[j][i]=='#'){
                if(first_col[i]==-1) first_col[i] = j;
                last_col[i] = j;
            }
        }
    }
    int D = last_row[0]-first_row[0]+1;
    D/=2;

    map<pii,int> mp;
    mp[make_pair(0,1)] = 0;  mp[make_pair(1,0)] = 1; 
    mp[make_pair(0,-1)] = 2;  mp[make_pair(-1,0)] = 3; 
    map<pii,char> mp2;
    mp2[make_pair(0,1)] = '>';  mp2[make_pair(1,0)] = 'v'; 
    mp2[make_pair(0,-1)] = '<';  mp2[make_pair(-1,0)] = '^'; 

    //start = {xx,yy};
    pii bb = start;
    //pii dir = make_pair(-1,0);
    pii dir = make_pair(0,1);
    //dir = dd;
    FOR(i,sz(M)){
        FOR(j,M[i].f){
            assert(A[start.f][start.s]!='#');
            A[start.f][start.s] = mp2[dir];
            pii prev = dir;
            pii next = make_pair(start.f+dir.f,start.s+dir.s);
            int x = start.f;
            int y = start.s;
            if(next.s>last_row[start.f]){
                //out of bounds moving right
                if(start.f<D){
                    //f1
                    //cout<<"F1\n";
                    dir = {0,-1};
                    next = {2*D+(D-1)-x,2*D-1};
                }
                else if(start.f<2*D){
                    //d1
                    //cout<<"D1\n";
                    dir = {-1,0};
                    next = {D-1,2*D+x-D};
                }
                else if(start.f<3*D){
                    //f2
                    //cout<<"F2\n";
                    dir = {0,-1};
                    next = {3*D-1-x,3*D-1};
                }
                else{
                    //a2
                    //cout<<"A2\n";
                    dir = {-1,0};
                    next = {3*D-1,D+x-3*D};
                }
            }
            else if(next.s<first_row[start.f]){
                //out of bounds moving left
                if(start.f<D){
                    //c1
                    //cout<<"C1\n";
                    dir = {0,1};
                    next = {2*D+D-1-x,0};
                }
                else if(start.f<2*D){
                    //b2
                    //cout<<"B2\n";
                    dir = {1,0};
                    next = {2*D,x-D};
                }
                else if(start.f<3*D){
                    //c2
                    //cout<<"C2\n";
                    dir = {0,1};
                    next = {3*D-1-x,D};
                }
                else{
                    //e2
                    //cout<<"E2\n";
                    dir = {1,0};
                    next = {0,D+x-3*D};
                }
            }
            else if(next.f>last_col[start.s]){
                //out of bounds moving down
                if(start.s<D){
                    //g1
                    //cout<<"G1\n";
                    dir = {1,0};
                    next = {0,2*D+y};
                }
                else if(start.s<2*D){
                    //a1
                    //cout<<"A1\n";
                    dir = {0,-1};
                    next = {3*D+y-D,D-1};
                }
                else{
                    //d2
                    //cout<<"D2\n";
                    dir = {0,-1};
                    next = {D+y-2*D,2*D-1};
                }
            }
            else if(next.f<first_col[start.s]){
                //out of bounds moving up 
                if(start.s<D){
                    //b1
                    //cout<<"B1\n";
                    dir = {0,1};
                    next = {D+y,D};
                }
                else if(start.s<2*D){
                    //e1
                    //cout<<"E1\n";
                    dir = {0,1};
                    next = {3*D+y-D,0};
                }
                else{
                    //g2
                    //cout<<"G2\n";
                    dir = {-1,0};
                    next = {4*D-1,y-2*D};
                }
            }
            //cout<<"pos:"<<start.f<<" "<<start.s<<endl;
            //cout<<"dir:"<<prev.f<<" "<<prev.s<<endl;
            //cout<<"next:"<<next.f<<" "<<next.s<<endl;
            assert(A[next.f][next.s]!=' ');
            if(A[next.f][next.s]==' '){
                //cout<<"T: "<<A[next.f][next.s]<<endl;
                //cout<<start.f<<" "<<start.s<<endl;
                //cout<<dir.f<<" "<<dir.s<<endl;
                assert(false);
            }
            if(A[next.f][next.s]!='#'){
                start = next;
            }
            else{
                dir = prev;
                break;
            }
        }
        if(M[i].s=='R') dir = right(dir);
        else if(M[i].s=='L') dir = left(dir);
        else assert(M[i].s=='E');
    }
    A[start.f][start.s] = mp2[dir];
    //assert(bb==start);
    //FOR(i,sz(A)) cout<<A[i]<<endl;
    cout<<start.f+1<<" "<<start.s+1<<" "<<endl;
    cout<<dir.f<<" "<<dir.s<<endl;
    int ans = 1000*(start.f+1)+4*(start.s+1)+mp[dir];
    cout<<ans<<endl;
    FOR(i,sz(A)){
        FOR(j,sz(A[i])){
            if(A[i][j]!=' ' && A[i][j]!='#') A[i][j]='.';
        }
    }
    times++;
    /*
    }}}
    */
    cout<<times<<endl;

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