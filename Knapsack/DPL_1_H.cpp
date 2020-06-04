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
typedef pair<ll,ll> P;
const int MOD = (int)1e9 + 7;
const int INF = 1LL << 60;
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
vector<pair<int,int>> get_half_sack(vector<int>& val, vector<int>& weight,int W){
    int N = val.size();
    int max_bit = 1<<N;
    vector<pair<int,int>> res;
    REP(bit_set,max_bit){
        int v=0,w=0;
        REP(i,N){
            if(bit_set&(1<<i)){
                v+=val[i];
                w+=weight[i];
            }
        }
        if(w<=W) res.push_back(mp(v,w));
    }
    return res;
}
int huge_knapsack(vector<int>& val1,vector<int>& val2, vector<int>& weight1, vector<int>& weight2,int W){
    vector<pair<int,int>> vw1=get_half_sack(val1,weight1,W); //前半
    vector<pair<int,int>> vw2=get_half_sack(val2,weight2,W); //後半
    int v,w,v2,w2;
    int res=0;
    
    sort(ALL(vw2),[&](pair<int,int> a,pair<int,int> b){
        return a.second<b.second;
    });//重さが大きい順に試していく
    sort(ALL(vw1),[&](pair<int,int> a,pair<int,int> b){
        return a.second>b.second;
    });//重さが大きい順に試していく)
    auto it = vw2.begin();
    int current_max_v=0; int current_weight=0;
    for(auto vw:vw1){
        tie(v,w) = vw;
        int remain = W-w;
        while(it!=vw2.end()){
            bool updated=false;
            tie(v2,w2)=*it;
            if(remain>=w2){
                chmax(current_max_v,v2);
                chmax(current_weight,w2);
                it++;
                updated=true;
            }
            chmax(res,current_max_v+v);
            if(!updated) break;
        }
    }
    return res;
}
//fixed<<setprecision(10)<<ans<<endl;
signed main(){
    cin.tie(0);
    ios::sync_with_stdio(false);
    int N,W;
    cin >> N >> W;
    vector<int> val1(N/2),weight1(N/2),val2((N+1)/2),weight2((N+1)/2);
    REP(i,N/2){
        cin >> val1[i] >> weight1[i];
    }
    REP(i,(N+1)/2){
        cin >> val2[i] >> weight2[i];
    }
    
    int ans = huge_knapsack(val1,val2,weight1,weight2,W);
    cout << ans << endl;
}