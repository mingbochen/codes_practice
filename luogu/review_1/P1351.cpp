#include<bits/stdc++.h>
using namespace std;
using ll = long long;
vector<vector<int>>edges;
vector<ll>w;
const int MOD = 10007;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    edges.resize(n+1), w.resize(n+1);
    for(int i = 0;i < n-1;i++) {
        int u, v;
        cin >> u >> v;
        edges[u].push_back(v);
        edges[v].push_back(u);
    }
    for(int i = 1;i <= n;i++) cin >> w[i];
    ll sum = 0, ansm = 0;
    for(int i = 1;i <= n;i++) {
        int sz = edges[i].size();
        if(sz < 2) continue;
        ll lianhesum = 0, sq = 0;
        ll max1 = 0, max2 = 0;
        for(auto v : edges[i]) {
            lianhesum += w[v];
            sq += w[v] * w[v];
            sq %= MOD;
            if(w[v] > max1) {
                max2 = max1;
                max1 = w[v];
            } else if(w[v] > max2) {
                max2 = w[v];
            }
        }
        sum += (lianhesum * lianhesum - sq) % MOD;
        sum %= MOD;
        ansm = max(ansm, max1*max2);
    }
    cout << ansm << ' ' << sum;
    return 0;
}