#include<bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;
struct node {
    int u;
    int d;
    bool operator<(const node& other) const {
        return d > other.d;
    }
};
vector<vector<int>>edges;
vector<int>dist;
vector<int>vis;

void dijkstra(int u) {
    dist[u] = 1;
    priority_queue<node>q;
    q.push({u, dist[u]});
    while(!q.empty()) {
        auto [u, d] = q.top();
        q.pop();
        if(vis[u]) continue;
        vis[u] = true;
        for(auto v : edges[u]) {
            if(dist[u] + 1 < dist[v]) {
                dist[v] = dist[u] + 1;
                q.push({v, dist[v]});
            }
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    edges.resize(k+1);
    dist.resize(k+1, INF), vis.resize(k+1, 0);
    for(int i = 0;i < n;i++) {
        int a, b;
        cin >> a >> b;
        edges[a].push_back(b);
    }
    dijkstra(1);
    if(dist[k] == INF) {
        cout << -1;
    } else {
        cout << dist[k];
    }
    return 0;
}