#include <bits/stdc++.h>
#include <vector>
#include <iostream> 
#include <fstream>
#include <set>
#define FOR(i,n) for(int i=0;i<n;i++)
#define sz size
#define pb push_back
#define pii pair<int,int>
using namespace std;
#define f first
#define s second
#define ll long long 

pii cords(string start){
    int p = start.find(',');
    int x = stoi(start.substr(0,p));
    int y = stoi(start.substr(p+1,sz(start)-p));
    return make_pair(x,y);
}

void part1(){
    ifstream file;
    file.open("in");
    string in;
    vector<vector<bool>> grid(1000,vector<bool>(1000,false));
    int floor = 0;
    while(getline(file,in)){
        cout<<in<<endl;
        stringstream ss(in);
        pii pos;
        string start; ss>>start;
        pos = cords(start);
        string next;
        while(ss>>start){
            ss>>start;
            pii next = cords(start);
            while(pos!=next){
                grid[pos.f][pos.s] = true;
                floor = max(floor,pos.s);
                pos.f = pos.f+(next.f-pos.f)/abs(next.f-pos.f);
                pos.s = pos.s+(next.s-pos.s)/abs(next.s-pos.s);
            }
            floor = max(floor,pos.s);
            grid[pos.f][pos.s] = true;
        }
    }
    floor+=1;
    int ans = 0;
    while(true){
        pii pos = make_pair(500,0);
        bool bad = false;
        while(true){
            if(pos.s==floor) break;
            if(!grid[pos.f][pos.s+1]){
                pos.s++;
            }
            else if(!grid[pos.f-1][pos.s+1]){
                pos.s++;
                pos.f-=1;
            }
            else if(!grid[pos.f+1][pos.s+1]){
                pos.s++;
                pos.f++;
            }
            else break;
        }
        grid[pos.f][pos.s] = true;
        ans++;
        if(pos==make_pair(500,0)) break;
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
