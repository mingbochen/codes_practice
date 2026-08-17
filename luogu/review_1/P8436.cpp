#include<bits/stdc++.h>
using namespace std;

struct edge{
    int to;
    int id;
};
vector<vector<edge>>edges;
vector<int>dfn, low, is_bridge;
int tot = 0, edcc_cnt = 0;

//找桥
void tarjan(int u, int fa_edgeid) {
    dfn[u] = low[u] = ++tot;
    for(auto [v, id] : edges[u]) {
        if(id == fa_edgeid) continue;//跳过来的父边
        if(!dfn[v]) {
            tarjan(v, id);
            low[u] = min(low[u], low[v]);
            //注意这里是大于不是大于等于
            if(low[v] > dfn[u]) {
                is_bridge[id] = true;
            }
        } else {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

//找边双连通分量
vector<vector<int>>belong;
vector<int>vis;
void dfs(int u, int color) {
    belong[color].push_back(u);
    vis[u] = true; //防止重复遍历
    for(auto [v, id] : edges[u]) {
        if(is_bridge[id]) continue;//跳过桥边
        if(!vis[v]) dfs(v, color);
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    edges.resize(n+1), dfn.resize(n+1), low.resize(n+1);
    is_bridge.resize(m+1), belong.resize(n+1), vis.resize(n+1);
    for(int i = 1;i <= m;i++) {
        int u, v;
        cin >> u >> v;
        edges[u].push_back({v, i});
        edges[v].push_back({u, i});
    }
    for(int i = 1;i <= n;i++) {
        //由于边的编号是从1开始的，所以这里可以用0
        //如果变得编号是从0开始的，那就要从-1不能用0
        if(!dfn[i]) tarjan(i, 0);
    }
    int edcc_cnt = 0;
    for(int i = 1;i <= n;i++) {
        if(!vis[i]) dfs(i, edcc_cnt++);
    }
    cout << edcc_cnt << '\n';
    for(int i = 0;i < edcc_cnt;i++) {
        cout << belong[i].size();
        for(auto it : belong[i]) cout << ' '  << it;
        cout << '\n';
    }
    return 0;
}