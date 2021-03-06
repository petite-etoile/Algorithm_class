#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include <cassert>
using namespace std;
typedef long long int64;
template<class T>bool chmax(T &a, const T &b) { if (a<b) { a=b; return 1; } return 0; }
template<class T>bool chmin(T &a, const T &b) { if (b<a) { a=b; return 1; } return 0; }
#define REP(i, n) for (int i = 0; i < (n); i++)
#define ALL(obj) (obj).begin(), (obj).end() 
#define debug(x) cerr << #x << ": " << x << "\n";

template <typename T>
ostream& operator<<(ostream& os, const vector<T> &V){
    int N = V.size();
    REP(i,N){
        os << V[i];
        if (i!=N-1) os << " ";
    }
    os << "\n";
    return os;
}
template<typename T,typename S>
ostream& operator<<(ostream& os, const pair<T,S> &P){
    os << P.first;
    os << ", ";
    os << P.second;
    return os;
}
vector<string> split(string str){
    vector<string> res;
    string now = "";
    for(auto chr:str){
        if(chr==','){
            res.emplace_back(now);
            now="";
        }else now += chr; 
    }
    if(now.size()!=0) res.emplace_back(now);
    return move(res);
}
bool input_data(string file_name, vector<string>& name, vector<int64>& price, vector<int64>& calorie, vector<int64>& salty){
    ifstream ifs(file_name);
    string str;

    if (ifs.fail()) {
        cerr << "Failed to open file." << endl;
        return true;
    }
    while (getline(ifs, str)) {
        vector<string> res = split(str);
        try{
            salty.emplace_back(int(stod(res[3])*10));
            name.emplace_back(res[0]);
            calorie.emplace_back(stoi(res[1]));
            price.emplace_back(stoi(res[2]));
        }catch(...){}
    }
    return false;
}

int64 unlimited_knapsack(vector<int64>const& val,vector<int64>const& weight,vector<int>& menu, int const W){
    assert(val.size() == weight.size());
    int N = val.size();
    //DP
    vector<vector<int64>> dp(N+1,vector<int64>(W+1));
    vector<vector<pair<int,int>>> pre(N+1,vector<pair<int,int>>(W+1,make_pair(-1,-1)));
    REP(i,N){
        dp[i+1] = dp[i];
        REP(w,W+1){
            pre[i+1][w] = make_pair(i,w);
            if(w>=weight[i]){
                if(chmax(dp[i+1][w],dp[i+1][w-weight[i]]+val[i])){
                    pre[i+1][w] = make_pair(i+1,w-weight[i]);
                }
            }
        }
    }
    
    //復元
    pair<int,int64> now = make_pair(N,W);
    while(now.first>0){
        if(now.second != pre[now.first][now.second].second) menu.emplace_back(now.first-1);
        now = pre[now.first][now.second];
    }

    return dp[N][W];
}

void solve(){
    vector<string> name;
    vector<int64> price,colorie,salty;
    input_data("menu_sai_20190630.csv",name,price,colorie,salty);
    size_t N = name.size();
    const int W = 1000;

    vector<int> menu;
    int64 ans_colorie = unlimited_knapsack(colorie, price, menu, W);
    cout << ans_colorie << endl;
    cout << "__採用メニュー__価格__カロリー___" << endl;
    for(auto a:menu) cout << name[a] << " " << make_pair(price[a], colorie[a]) << endl;

}

void DPL_1_C(){
    int N,W;
    cin >> N >> W;
    vector<int64> val(N),weight(N);
    REP(i,N){
        cin >> val[i] >> weight[i];
    }
    vector<int> menu;
    cout << unlimited_knapsack(val,weight,menu,W) << endl;
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    
    // DPL_1_C();
    solve();

    return 0;
}
