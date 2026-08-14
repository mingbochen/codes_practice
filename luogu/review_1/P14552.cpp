#include<bits/stdc++.h>
using namespace std;

vector<vector<int>>edges;
vector<int>color;
vector<vector<int>>cnt;

bool dfs(int u, int c) {
    color[u] = c;
    cnt[c].push_back(u);
    for(auto v : edges[u]) {
        if(color[v] == -1) {
            if(!dfs(v, c^1)) return false;
        } else if(color[u] == color[v]) {
            return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n;
    edges.resize(n+1);
    color.resize(n+1, -1);
    for(int i = 0;i < n;i++) {
        int u, v;
        cin >> u >> v;
        edges[u].push_back(v);
        edges[v].push_back(u);
    }
    cin >> k;
    vector<int>ans;
    for(int i = 1;i <= n;i++) {
        if(color[i] != -1) continue;
        cnt.clear();
        cnt.resize(3);
        if(dfs(i, 0)) {
            if(cnt[0].size() > cnt[1].size()) {
                for(auto v : cnt[0]) ans.push_back(v);
            } else {
                for(auto v : cnt[1]) ans.push_back(v);
            }
        }
    }
    if(ans.size() >= k) {
        for(int i = 0;i < k;i++) cout << ans[i] << ' ';
    } else {
        cout << 0;
    }
    return 0;
}