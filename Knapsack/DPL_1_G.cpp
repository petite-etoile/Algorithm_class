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
using namespace std;
#define int long long
typedef long long ll;
const int MOD = (int)1e9 + 7;
const int INF = 1LL << 60;
template<class T>bool chmax(T &a, const T &b) { if (a<b) { a=b; return 1; } return 0; }
template<class T>bool chmin(T &a, const T &b) { if (b<a) { a=b; return 1; } return 0; }
#define REP(i, n) for (int i = 0; i < (n); i++)
#define FOR(i,s,n) for (int i = s; i < (n); i++)
#define ALL(obj) (obj).begin(), (obj).end() //コンテナじゃないと使えない!!
#define debug(x) cerr << #x << ": " << x << "\n";
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
ostream& operator<<(ostream& os, pair<T,T> &P){
os << P.first;
os << " ";
os << P.second;
os << "\n";
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
//fixed<<setprecision(10)<<ans<<endl;


int binary_knapsack(vector<int>& val,vector<int>& weight, int W){
    int N = val.size();
    vector<vector<int>> dp(N+1,vector<int>(W+1,0));
    REP(i,N){
        REP(w,W+1){
            if(w>=weight[i])
                dp[i+1][w] = dp[i][w-weight[i]]+val[i];
            chmax(dp[i+1][w], dp[i][w]);
        }
    }
    return dp[N][W];
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
signed main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    int N,W;
    cin >> N >> W;
    vector<int> val(N),weight(N),cnt(N);
    REP(i,N){
        cin >> val[i] >> weight[i] >> cnt[i];
    }
    int ans = nlimited_knapsack(val,weight,cnt,W);    
    cout << ans << endl;
}

