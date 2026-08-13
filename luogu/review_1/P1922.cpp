#include<bits/stdc++.h>
using namespace std;

vector<vector<int>>edges;
vector<int>dp;
vector<int>sz;//sz[i]表示以i为根节点的子树中可用的空白节点
void dfs(int u, int fa) {
    sz[u] = 1;
    for(auto v : edges[u]) {
        if(v == fa) continue;
        dfs(v, u);
        //对于叶子节点,可用节点数加一
        if(dp[v] == 0) sz[u] += sz[v];
        //用u节点的子节点v(非叶子节点)构成的子树的dp值更新dp[u]
        dp[u] += dp[v];
    }
    //加上节点u子树中可用的叶子节点
    dp[u] += sz[u] / 2;
    //如果dp[u]!=0即表示以u为根节点的子树已经分配好了
    //此时u的祖先节点不能再对该子树中的节点进行修改,可用节点数修改为0
    if(dp[u] != 0) sz[u] = 0;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    edges.resize(n+1);
    dp.resize(n+1, 0);
    sz.resize(n+1, 0);
    for(int i = 0;i < n-1;i++) {
        int u, v;
        cin >> u >> v;
        edges[u].push_back(v);
        edges[v].push_back(u);
    }
    dfs(1, 0);
    cout << dp[1];
    return 0;
}