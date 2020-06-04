#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include <cassert>
#include<numeric>
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
    os << "(";
    os << P.first;
    os << ", ";
    os << P.second;
    os << ")";
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





//fixed<<setprecision(10)<<ans<<endl;
int64 big_weight_knapsack(vector<int64>& val,vector<int64>& weight, vector<int>& menu,int64 W){
    int N = val.size();
    int64 const MAX_V = accumulate(val.begin(), val.end(), 0LL);
    debug(MAX_V);
    int64 const INF = 1LL<<61;
    vector<vector<int64>> dp(N+1,vector<int64>(MAX_V+1,INF));//価値vを達成するのに最小重さ
    vector<vector<pair<int,int>>> pre(N+1,vector<pair<int,int>>(MAX_V+1,make_pair(-2,-2)));
    dp[0][0] = 0;
    REP(i,N){
        dp[i+1] = dp[i];
        for(int64 v=MAX_V;v>=0;v--){
            if (v>val[i]){
                if(chmin(dp[i+1][v],dp[i][v-val[i]]+weight[i])) pre[i+1][v] = make_pair(i,v-val[i]);
                else pre[i+1][v] = make_pair(i,v);
            }
            else if(chmin(dp[i+1][v],weight[i])){
                pre[i+1][v] = make_pair(-1,-1);
            }else pre[i+1][v] = make_pair(i, v);
        }
    }

    int result=0;
    REP(i,MAX_V+1){
        if(dp[N][i]<=W)
            result=i;
        else break;
    }   

    pair<int,int> now = make_pair(N, result);
    while(now.first > 0){
        if(pre[now.first][now.second].second != now.second) menu.emplace_back(now.first-1);
        now = pre[now.first][now.second];
    }
    return result;
}
void DPL_1_F(){
    int N,W;
    cin >> N >> W;
    vector<int64> val(N),weight(N);
    REP(i,N){
        cin >> val[i] >> weight[i];
    }
    vector<int> menu;
    cout << big_weight_knapsack(val,weight,menu,W) << endl;
}

void change_data(vector<int64>& price, vector<int64>& colorie){
    for(auto& p:price){
        p *= 1'000'000'000;
    }
    for(auto& c:colorie){
        // c /= 
    }
}
void solve(){
    vector<string> name;
    vector<int64> price,colorie,salty;
    input_data("menu_sai_20190630.csv",name,price,colorie,salty);
    change_data(price,colorie);
    size_t N = name.size();
    const int64 W = (int64)(1000) * 1'000'000'000;

    vector<int> menu;
    int64 ans_colorie = big_weight_knapsack(colorie, price, menu, W);
    cout << ans_colorie << endl;
    cout << "__採用メニュー__価格__カロリー___" << endl;
    for(auto a:menu) cout << name[a] << " " << make_pair(price[a], colorie[a]) << endl;

}
int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    
    // DPL_1_F();
    solve();

    return 0;
}