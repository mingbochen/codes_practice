#include<bits/stdc++.h>
using namespace std;

vector<vector<int>>edges;
vector<int>a;
vector<char>vis;
vector<int>dp;//dp[u]是把u点燃之后能够烧到多少节点
int ans = 0;

//使用记忆化搜索
int dfs(int u) {
    //如果u已经遍历过了，则直接返回u的结果
    if(dp[u]) return dp[u];
    for(auto v : edges[u]) {
        if(a[v] < a[u]) {
            dp[u] += dfs(v);
        }
    }
    return dp[u]+=1;
}

// //不管会不会写，先看能不能骗到分，下面的代码已经获得了40分，问题就是复杂度高
// //先把自己能写出来的提交，得到部分分后再追求全对，不要一直想着全对的方案，但是又想不出来，最后导致没分
// //点燃u
// long long dfs(int u, int fa) {
//     long long result = 1;
//     for(auto v : edges[u]) {
//         if(v == fa) continue;
//         if(a[v] < a[u]) {
//             result += dfs(v, u);
//         }
//     }
//     return result;
// }
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    edges.resize(n+1);
    a.resize(n+1);
    vis.resize(n+1, 0), dp.resize(n+1);
    for(int i = 1;i <= n;i++) cin >> a[i];
    for(int i = 0;i < n-1;i++) {
        int u, v;
        cin >> u >> v;
        edges[u].emplace_back(v);
        edges[v].emplace_back(u);
    }
    for(int i = 1;i <= n;i++) {
        ans = max(ans, dfs(i));
    }
    cout << ans;
    return 0;
}