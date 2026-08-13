#include<bits/stdc++.h>
using namespace std;

vector<int>a;
vector<vector<int>>edges;
vector<int>dp;//dp[i]表示点燃i最多可以燃烧i个节点

int dfs(int u, int fa) {
    if(dp[u]) return dp[u];
    for(auto v : edges[u]) {
        if(v == fa) continue;
        if(a[v] < a[u]) {
            dfs(v, u);
            dp[u] += dp[v];
        }
    }
    //既是对于叶子节点的初始化
    //也是对于u加上本身更新
    dp[u] += 1;
    return dp[u];
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    a.resize(n+1);
    edges.resize(n+1);
    dp.resize(n+1, 0);
    for(int i = 1;i <= n;i++) cin >> a[i];
    for(int i = 0;i < n-1;i++) {
        int u, v;
        cin >> u >> v;
        edges[u].push_back(v);
        edges[v].push_back(u);
    }
    int ans = 0;
    for(int i = 1;i <= n;i++) {
        ans = max(ans, dfs(i, 0));
    }
    cout << ans;
    return 0;
}