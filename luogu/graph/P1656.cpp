#include<bits/stdc++.h>
using namespace std;

struct edge{
    int to;
    int id;
};
vector<vector<edge>>edges;
vector<int>dfn, low, is_bridge;
vector<pair<int, int>>bian;
int tot = 0;

void tarjan(int u, int fa_edgeid) {
    dfn[u] = low[u] = ++tot;
    for(auto [v, id] : edges[u]) {
        if(id == fa_edgeid) continue;
        if(!dfn[v]) {
            tarjan(v, id);
            low[u] = min(low[u], low[v]);
            if(low[v] > dfn[u]) {
                is_bridge[id] = true;
            }
        } else {
            low[u] = min(low[u], dfn[v]);
        }
    }
}

// bool comp(const pair<int, int>& a, const pair<int, int>& b) {
//     if(a.first != b.first) return a.first < b.first;
//     return a.second < b.second;
// }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    edges.resize(n+1), dfn.resize(n+1), low.resize(n+1);
    is_bridge.resize(m+1), bian.resize(m+1);
    for(int i = 1;i <= m;i++) {
        int a, b;
        cin >> a >> b;
        edges[a].push_back({b, i});
        edges[b].push_back({a, i});
        //这里也要排一下序，下面的sort不会排pair里面的序
        bian[i] = {min(a, b), max(a, b)};
    }
    for(int i = 1;i <= n;i++) {
        if(!dfn[i]) tarjan(i, 0);
    }
    vector<pair<int, int>>result;
    for(int i = 1;i <= m;i++) {
        if(is_bridge[i]) result.emplace_back(bian[i]);
    }
    sort(result.begin(), result.end());
    for(auto[u, v] : result) cout << u << ' ' << v << '\n';
    return 0;
}