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
    int ans = 0;
    while(file>>in){
        int n = in.size();
        set<char> all;
        FOR(i,n/2){
            all.insert(in[i]);
        }
        for(int i=n/2;i<n;i++){
            if(all.find(in[i])!=all.end()){
                char c = in[i];
                if(isupper(c)){
                    ans+=(c-'A')+27;
                }
                else ans+=(c-'a')+1;
                break;
            }
        }
    }
    cout<<ans<<endl;
    file.close();
}

void part2(){
    ifstream file;
    file.open("in");
    string in;
    int ans = 0;
    int i = 1;
    vector<string> A;
    while(file>>in){
        A.pb(in);
        if(i%3==0){
            for(char c ='a';c<='z';c++){
                int times = 0;
                FOR(i,3){
                    FOR(j,sz(A[i])){
                        if(A[i][j]==c){
                            times++;
                            break;
                        }
                    }
                }
                if(times>=3){
                    ans+=c-'a'+1;
                }
            }
            for(char c ='A';c<='Z';c++){
                int times = 0;
                FOR(i,3){
                    FOR(j,sz(A[i])){
                        if(A[i][j]==c){
                            times++;
                            break;
                        }
                    }
                }
                if(times>=3){
                    ans+=c-'A'+27;
                }
            }

            A.clear();
        }
        i++;
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
