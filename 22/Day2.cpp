#include <iostream> 
#include <fstream>
#include <set>
using namespace std;
#define ll long long 

void part1(){
    ifstream file;
    file.open("in");
    string t, y;
    ll tot = 0;
    while(file>>t>>y){
        if(y=="Y") y = "B";
        if(y=="Z") y = "C";
        if(y=="X") y = "A";
        if(t==y) tot+=3;
        else if(y=="A" && t=="C") tot+=6;
        else if(y=="B" && t=="A") tot+=6;
        else if(y=="C" && t=="B") tot+=6;
        if(y=="A") tot+=1;
        else if(y=="B") tot+=2;
        else tot+=3;
    }
    cout<<tot<<endl;
    file.close();
}

void part2(){
    ifstream file;
    file.open("in");
    string t, y;
    ll tot = 0;
    while(file>>t>>y){
        if(y=="Y"){
            tot+=3;
            if(t=="A") tot+=1;
            if(t=="B") tot+=2;
            if(t=="C") tot+=3;
        }
        if(y=="Z"){
            tot+=6;
            if(t=="A") tot+=2;
            if(t=="B") tot+=3;
            if(t=="C") tot+=1;
        }
        if(y=="X"){
            if(t=="A") tot+=3;
            if(t=="B") tot+=1;
            if(t=="C") tot+=2;
        }
    }
    cout<<tot<<endl;
    file.close();
}

int main()
{
    //part1();
    part2();
    return 0;
}
