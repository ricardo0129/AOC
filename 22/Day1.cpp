#include <iostream> 
#include <fstream>
#include <set>
using namespace std;
#define ll long long 

void part1(){
    ifstream file;
    file.open("in1");

    string line;
    ll curr = 0;
    ll ans = 0;
    while(getline(file,line)){
        if(line.empty()){
            ans = max(ans,curr);
            curr = 0;
        }
        else
            curr+=stoi(line);
    }
    ans = max(ans,curr);
    cout<<ans<<endl;

    file.close();
}

void part2(){
    ifstream file;
    file.open("in1");

    string line;
    ll curr = 0;
    multiset<ll> highest;
    ll ans = 0;
    while(getline(file,line)){
        if(line.empty()){
            highest.insert(curr);
            if(highest.size()>3) highest.erase(highest.begin());
            curr = 0;
        }
        else
            curr+=stoi(line);
    }
    highest.insert(curr);
    if(highest.size()>3) highest.erase(highest.begin());
    for(ll x: highest) ans+=x;
    cout<<ans<<endl;

    file.close();
}

int main()
{
    //part1();
    part2();
    return 0;
}
