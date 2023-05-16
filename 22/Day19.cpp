#include <bits/stdc++.h>
#define FOR(i,n) for(int i=0;i<n;i++)
#define sz size
#define pb push_back
#define all(x) begin(x), end(x)
using namespace std;
#define ll long long 
#define pii pair<int,int>
#define vi vector<int>

struct Ore{
    //0 for ore, clay, obsidian
    int type=10000;
    int quant=10000;
    Ore(){}
    Ore(int t, int q){
        type = t;
        quant = q;
    }
};
struct Robot{
    vector<Ore> ores;
    Robot(){}
    void add(Ore o){
        ores.pb(o);
    }
};
struct Blueprint{
    vector<Robot> rob;
    Blueprint(){}
    void add(Robot r){
        rob.pb(r);
    }
};

//int dp[24][16][16][18][20][20][20];
int n1 = 33,n2=18,n3=18,n4=18,n5=30,n6=30,n7=30;
int x1,x2,x3,x4,x5,x6;
vector<vector<vector<vector<vector<vector<vi>>>>>> dp;
vector<Robot> X;
int solve(int day, int ro, int rc, int rob, int o, int c, int ob){
    if(day==0) return 0;
    assert(ro>=0 && rc>=0 && rob>=0 && o>=0 && c>=0 && ob>=0);
    ro = min(ro,n2-1); rc = min(rc,n3-1); rob = min(rob,n4-1);
    o = min(o,n5-1); c = min(c,n6-1); ob = min(ob,n7-1);
    if(dp[day][ro][rc][rob][o][c][ob]>=0) return dp[day][ro][rc][rob][o][c][ob];
    int best = solve(day-1,ro,rc,rob,o+ro,c+rc,ob+rob);
    //try buying all possible pairing of (robot ores, robot clay, robot obsidian, robot geodoe)
    /*
    for(int i=0;i<=o/x1;i++){
        int mo = o-i*x1;
        for(int j=0;j<=mo/x2;j++){
            int mo2 = mo-j*x2;
            int mc = c;
            int max_obsidian = min(mo2/x3,mc/x4);
            for(int k=0;k<=max_obsidian;k++){
                int mo3 = mo2-k*x3;
                int mc3 = mc-k*x4;
                int mob = ob;
                int max_geode = min(mo3/x5,mob/x6);
                for(int l=0;l<=max_geode;l++){
                    int mo4 = mo3-l*x5;
                    int mob4 = mob-l*x6;
                    //cout<<i<<" "<<j<<" "<<k<<" "<<l<<endl;
                    assert(i*x1+j*x2+k*x3+x5*l+mo4==o);
                    assert(k*x4+mc3==c);
                    assert(l*x6+mob4==ob);
                    assert(mo4<=o && mc3<=c && mob4<=ob);
                    int v = solve(day-1,ro+i,rc+j,rob+k,mo4+ro,mc3+rc,mob4+rob)+l*(day-1);
                    if(v>best){
                        best = v;
                        //printf("(%d,%d,%d,%d,%d,%d,%d) -> action (%d,%d,%d,%d)\n",
                        //day,ro,rc,rob,o,c,ob,
                        //i,j,k,l
                        //);
                    }
                }
            }
        } 
    }
    */
    if(o>=x1) best = max(best,solve(day-1,ro+1,rc,rob,o+ro-x1,c+rc,ob+rob));
    if(o>=x2) best = max(best,solve(day-1,ro,rc+1,rob,o+ro-x2,c+rc,ob+rob));
    if(o>=x3 && c>=x4) best = max(best,solve(day-1,ro,rc,rob+1,o+ro-x3,c+rc-x4,ob+rob));
    if(o>=x5 && ob>=x6) best = max(best,solve(day-1,ro,rc,rob,o+ro-x5,c+rc,ob+rob-x6)+day-1);

    assert(day<n1&& ro<n2 && rc<n3 && rob<n4 && o<n5 && c<n6 && ob<n7);
    return dp[day][ro][rc][rob][o][c][ob] = best;
}

void part1(){
    ifstream file;
    file.open("in");
    string in;
    vector<Blueprint> A;
    while(getline(file,in)){
        stringstream ss(in);
        Robot clay; Robot obsidian;
        Robot ore;  Robot geode;
        string g,m;
        FOR(i,7) 
            ss>>g;
        ore.add(Ore(0,stoi(g)));
        FOR(i,6)
            ss>>g;
        clay.add(Ore(0,stoi(g)));
        FOR(i,6)
            ss>>g;
        ss>>m>>m>>m;
        obsidian.add(Ore(0,stoi(g)));
        obsidian.add(Ore(1,stoi(m)));
        FOR(i,6)
            ss>>g;
        ss>>m>>m>>m;
        geode.add(Ore(0,stoi(g)));
        geode.add(Ore(2,stoi(m)));
        Blueprint B;
        B.add(ore); B.add(clay); B.add(obsidian); B.add(geode);
        A.pb(B);
    }
    //int dp[24][16][16][18][20][20][20];
    cout<<(ll)n1*n2*n3*n4*n5*n6*n7<<endl;
    int tot = 1;
    int i = 1;
    for(Blueprint b: A){
        X = b.rob;
        dp.assign(n1,vector<vector<vector<vector<vector<vi>>>>>(n2, vector<vector<vector<vector<vi>>>>(n3,vector<vector<vector<vi>>>(n4, vector<vector<vi>>(n5,vector<vi>(n6,vi(n7,-1)))))));
        x1 = X[0].ores[0].quant;
        x2 = X[1].ores[0].quant;
        x3 = X[2].ores[0].quant; x4 = X[2].ores[1].quant;
        x5 = X[3].ores[0].quant; x6 = X[3].ores[1].quant;
        cout<<"Ore robot "<<x1<<" ores\n";
        cout<<"Clay robot "<<x2<<" ores\n";
        cout<<"Obsidian robot "<<x3<<" ores"<<" "<<x4<<" clay\n";
        cout<<"geode robot "<<x5<<" ores"<<" "<<x6<<" obsidian\n";
        double time_before_loop_begins = time(NULL);
        int ans = solve(32,1,0,0,0,0,0);
        int time_after_loop_ends = time(NULL);
        int time_diff = time_after_loop_ends - time_before_loop_begins;
        cout << "Time taken to run a for loop = " << time_diff << endl;
        tot = tot*ans;
        if(i==3) break;
        i++;
        cout<<ans<<endl;
    }
    cout<<tot<<endl;
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
