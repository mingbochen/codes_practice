#include<bits/stdc++.h>
using namespace std;

vector<vector<int>>edges;
vector<int>du;
vector<int>vis;

int dfs(int u, int fa) {
    vis[u] = true;
    int ans = 0;
    if(du[u] % 2 != 0) ans++;
    for(auto v : edges[u]) {
        if(v == fa || vis[v]) continue;
        ans += dfs(v, u);
    }
    return ans;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    edges.resize(n+1);
    du.resize(n+1, 0);
    vis.resize(n+1, false);
    for(int i = 0;i < m;i++) {
        int a, b;
        cin >> a >> b;
        edges[a].push_back(b);
        edges[b].push_back(a);
        du[a]++, du[b]++;
    }
    int ans = 0;
    for(int i = 1;i <= n;i++) {
        if(!vis[i]) {
            //奇数度点的个数
            int odds = dfs(i, 0);
            //不是单个节点的连通分量
            if(du[i]) {
                //没有奇数度数的连通分量以及有奇数度数的连通分量
                ans += max(1, odds/2);
            }
        }
    }
    cout << ans;
    return 0;
}