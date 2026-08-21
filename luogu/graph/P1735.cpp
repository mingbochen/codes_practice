#include<bits/stdc++.h>
using namespace std;

int n;
const int INF = 0x3f3f3f3f;
//TLE,先尝试用数组优化,将二维坐标转化成一个整数id = x*(n+1)+y;
vector<vector<pair<int, int>>>edges;
vector<vector<char>>migong;
vector<int>dx1 = {-1, 1, 0, 0};
vector<int>dx2 = {-2, 2, 0, 0};
vector<int>dx3 = {-1, 1, -1, 1};
vector<int>dy1 = {0, 0, -1, 1};
vector<int>dy2 = {0, 0, -2, 2};
vector<int>dy3 = {-1, -1, 1, 1};
void add_edge(int i, int j, int u, int t) {
    if(migong[i][j] == '*') return;
    int v = i*(n+1)+j;
    if(t == 1 || t == 2) {
        edges[u].push_back({v, 1});
    } else if(t == 3) {
        edges[u].push_back({v, 2});
    }
}
vector<int>dist;
vector<int>vis;
struct node{
    int u;
    int d;
    bool operator<(const node& other) const {
        return d > other.d;
    }
};

void dijkstra() {
    int s1 = 1*(n+1)+1;
    int s2 = 1*(n+1)+n;
    int s3 = n*(n+1)+1;
    dist[s1] = 1;
    dist[s2] = 1;
    dist[s3] = 1;
    //多源dijkstra
    priority_queue<node>q;
    q.push({s1, dist[s1]});
    q.push({s2, dist[s2]});
    q.push({s3, dist[s3]});
    while(!q.empty()) {
        auto [u, d] = q.top();
        q.pop();
        if(vis[u]) continue;
        vis[u] = true;
        for(auto [v, w] : edges[u]) {
            if(dist[v] > d+w){
                dist[v] = d+w;
                q.push({v, dist[v]});
            }
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    dist.resize((n+1)*(n+1)+1, INF);
    vis.resize((n+1)*(n+1)+1);
    migong.resize(n+1, vector<char>(n+1));
    edges.resize((n+1)*(n+1)+1);
    for(int i = 1;i <= n;i++) {
        for(int j = 1;j <= n;j++) {
            cin >> migong[i][j];
        }
    }
    //添加边
    for(int i = 1;i <= n;i++) {
        for(int j = 1;j <= n;j++) {
            int u = i*(n+1) + j;
            if(migong[i][j] == 'A') {
                for(int k = 0;k < 4;k++) {
                    int ni = i+dx1[k], nj = j+dy1[k];
                    if(ni >= 1 && ni <= n && nj >= 1 && nj <= n) {
                        add_edge(ni, nj, u, 1);
                    }
                }
            } else if(migong[i][j] == 'B') {
                for(int k = 0;k < 4;k++) {
                    int ni = i+dx2[k], nj = j+dy2[k];
                    if(ni >= 1 && ni <= n && nj >= 1 && nj <= n) {
                        add_edge(ni, nj, u, 2);
                    }
                }
            } else if(migong[i][j] == 'C') {
                for(int k = 0;k < 4;k++) {
                    int ni = i+dx3[k], nj = j+dy3[k];
                    if(ni >= 1 && ni <= n && nj >= 1 && nj <= n) {
                        add_edge(ni, nj, u, 3);
                    }
                }
            }
        }
    }
    dijkstra();
    int e = n*(n+1)+n;
    if(dist[e] == INF) {
        cout << "No answer";
    } else {
        cout << dist[e];
    }
    return 0;
}