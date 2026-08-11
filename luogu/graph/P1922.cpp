#include<bits/stdc++.h>
using namespace std;

vector<vector<int>>edges;
vector<int>dp;//dp[i]表示以i为根节点的子树中最多能放多少女仆咖啡厅
vector<int>sz;//以i为根节点的子树中有多少个可用节点

void dfs(int u, int fa) {
    sz[u] = 1;
    for(auto v : edges[u]) {
        if(v == fa) continue;
        dfs(v, u);
        //对于叶子节点，可用节点加一
        if(dp[v] == 0) sz[u] += 1;
        //对于非叶子节点加上对应的dp值
        dp[u] += dp[v];
    }
    //遍历完子节点之后，对于所有的叶子节点以及根节点自己进行添加咖啡厅
    dp[u] += sz[u]/2;
    //如果dp[u]!=0说明该节点不是叶子节点，以上分配已经完成了，它的根节点不能在对其进行改动
    //所以设置可用节点为0
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