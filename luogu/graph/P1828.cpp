// #include<bits/stdc++.h>
// using namespace std;

// const int INF = 0x3f3f3f3f;
// struct edge{
//     int v;
//     int w;
// };

// struct node{
//     int u;
//     int d;
//     bool operator<(const node& other) const {
//         return d > other.d;
//     }
// };

// vector<vector<edge>>edges;
// vector<int>dist, vis;

// void dijkstra(int u) {

// }
// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     int n, p, c;
//     cin >> n >> p >> c;
//     edges.resize(p+1), dist.resize(p+1, INF), vis.resize(p+1, 0);
//     vector<int>cowcnt(p+1, 0);
//     for(int i = 1;i <= n;i++) {
//         int num;
//         cin >> num;
//         cowcnt[num]++;
//     }
//     for(int i = 0;i < c;i++) {
//         int a, b, d;
//         cin >> a >> b >> d;
//         edges[a].push_back({b, d});
//         edges[b].push_back({a, d});
//     }
// }

#include<bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, p, c;
    cin >> n >> p >> c;
    vector<vector<int>>dist(p+1, vector<int>(p+1, INF));
    vector<int>cowcnt(p+1);
    for(int i = 0;i < n;i++) {
        int num;
        cin >> num;
        cowcnt[num]++;
    }
    for(int i = 1;i <= p;i++) dist[i][i] = 0;
    for(int i = 0;i < c;i++) {
        int a, b, d;
        cin >> a >> b >> d;
        dist[a][b] = min(dist[a][b], d);
        dist[b][a] = min(dist[b][a], d);
    }
    for(int k = 1;k <= p;k++) {
        for(int i = 1;i <= p;i++) {
            for(int j = 1;j <= p;j++) {
                if(dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
    int ans = INF;
    for(int i = 1;i <= p;i++) {
        int temp = 0;
        bool flag = true;
        for(int j = 1;j <= p;j++) {
            if(dist[i][j] == INF) {
                flag = false;
            }
            temp += cowcnt[j] * dist[i][j];
        }
        if(flag) ans = min(ans, temp);        
    }
    cout << ans;
    return 0;
}