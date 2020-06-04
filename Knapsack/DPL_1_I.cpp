/*
　　　∫ ∫ ∫
　　　ノヽ
　　（＿　 ）
　（＿　　　 ）
（＿＿＿＿＿＿ ）
　ヽ(´･ω･)ﾉ　
　　 |　 /
　　 UU
*/
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
using P = pair<ll, ll>;
typedef vector<int> vi;
const int MOD = (int)1e9 + 7;
const ll INF = 1LL << 62;
const int inf = 1<<30;
template<class T>bool chmax(T &a, const T &b) { if (a<b) { a=b; return 1; } return 0; }
template<class T>bool chmin(T &a, const T &b) { if (b<a) { a=b; return 1; } return 0; }
#define REP(i, n) for (int i = 0; i < (n); i++)
#define FOR(i,s,n) for (int i = s; i < (n); i++)
#define ALL(obj) (obj).begin(), (obj).end() //コンテナじゃないと使えない!!
#define debug(x) cerr << #x << ": " << x << "\n";
#define mp make_pair
template <typename T>
ostream& operator<<(ostream& os, vector<T> &V){
    int N = V.size();
    REP(i,N){
        os << V[i];
        if (i!=N-1) os << " ";
    }
    os << "\n";
    return os;
}
template <typename T>
ostream& operator<<(ostream& os, pair<T,T> const&P){
    os << P.first;
    os << " ";
    os << P.second;
    return os;
}
template <typename T>
ostream& operator<<(ostream& os, set<T> &S){
    auto it=S.begin();
    while(it!=S.end()){
        os << *it;
        os << " ";
        it++;
    }
    os << "\n";
    return os;
}
template <typename T>
ostream& operator<<(ostream& os, deque<T> &q){
    for(auto it=q.begin();it<q.end();it++){
        os<<*it;
        os<<" ";
    }
     os<<endl;
    return os;
}
vector<pair<int,int>> dxdy = {mp(0,1),mp(1,0),mp(-1,0),mp(0,-1)};
//fixed<<setprecision(10)<<ans<<endl;

vector<vector<ll>> binary_knapsack(vector<int>& val,vector<int>& weight, int W){
    int N = val.size();
    vector<vector<ll>> dp(N,vector<ll>(W+1,0));
    REP(w,W+1){
        if(weight[0]<=w) dp[0][w] = val[0];
    }
    REP(i,N-1){
        REP(w,W+1){
            if(w>=weight[i+1]){
                dp[i+1][w] = dp[i][w-weight[i+1]]+val[i+1];
            }
            chmax(dp[i+1][w], dp[i][w]);
        }
    }
    return dp;

ll big_weight_knapsack(vector<ll>& val,vector<ll>& weight, ll W){
    ll N = val.size();
    ll MAX=10001;
    // vector<vector<ll>> dp(N+1,vector<ll>(10001,INF));//価値vを達成するのに最小重さ
    vector<ll> dp(MAX+1,INF);//価値vを達成するのに最小重さ

    dp[0] = 0;
    REP(i,N){
        for(ll v=MAX;v>=0;v--){
            if (v>val[i])
                chmin(dp[v],dp[v-val[i]]+weight[i]);
            else
                chmin(dp[v],weight[i]);
        }
    }

    ll res=0;
    REP(i,MAX){
        if(dp[i]<=W)
            res=i;
        else break;
    }
    return res;
}

int nlimited_knapsack(vector<int>& val,vector<int>& weight, vector<int>& cnt, int W){
    vector<int> val_,weight_;
    int N = val.size();
    REP(i,N){
        int num = cnt[i];
        for(int k=1;num>0;k<<=1){
            chmin(k,num);
            val_.push_back(val[i]*k);
            weight_.push_back(weight[i]*k);
            num-=k;
        }
    }
    int res = binary_knapsack(val_,weight_,W);
    return res;
}

//https://onlinejudge.u-aizu.ac.jp/courses/library/7/DPL/1/DPL_1_I
int nlimited_knapsack2(vector<int>& val,vector<int>& weight, vector<int>& cnt, int W){
    vector<int> val_,weight_;
    int N = val.size();
    REP(i,N){
        int num = cnt[i];
        for(int k=1;num>0;k<<=1){
            chmin(k,num);
            val_.push_back(val[i]*k);
            weight_.push_back(weight[i]*k);
            num-=k;
        }
    }

    int res = binary_knapsack(val_,weight_,W);
    return res;
}

int main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    int N;
    cin >> N;

    int ans=0;



    cout << ans << endl;
}