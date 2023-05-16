#include <vector>
#include <bits/stdc++.h>
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
    string in;
    vector<vector<char> > rows;
    int r = 0;
    vector<char> A[100];
    while(getline(file,in)){
        if(in.empty()) 
            break;
        //1 5 
        //1+4x
        FOR(i,sz(in)){
            if(i%2==1 && (i-1)%4==0){
                if(isalpha(in[i])){
                    A[(i-1)/4].pb(in[i]);     
                }
                if(isdigit(in[i])){
                    r = in[i]-'0';
                }
            }
        }
    }
    stack<char> V[r];
    FOR(i,r){
        for(int j=sz(A[i])-1;j>=0;j--){
            V[i].push(A[i][j]);
        }
    }
    while(getline(file,in)){
        stringstream ss(in);
        string g;
        //move k from u to v
        int k,u,v;
        ss>>g>>k>>g>>u>>g>>v;
        u--;v--;
        FOR(i,k){
            V[v].push(V[u].top());
            V[u].pop();
        }
    }
    FOR(i,r){
        cout<<V[i].top(); 
    }
    cout<<endl;
    file.close();
}

void part2(){
    ifstream file;
    file.open("in");
    string in;
    vector<vector<char> > rows;
    int r = 0;
    vector<char> A[100];
    while(getline(file,in)){
        if(in.empty()) 
            break;
        //1 5 
        //1+4x
        FOR(i,sz(in)){
            if(i%2==1 && (i-1)%4==0){
                if(isalpha(in[i])){
                    A[(i-1)/4].pb(in[i]);     
                }
                if(isdigit(in[i])){
                    r = in[i]-'0';
                }
            }
        }
    }
    stack<char> V[r];
    FOR(i,r){
        for(int j=sz(A[i])-1;j>=0;j--){
            V[i].push(A[i][j]);
        }
    }
    while(getline(file,in)){
        stringstream ss(in);
        string g;
        //move k from u to v
        int k,u,v;
        ss>>g>>k>>g>>u>>g>>v;
        u--;v--;
        vector<char> R;
        FOR(i,k){
            R.pb(V[u].top());
            V[u].pop();
        }
        for(int i=sz(R)-1;i>=0;i--){
            V[v].push(R[i]);
        }
    }
    FOR(i,r){
        cout<<V[i].top(); 
    }
    cout<<endl;


    file.close();
}

int main()
{
    //part1();
    part2();
    return 0;
}
