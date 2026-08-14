#include<bits/stdc++.h>
using namespace std;


// vector<vector<int>>edges;
// vector<int>vis;
// vector<int>color;//-1表示未染色,1和0表示不相同的颜色
// vector<int>cnt;
// bool flag = false;
// void dfs(int u, int c) {
//     color[u] = c;
//     cnt[c]++;
//     vis[u] = true;
//     for(auto v : edges[u]) {
//         if(color[v] == color[u]) {
//             flag = true;
//             return;
//         }
//         if(vis[v]) continue;
//         dfs(v, color[u]^1);
//     }
// }
// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     //二分图
//     int n, m;
//     cin >> n >> m;
//     edges.resize(n+1);
//     vis.resize(n+1, false);
//     color.resize(n+1, -1);
//     cnt.resize(3, 0);
//     for(int i = 0;i < m;i++) {
//         int u, v;
//         cin >> u >> v;
//         edges[u].push_back(v);
//         edges[v].push_back(u);
//     }
//     int ans = 0;
//     for(int i = 1;i <= n;i++) {
//         if(!vis[i]){
//             cnt.assign(3, 0);
//             dfs(i, 0);
//             if(flag) {
//                 cout << "Impossible";
//                 return 0;
//             } else {
//                 //选择该连通分量中颜色较少的
//                 ans += min(cnt[0], cnt[1]);
//             }
//         }
//     }
//     cout << ans;
//     return 0;
// }

vector<vector<int>>edges;
vector<int>color;//-1未染色,同时承担了没有被访问过的判断
//0/1两种颜色
vector<int>cnt(3, 0);

//false表示不是二分图
bool dfs(int u, int c) {
    color[u] = c;
    cnt[c]++;
    for(int v : edges[u]) {
        if(color[v] == -1) {
            //没有被染色,则继续递归v
            if(!dfs(v, c^1)) return false;
        } else if(color[v] == color[u]) {
            //如果染过色了且和u是同样的颜色,那么也返回false
            return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    edges.resize(n+1);
    color.assign(n+1, -1);
    for(int i = 0;i < m;i++) {
        int u, v;
        cin >> u >> v;
        edges[u].push_back(v);
        edges[v].push_back(u);
    }
    int ans = 0;
    //整张图可能不连通,所以需要遍历每个点
    for(int i = 1;i <= n;i++) {
        if(color[i] != -1) continue;
        cnt[0] = cnt[1] = 0;
        if(!dfs(i, 0)) {
            cout << "Impossible";
            return 0;
        }
        ans += min(cnt[0], cnt[1]);
    }
    cout << ans;
    return 0;
}
