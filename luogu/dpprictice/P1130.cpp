#include<bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<int>>cost(m+1, vector<int>(n+1));
    for(int i = 1;i <= m;i++) {
        for(int j = 1;j <= n;j++) {
            cin >> cost[i][j];
        }
    }
    //dp[i][j]表示第i步是第j小组
    vector<vector<int>>dp(n+1, vector<int>(m+1, INF));
    for(int i = 1;i <= m;i++) {
        dp[1][i] = cost[i][1];
    }
    for(int i = 2;i <= n;i++) {
        for(int j = 1;j <= m;j++) {
            dp[i][j] = min({dp[i][j], dp[i-1][j]+cost[j][i], (j-1 == 0 ? dp[i-1][m] : dp[i-1][j-1]) + cost[j][i]});
        }
    }
    int ans = INF;
    for(int i = 1;i <= m;i++) ans = min(ans, dp[n][i]);
    cout << ans;
    return 0;
}