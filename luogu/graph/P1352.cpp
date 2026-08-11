#include<bits/stdc++.h>
using namespace std;

vector<vector<int>>edges;
vector<int>r;
//dp[u][0]表示以u为根的子树的最大快乐值，u不参加，1代表u参加
vector<vector<int>>dp;

void dfs(int u, int fa) {
    dp[u][1] = r[u];
    for(auto v : edges[u]) {
        if(v == fa) continue;
        dfs(v, u);
        //u不参加，v可以选择参加或者不参加
        dp[u][0] = max(dp[u][0] + dp[v][1], dp[u][0] + dp[v][0]);
        //u参加，v只能不参加
        dp[u][1] = max(dp[u][1], dp[u][1] + dp[v][0]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    edges.resize(n+1), r.resize(n+1);
    dp.resize(n+1, vector<int>(2));
    for(int i = 1;i <= n;i++) cin >> r[i];
    vector<char>isboss(n+1, 1);
    for(int i = 0;i < n-1;i++) {
        int l, k;
        cin >> l >> k;
        edges[k].push_back(l);
        isboss[l] = 0;
    }
    int root = 0;
    for(int i = 1;i <= n;i++) {
        if(isboss[i]){
            root = i;
            break;
        } 
    }
    dfs(root, 0);
    cout << max(dp[root][0], dp[root][1]);
    return 0;
}