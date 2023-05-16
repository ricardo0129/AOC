#include <vector>
#include <iostream> 
#include <fstream>
#include <set>
#define FOR(i,n) for(int i=0;i<n;i++)
#define sz size
#define pii pair<int,int>
#define f first
#define s second
#define pb push_back
using namespace std;
#define ll long long 

/*
    The input was formated in an annoying way 
    I just replaced "," & "-" with spaces
*/
void part1(){
    ifstream file;
    file.open("in");
    string a;
    vector<pii> A;
    while(file>>a){
        string b;
        file>>b;
        A.pb(make_pair(stoi(a),stoi(b)));
    }
    int ans = 0;
    for(int i=0;i<A.size();i+=2){
        bool valid = false;
        if(A[i].f<=A[i+1].f && A[i+1].s<=A[i].s) valid = true;
        if(A[i+1].f<=A[i].f && A[i].s<=A[i+1].s) valid = true;
        ans+=valid;
    }
    cout<<ans<<endl;
    file.close();
}

void part2(){
    ifstream file;
    file.open("in");
    string a;
    vector<pii> A;
    while(file>>a){
        string b;
        file>>b;
        A.pb(make_pair(stoi(a),stoi(b)));
    }
    int ans = 0;
    for(int i=0;i<A.size();i+=2){
        if(A[i].s<A[i+1].f || A[i+1].s<A[i].f) ans+=0;
        else ans+=1;
    }
    cout<<ans<<endl;
    file.close();
}

int main()
{
    //part1();
    part2();
    return 0;
}
