#include<bits/stdc++.h>
using namespace std;

//虚拟源节点
struct edge{
    int v;
    int w;
};
vector<vector<edge>>edges;
int ans = 0;
vector<int>vis;

void dfs(int u, int sum) {
    ans = max(ans, sum);
    for(auto [v, w] : edges[u]) {
        if(!vis[v]) {
            vis[v] = true;
            dfs(v, sum+w);
            vis[v] = false;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    edges.resize(n+1);
    //添加虚拟源节点0
    for(int i = 1;i <= n;i++) {
        edges[0].push_back({i, 0});
    }
    for(int i = 0;i < m;i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges[u].push_back({v, w});
        edges[v].push_back({u, w});
    }
    vis.resize(n+1, 0);
    dfs(0, 0);
    cout << ans;
    return 0;
}