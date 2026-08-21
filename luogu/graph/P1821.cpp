#include<bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;
struct edge{
    int v;
    int w;
};
struct node{
    int u;
    int d;
    bool operator<(const node& other) const {
        return d > other.d;
    }
};

vector<vector<edge>>edges;
vector<vector<edge>>rev_edges;
vector<int>dist;
vector<int>rev_dist;
vector<int>vis;
vector<int>rev_vis;

void dijkstra(int s, vector<int>& dist, const vector<vector<edge>>&edges, vector<int>& vis) {
    priority_queue<node>q;
    dist[s] = 0;
    q.push({s, dist[s]});
    while(!q.empty()){
        auto [u, d] = q.top();
        q.pop();
        if(vis[u]) continue;
        vis[u] = true;
        for(auto [v, w] : edges[u]) {
            if(dist[v] > d+w) {
                dist[v] = d+w;
                q.push({v, dist[v]});
            }
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m, x;
    cin >> n >> m >> x;
    edges.resize(n+1), rev_edges.resize(n+1);
    dist.resize(n+1, INF), rev_dist.resize(n+1, INF);
    vis.resize(n+1, 0), rev_vis.resize(n+1, 0);
    for(int i = 0;i < m;i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges[u].push_back({v, w});
        rev_edges[v].push_back({u, w});
    }
    dijkstra(x, dist, edges, vis);
    dijkstra(x, rev_dist, rev_edges, rev_vis);
    int ans = 0;
    for(int i = 1;i <= n;i++) {
        ans = max(ans, dist[i]+rev_dist[i]);
    }
    cout << ans;
    return 0;
}