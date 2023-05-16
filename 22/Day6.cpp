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
    string in;
    file>>in;
    int n = in.size();
    for(int i=0;i<n;i++){
        set<char> ss;
        for(int j=i;j<i+4;j++){
            ss.insert(in[j]);
        }
        if(ss.size()==4){
            cout<<i+4<<endl;
            break;
        }
    }
    file.close();
}

void part2(){
    ifstream file;
    file.open("in");
    string in;
    file>>in;
    int n = in.size();
    for(int i=0;i<n;i++){
        set<char> ss;
        for(int j=i;j<i+14;j++){
            ss.insert(in[j]);
        }
        if(ss.size()==14){
            cout<<i+14<<endl;
            break;
        }
    }
    file.close();
}

int main()
{
    part1();
    //part2();
    return 0;
}
