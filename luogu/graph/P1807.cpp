#include<bits/stdc++.h>
using namespace std;


// struct edge{
//     int v;
//     int w;
// };
// struct node {
//     int u;
//     int d;
// };

// vector<vector<edge>>edges;
// vector<int>dist;

// void bfs() {
//     queue<node>q;
//     q.push({1, 0});
//     while(!q.empty()) {
//         auto [u, d] = q.front();
//         q.pop();
//         for(auto [v, w] : edges[u]) {
//             if(d + w > dist[v]) {
//                 dist[v] = d + w;
//                 q.push({v, dist[v]});
//             }
//         }
//     }
// }
// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     int n, m;
//     cin >> n >> m;
//     edges.resize(n+1);
//     //因为边权有负值，所以初始化dist为INT_MIN表示不可达
//     dist.resize(n+1, INT_MIN);
//     for(int i = 0;i < m;i++) {
//         int u, v, w;
//         cin >> u >> v >> w;
//         edges[u].push_back({v, w});
//     }
//     bfs();
//     if(dist[n] == INT_MIN) {
//         cout << -1;
//     } else {
//         cout << dist[n];
//     }
//     return 0;
// }

//因为是有向无环图所以可以用拓扑排序来做
#include<bits/stdc++.h>
using namespace std;

struct edge{
    int v;
    int w;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<edge>>edges(n+1);
    vector<int>indeg(n+1);
    for(int i = 0;i < m;i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges[u].push_back({v, w});
        indeg[v]++;
    }
    //拓扑排序保证了更新一个节点的时候其前置节点都已经更完了
    queue<int>q;
    vector<int>topo;
    for(int i = 1;i <= n;i++) {
        if(!indeg[i]) q.push(i);
    }
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        topo.push_back(u);
        for(auto [v, w] : edges[u]) {
            if(indeg[v]) {
                indeg[v]--;
                if(!indeg[v]) {
                    q.push(v);
                }
            }
        }
    }
    vector<int>dist(n+1, INT_MIN);
    dist[1] = 0;
    for(auto u : topo) {
        if(dist[u] == INT_MIN) continue;
        for(auto [v, w] : edges[u]) {
            dist[v] = max(dist[v], dist[u] + w);
        }
    }
    if(dist[n] == INT_MIN) {
        cout << -1;
    } else {
        cout << dist[n];
    }
    return 0;
}