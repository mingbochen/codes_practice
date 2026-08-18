#include<bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, h, delta;
    cin >> n >> h >> delta;
    //num[i][j]表示在第i棵树的高度j处有多少柿子
    vector<vector<int>>num(n+1, vector<int>(h+1));
    for(int i = 1;i <= n;i++) {
        int total = 0;
        cin >> total;
        for(int j = 0;j < total;j++) {
            int height;
            cin >> height;
            num[i][height]++;
        }
    }
    //dp[i][j]表示小猫走到第i棵树且高度为j的时候能够吃到的最多柿子数量
    vector<vector<int>>dp(n+1, vector<int>(h+1));
    vector<int>best(h+1);//best[i]表示在到达高度i处所能够吃到的最多柿子数量
    for(int i = 1;i <= n;i++) {
        dp[i][h] = num[i][h];
        best[h] = max(dp[i][h], best[h]);
    }
    //因为最外层是高度且倒叙循环，所以当更新低高度的时候高高度已经更新好了
    for(int i = h-1;i >= 0;i--) {
        for(int j = 1;j <= n;j++) {
            dp[j][i] = max({dp[j][i], dp[j][i+1]+num[j][i], (i+delta <= h ? best[i+delta] : 0)+num[j][i]});
            best[i] = max(best[i], dp[j][i]);
        }
    }
    cout << best[0];
    return 0;
}