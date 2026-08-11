#include<bits/stdc++.h>
using namespace std;

vector<int>color;
vector<vector<int>>edges;
vector<vector<int>>dp;//dp[i][0]表示以i这个根节点为美丽路径中的一个中间节点的长度
//dp[i][1]表示以i这个根节点为终点的美丽路径的长度

//ans的路径可能不会经过根节点，所以要在dfs的时候进行维护
int ans = 0;

void dfs(int u, int fa) {
    dp[u][0] = 1;
    dp[u][1] = 1;
    for(auto v : edges[u]) {
        if(v == fa) continue;
        dfs(v, u);
        //1.u作为结束节点
        if(color[u] == color[v]) {
            dp[u][1] = max(dp[u][1], 1);
        } else {
            dp[u][1] = max(dp[u][1], dp[v][1] + 1);
        }
        ans = max(ans, dp[u][1]);
    }
    //2.u作为中间节点
    //得到和u不同色的子节点中的最大值和第二大值就可以，不用双层循环
    int max1 = 0, max2 = 0;
    for(auto v : edges[u]) {
        if(color[v] != color[u] && v != fa) {
            if(dp[v][1] >= max1) {
                max2 = max1;
                max1 = dp[v][1];
            } else if(dp[v][1] > max2) {
                max2 = dp[v][1];
            }
        }
    }
    dp[u][0] = max(dp[u][0], max1 + max2 + 1);
    ans = max(ans, dp[u][0]);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    color.resize(n+1);
    edges.resize(n+1);
    dp.resize(n+1, vector<int>(2));
    for(int i = 1;i <= n;i++) {
        cin >> color[i];
    }
    for(int i = 0;i < n-1;i++) {
        int u, v;
        cin >> u >> v;
        edges[u].emplace_back(v);
        edges[v].emplace_back(u);
    }
    dfs(1, 0);
    cout << ans;
    return 0;
}