#include<bits/stdc++.h>
using namespace std;

vector<long long>ans;
vector<long long>beauty;
vector<vector<int>>edges;

void dfs(int u, int fa) {
    ans[u] = beauty[u];
    for(auto v : edges[u]) {
        if(v == fa) continue;
        dfs(v, u);
        //选子树v和不选子树v
        ans[u] = max(ans[u], ans[u] + ans[v]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    beauty.resize(n+1);
    edges.resize(n+1);
    ans.resize(n+1);
    for(int i = 1;i <= n;i++) {
        cin >> beauty[i];
    }
    for(int i = 0;i < n-1;i++) {
        int a, b;
        cin >> a >> b;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }
    long long result = INT_MIN;
    dfs(1, 0);
    //只需要遍历ans[i]就可以了不需要再以每个节点为根算出ans[i],
    for(int i = 1;i <= n;i++) result = max(result, ans[i]);
    cout << result;
    return 0;
}