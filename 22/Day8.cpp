#include <vector>
#include <iostream> 
#include <fstream>
#include <set>
#define FOR(i,n) for(int i=0;i<n;i++)
#define sz size
#define pb push_back
using namespace std;
#define ll long long 

void part1(){
    ifstream file;
    file.open("in");
    vector<string> g;
    string in;
    while(file>>in)
        g.pb(in);
    int r = g.size(); int c = g[0].size();
    vector<vector<bool>> visible(r,vector<bool>(c,false));
    for(int i=0;i<r;i++){
        visible[i][0] = true;
        char maxi = g[i][0];
        for(int j=1;j<c-1;j++){
            if(g[i][j]>maxi) visible[i][j] = true;
            maxi = max(maxi,g[i][j]);
        }
        visible[i][c-1] = true;
        maxi = g[i][c-1];
        for(int j=c-2;j>0;j--){
            if(g[i][j]>maxi) visible[i][j] = true;
            maxi = max(maxi,g[i][j]);
        }
    }
    for(int i=0;i<c;i++){
        visible[0][i] = true;
        char maxi = g[0][i];
        for(int j=1;j<r-1;j++){
            if(g[j][i]>maxi) visible[j][i] = true;
            maxi = max(maxi,g[j][i]);
        }
        visible[r-1][i] = true;
        maxi = g[r-1][i];
        for(int j=c-2;j>0;j--){
            if(g[j][i]>maxi) visible[j][i] = true;
            maxi = max(maxi,g[j][i]);
        }
    }
    int ans = 0;
    FOR(i,r) FOR(j,c) ans+=visible[i][j];
    cout<<ans<<endl;


    file.close();
}

void part2(){
    ifstream file;
    file.open("in");
    vector<string> g;
    string in;
    while(file>>in)
        g.pb(in);
    int r = g.size(); int c = g[0].size();
    ll best = 0;
    for(int i=1;i<r-1;i++){
        for(int j=1;j<c-1;j++){
            //assume i,j is the viewing tree
            ll curr = 1;
            int seen = 0;
            for(int k=j+1;k<c;k++){
                seen++;
                if(g[i][j]<=g[i][k]) break;
            }
            curr*=seen;
            seen = 0;
            for(int k=j-1;k>=0;k--){
                seen++;
                if(g[i][j]<=g[i][k]) break;
            }
            curr*=seen;
            seen = 0;
            for(int k=i+1;k<r;k++){
                seen++;
                if(g[i][j]<=g[k][j]) break;
            }
            curr*=seen;
            seen = 0;
            for(int k=i-1;k>=0;k--){
                seen++;
                if(g[i][j]<=g[k][j]) break;
            }
            curr*=seen;
            best = max(best,curr);
        }
    }
    cout<<best<<endl;
    file.close();
}

int main()
{
    //part1();
    part2();
    return 0;
}
