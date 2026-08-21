// #include<bits/stdc++.h>
// using namespace std;

// const int INF = 0x3f3f3f3f;
// const int maxsize = 20000*10005;
// struct edge {
//     string v;
//     double w;
// };

// struct node {
//     string u;
//     double d;
//     bool operator<(const node& other) const {
//         return d > other.d;
//     }
// };
// unordered_map<string, vector<edge>>edges;
// unordered_map<string, double>dist;
// unordered_map<string, int>vis;
// string getid(int x, int y) {
//     return to_string(x) + "#" + to_string(y);
// }

// void dijkstra(string s, string t) {
//     priority_queue<node>q;
//     dist[s] = 0;
//     q.push({s, dist[s]});
//     while(!q.empty()) {
//         auto [u, d] = q.top();
//         q.pop();
//         if(vis[u]) continue;
//         vis[u] = true;
//         if(vis[t]) break;
//         for(auto [v, w] : edges[u]) {
//             if(!dist.count(v) || dist[v] > d+w) {
//                 dist[v] = d+w;
//                 q.push({v, dist[v]});
//             }
//         }
//     }
// }
// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     //这道题由于n只有100所以可以使用unordered_map
//     //起始更好的方法是把点的序号当作u和v
//     int n;
//     cin >> n;
//     vector<pair<int, int>>position(n+1);
//     for(int i = 1;i <= n;i++) {
//         int x, y;
//         cin >> x >> y;
//         position[i] = {x, y};
//     }
//     int m;
//     cin >> m;
//     for(int i = 0;i < m;i++) {
//         int j, k;
//         cin >> j >> k;
//         auto [x1, y1] = position[j];
//         auto [x2, y2] = position[k];
//         string u = getid(x1, y1), v = getid(x2, y2);
//         double w = sqrt(pow(x1-x2, 2)+pow(y1-y2, 2));
//         edges[u].push_back({v, w});
//         edges[v].push_back({u, w});
//     }
//     int s, t;
//     cin >> s >> t;
//     string sid = getid(position[s].first, position[s].second);
//     string tid = getid(position[t].first, position[t].second);
//     dijkstra(sid, tid);
//     cout << fixed << setprecision(2) << dist[tid];
//     return 0;
// }


#include<bits/stdc++.h>
using namespace std;

const double INF = 0x3f3f3f3f;
struct edge{
    int v;
    double w;
    edge(int v1, double w1) : v(v1), w(w1) {}
};
struct node{
    int u;
    double d;
    bool operator<(const node& other) const {
        return d > other.d;
    }
};

vector<vector<edge>>edges;
vector<double>dist;
vector<int>vis;

void dijkstra(int s, int t) {
    priority_queue<node>q;
    dist[s] = 0;
    q.push({s, dist[s]});
    while(!q.empty()) {
        auto [u, d] = q.top();
        q.pop();
        if(vis[u]) continue;
        vis[u] = true;
        if(u == t) break;
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
    int n;
    cin >> n;
    edges.resize(n+1), dist.resize(n+1, INF);
    vis.resize(n+1);
    vector<pair<int, int>>position(n+1);
    for(int i = 1;i <= n;i++) {
        int x, y;
        cin >> x >> y;
        position[i] = {x, y};
    }
    int m;
    cin >> m;
    for(int i = 0;i < m;i++) {
        int u, v;
        cin >> u >> v;
        double dx = position[u].first-position[v].first;
        double dy = position[u].second-position[v].second;
        double w = sqrt(dx*dx + dy*dy);
        //双向边
        edges[u].emplace_back(v, w);
        edges[v].emplace_back(u, w);
    }
    int s, t;
    cin >> s >> t;
    dijkstra(s, t);
    cout << fixed << setprecision(2) << dist[t];
    return 0;
}