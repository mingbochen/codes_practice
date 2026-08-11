#include<bits/stdc++.h>
using namespace std;



// //不知道为啥是错误的
// vector<vector<int>>edges;
// vector<vector<char>>flag;
// int ans = 0;
// void dfs(int u, int fa) {
//     bool s = false;
//     for(auto v : edges[u]) {
//         if(v == fa) continue;
//         dfs(v, u);
//         //如果该根的子节点中存在一个节点没有被瞭望到
//         if(!flag[u][v] || !flag[v][u]) {
//             s = true;
//             break;
//         }
//     }
//     if(s) {
//         for(auto v : edges[u]) {
//             flag[u][v] = true;
//             flag[v][u] = true;
//         }
//         ans++;
//     }
// }

//标准树形DP
vector<vector<int>>edges;
vector<vector<int>>dp; //dp[u][0]表示u不放士兵

void dfs(int u, int fa) {
    dp[u][0] = 0;
    dp[u][1] = 1;
    for(auto v : edges[u]) {
        if(v == fa) continue;
        dfs(v, u);
        //u不放的话，所有子节点必须放
        dp[u][0] += dp[v][1];
        //u放的话，子节点可以选择不放
        dp[u][1] += min(dp[v][0], dp[v][1]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    edges.resize(n);
    dp.resize(n, vector<int>(2));
    for(int i = 0;i < n;i++) {
        int index;
        cin >> index;
        int k;
        cin >> k;
        while(k--) {
            int r;
            cin >> r;
            edges[index].push_back(r);
            edges[r].push_back(index);
        }
    }
    dfs(0, -1);
    cout << min(dp[0][0], dp[0][1]);
    return 0;
}