#include<bits/stdc++.h>
using namespace std;

vector<int>color;
vector<vector<int>>edges;
//以i为中间节点的状态完全可以不用存储
//因为其只在更新ans的时候有用而对于更新fa节点的状态的时候并无作用
//只有以i为端点的状态才是对于fa节点状态更新是有用的
//这也是树形DP里很重要的一种判断
//一个状态需不需要存下来，关键看它以后还能不能参与更高层的状态转移。
// vector<vector<int>>dp1; //dp1[i][k]表示以i为中间节点的路径中经过k个黑色节点经过的最多节点个数
vector<vector<int>>dp; //dp2[i][k]表示以i为端点的路径中经过k个黑色节点经过的最多节点数
int n, k;
int ans = 0;
void dfs(int u, int fa) {
    int c = color[u];
    dp[u][c] = 1;
    for(auto v : edges[u]) {
        if(v == fa) continue;
        dfs(v, u);
        //计算u为中间节点的情况
        //左侧为dp[u][i]右侧为dp[v][j]
        //因为此时左侧dp[u][i]还没有用dp[v][j]更新
        //所以不会产生同一条路径重复使用的情况
        for(int i = 0;i <= k;i++) {
            for(int j = 0;i+j <= k;j++) {
                ans = max(ans, dp[u][i] + dp[v][j]);
            }
        }
        //更新以u为端点的情况
        for(int i = c;i <= k;i++) {
            //i-c表示的是从v下去的这条链中的黑色节点数量
            //u->v->...这条路径的长度就是1+dp[v][i-c]
            dp[u][i] = max(dp[u][i], 1+dp[v][i-c]);
            ans = max(ans, dp[u][i]);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> k;
    color.resize(n+1);
    edges.resize(n+1);
    dp.resize(n+1, vector<int>(k+1, 0));
    for(int i = 1;i <= n;i++) cin >> color[i];
    for(int i = 1;i < n;i++) {
        int u, v;
        cin >> u >> v;
        edges[u].push_back(v);
        edges[v].push_back(u);
    }
    dfs(1, 0);
    cout << ans;
    return 0;
}