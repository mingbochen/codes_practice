#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int INF = 0x3f3f3f3f;
struct edge{
    int v;
    int w;
};
struct node{
    int v;
    ll dist;
    bool operator<(const node& other) const {
        return dist > other.dist;
    }
};

vector<vector<edge>>edges;
vector<vector<edge>>rev_edges;
vector<ll>dist;
vector<int>vis;

void dijikstra(int u, const vector<vector<edge>>& edges) {
    dist[u] = 0;
    priority_queue<node>q;
    q.push({u, dist[u]});
    while(!q.empty()) {
        auto [u, d] = q.top();
        q.pop();
        if(vis[u]) continue;
        vis[u] = true;
        for(auto [v, w] : edges[u]) {
            if(d + w < dist[v]) {
                dist[v] = d + w;
                q.push({v, dist[v]});
            }
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    edges.resize(n+1), rev_edges.resize(n+1);
    dist.resize(n+1, INF), vis.resize(n+1, false);
    for(int i = 0;i < m;i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges[u].push_back({v, w});
        rev_edges[v].push_back({u, w});
    }
    dijikstra(1, edges);
    ll ans = 0;
    for(int i = 1;i <= n;i++) ans += dist[i];
    dist.assign(n+1, INF);
    vis.assign(n+1, false);
    dijikstra(1, rev_edges);
    for(int i = 1;i <= n;i++) ans += dist[i];
    cout << ans;
    return 0;
}