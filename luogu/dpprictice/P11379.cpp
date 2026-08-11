#include<bits/stdc++.h>
using namespace std;

vector<int>a;
vector<vector<int>>edges;
vector<vector<int>>dp;//dp[i][j]表示的是以i为端点包含j个黑色点数时经过的最多总结点数
int n, k;
int ans = 0;
void dfs(int u, int fa) {
    dp[u][a[u]] = 1;//表示当前以u为端点至少经过一个节点就是u节点自身
    //先处理u作为中间节点的
    for(auto v : edges[u]) {
        if(v == fa) continue;
        dfs(v, u);
        //prefix[j]记录当前dp[u][0...j]中的最大的路径长度
        vector<int>prefix(k+1, INT_MIN);
        prefix[0] = dp[u][0];
        for(int j = 1;j <= k;j++) {
            prefix[j] = max(prefix[j-1], dp[u][j]);
        }
        //从当前孩子v中选择一条路径
        for(int j = 0;j <= k;j++) {
            if(dp[v][j] < 0) continue;
            //另外一遍最多还能使用k-j个黑点
            int remain = k-j;
            if(remain >= 0 && prefix[remain] >= 0) {
                ans = max(ans, prefix[remain] + dp[v][j]);
            }
        }
        //更新dp[u]
        //这里要在上面计算完prefix之后再更新dp[u]，不然dp[u]可能是由dp[v]更新而来
        //然后在上面又使用dp[v][j]进行更新，使得路径会被重复计算
        vector<int>old = dp[u];
        for(int j = 0;j <= k;j++) {
            if(dp[v][j] < 0) continue;
            int newBlack = j+a[u];
            if(newBlack <= k) {
                dp[u][newBlack] = max(dp[u][newBlack], dp[v][j] + 1);
            }
        }
    }
    //再处理u作为端点的情况
    for(int j = 0;j <= k;j++) {
        if(dp[u][j] >= 0) {
            ans = max(ans, dp[u][j]);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> k;
    a.resize(n+1);
    edges.resize(n+1);
    dp.resize(n+1, vector<int>(k+1, INT_MIN));
    for(int i = 1;i <= n;i++) cin >> a[i];
    for(int i = 0;i < n-1;i++) {
        int u, v;
        cin >> u >> v;
        edges[u].push_back(v);
        edges[v].push_back(u);
    }
    dfs(1, 0);
    cout << ans;
    return 0;
}