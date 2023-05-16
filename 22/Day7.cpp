#include <bits/stdc++.h>
#include <vector>
#include <iostream> 
#include <fstream>
#include <set>
#define FOR(i,n) for(int i=0;i<n;i++)
#define sz size
#define pb push_back
using namespace std;
#define ll long long 

struct directory{
    string name;
    set<string> files;
    map<string,int> dir;
    directory* parent;
    vector<directory*> c;
    ll S;
    directory(){
        S = 0;
        parent = NULL;
    }
    void addFile(string f, int v){
        directory* start = this;
        int times =0 ;
        while(start!=NULL){
            f = start->name+"/"+f;
            if(start->files.find(f)==start->files.end()){
                start->files.insert(f);
                start->S+=v;
            }
            assert(start!=start->parent);
            start = start->parent;
        }
    }
    void addDir(directory* D){
        if(dir.count(D->name)<=0){
            dir[D->name] = dir.size();
            S+=D->S;
            c.push_back(D);
        }
    }
    bool checkdir(string dname){
        return dir.count(dname)>0;
    }
    directory* find(string dname){
        directory* found = NULL;
        if(dir.count(dname)>0) found = c[dir[dname]];
        return found;
    }
};

void part1(){
    ifstream file;
    file.open("in");
    string in;
    vector<string> lines;
    while(getline(file,in)){
        lines.pb(in);
    }
    int n = lines.size();
    string dir = "/";
    map<string,int> d;
    directory* top;
    directory* curr;

    for(int i=0;i<n;){
        if(lines[i][0]=='$'){
            if(lines[i][2]=='c'){
                //cd command
                if(lines[i][lines[i].size()-1]=='/'){
                    curr = new directory();
                    curr->name = "/";
                    top = curr;
                }
                else if(lines[i][5]=='.'){
                    curr = curr->parent;
                    assert(curr!=NULL);
                }
                else{
                    string name = lines[i].substr(5,lines[i].size()-5);
                    if(!curr->checkdir(name)){
                        directory* new_dir = new directory();
                        new_dir->name = name;
                        curr->addDir(new_dir);
                        new_dir->parent = curr;
                    }
                    curr = curr->find(name);

                }
                i++;
            }
            else if(lines[i][2]=='l'){
                int j = i+1;
                for(;j<n;j++){
                    if(lines[j][0]=='$') break;
                    stringstream ss(lines[j]);
                    string left,right;
                    ss>>left>>right;
                    if(left=="dir"){
                        if(!curr->checkdir(right)){
                            directory* new_dir = new directory();
                            new_dir->name = right;
                            curr->addDir(new_dir);
                            new_dir->parent = curr;
                        }
                        directory* cc = curr->find(right);
                        cc->parent = curr;
                    }
                    else{
                        ll fs = stoll(left);
                        curr->addFile(right,fs);
                    }
                }
                i = j;

            }
        }
    }

    queue<directory*> q; 
    q.push(top);
    ll ans = 0;
    while(!q.empty()){
        directory* curr = q.front(); q.pop();
        if(curr->S<=100000) ans+=curr->S;
        for(directory* v: curr->c){
            q.push(v);
        }
    }
    cout<<ans<<endl;
    file.close();
}

void part2(){
    ifstream file;
    file.open("in");
    string in;
    vector<string> lines;
    while(getline(file,in)){
        lines.pb(in);
    }
    int n = lines.size();
    string dir = "/";
    map<string,int> d;
    directory* top;
    directory* curr;

    for(int i=0;i<n;){
        if(lines[i][0]=='$'){
            if(lines[i][2]=='c'){
                //cd command
                if(lines[i][lines[i].size()-1]=='/'){
                    curr = new directory();
                    curr->name = "/";
                    top = curr;
                }
                else if(lines[i][5]=='.'){
                    curr = curr->parent;
                    assert(curr!=NULL);
                }
                else{
                    string name = lines[i].substr(5,lines[i].size()-5);
                    if(!curr->checkdir(name)){
                        directory* new_dir = new directory();
                        new_dir->name = name;
                        curr->addDir(new_dir);
                        new_dir->parent = curr;
                    }
                    curr = curr->find(name);

                }
                i++;
            }
            else if(lines[i][2]=='l'){
                int j = i+1;
                for(;j<n;j++){
                    if(lines[j][0]=='$') break;
                    stringstream ss(lines[j]);
                    string left,right;
                    ss>>left>>right;
                    if(left=="dir"){
                        if(!curr->checkdir(right)){
                            directory* new_dir = new directory();
                            new_dir->name = right;
                            curr->addDir(new_dir);
                            new_dir->parent = curr;
                        }
                        directory* cc = curr->find(right);
                        cc->parent = curr;
                    }
                    else{
                        ll fs = stoll(left);
                        curr->addFile(right,fs);
                    }
                }
                i = j;

            }
        }
    }

    queue<directory*> q; 
    q.push(top);
    ll unused = 70000000;
    unused-=top->S;
    ll hi = 1e16;
    while(!q.empty()){
        directory* curr = q.front(); q.pop();
        if(unused+curr->S>=30000000) hi = min(hi,curr->S);
        for(directory* v: curr->c){
            q.push(v);
        }
    }
    cout<<hi<<endl;
    file.close();
}

int main()
{
    //part1();
    part2();
    return 0;
}
