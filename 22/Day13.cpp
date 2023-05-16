#include <vector>
#include <iostream> 
#include <fstream>
#include <set>
#define FOR(i,n) for(int i=0;i<n;i++)
#define sz size
#define pb push_back
using namespace std;
#define pii pair<int,int>
#define ll long long 
#define f first 
#define s second
#define vi vector<int>
struct mixedList{
    bool isNumb=false;
    bool isDivider=false;
    int val = -1;
    vector<mixedList*> elements;
    mixedList(){}
    mixedList(int v){
        mixedList* el = new mixedList();
        el->isNumb = true; el->val = v;
        add(el);
    }
    void add(mixedList* v){
        elements.pb(v);
    }
    void print(){
        if(isNumb) return;
        for(auto x: elements) x->print();
    }
};
int compare(mixedList* left, mixedList* right){
    //checks if left<right -1 
    //left>right 1
    //left==right 0
    int l = sz(left->elements);
    int r = sz(right->elements);
    int comp = 0;
    for(int i=0;i<min(l,r);i++){
        if(left->elements[i]->isNumb && right->elements[i]->isNumb){
            if(left->elements[i]->val<right->elements[i]->val) return -1;
            else if(left->elements[i]->val>right->elements[i]->val) return 1;
        }
        else if(!left->elements[i]->isNumb && !right->elements[i]->isNumb){
            int v = compare(left->elements[i],right->elements[i]);
            if(v!=0) return v; 
        }
        else if(left->elements[i]->isNumb){
            mixedList* new_el = new mixedList(left->elements[i]->val);
            int v = compare(new_el,right->elements[i]);
            if(v!=0) return v;
        }
        else{
            mixedList* new_el = new mixedList(right->elements[i]->val);
            int v = compare(left->elements[i],new_el);
            if(v!=0) return v;
        }
    }
    //everything has been the same check size
    if(l<r) comp = -1;
    else if(l>r) comp = 1;
    return comp;
}
vi list;
stack<int> ss;
mixedList* convert(string in, int& idx){
    if(idx==sz(list)) return NULL;
    //if(list[idx]-list[idx-1]-1)
    //cout<<"el: "<<in.substr(list[idx-1]+1,list[idx]-list[idx-1]+1-2)<<endl;
    mixedList* root = new mixedList();
    int left = -1;
    for(;idx<sz(list);){
        //cout<<"idx:"<<idx<<endl;
        if(in[list[idx]]=='['){
            ss.push(list[idx]);
            idx++;
            mixedList* el = convert(in,idx);
            root->add(el);
        }
        else if(in[list[idx]]==']'){
            if(list[idx]-list[idx-1]-1){
                string el = in.substr(list[idx-1]+1,list[idx]-list[idx-1]+1-2);
                mixedList* val = new mixedList();
                val->isNumb = true;
                val->val = stoi(el);
                root->add(val);
            }
            int l = ss.top(); ss.pop();
            //cout<<l<<" "<<list[idx]<<endl;
            idx++;
            return root;
        }
        else if(in[list[idx]]==','){
            if(list[idx]-list[idx-1]-1){
                string el = in.substr(list[idx-1]+1,list[idx]-list[idx-1]+1-2);
                mixedList* val = new mixedList();
                val->isNumb = true;
                val->val = stoi(el);
                root->add(val);
            }
            idx++;
        }
        else cout<<"BAD"<<endl;
    }
    return root;
}
mixedList* process(string in){
    list.clear();
    assert(ss.empty());
    FOR(i,sz(in)){
        if(!isdigit(in[i])) 
            list.pb(i);
    }
    int idx = 0;
    mixedList* root = convert(in,idx);
    return root;
}

void part1(){
    ifstream file;
    file.open("in");
    string A,B;
    int ans = 0;
    int idx = 1;
    string C;
    vector<mixedList*> all;
    while(getline(file,A)){
        getline(file,B); 
        mixedList* leftList = process(A);
        mixedList* rightList = process(B);
        all.pb(leftList);
        all.pb(rightList);
        /*
        if(compare(leftList,rightList)!=1){
            cout<<idx<<endl;
            ans+=idx;
        }
        */
        idx++;
        //skips empty line
        getline(file,C);

    }
    mixedList* L = process("[[2]]");
    L->isDivider = true;
    mixedList* R = process("[[6]]");
    R->isDivider = true;
    all.pb(L); all.pb(R);
    sort(all.begin(),all.end(),[](mixedList* a, mixedList* b){
        return compare(a,b)==-1;
    });
    vi indx;
    FOR(i,sz(all)){
        if(all[i]->isDivider) indx.pb(i+1);
    }
    cout<<indx[0]<<" "<<indx[1]<<endl;
    cout<<indx[0]*indx[1]<<endl;

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
