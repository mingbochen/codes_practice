#include<bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int m, s, t;
    cin >> m >> s >> t;
    //dp[i]表示时间i内可以走的最远距离
    vector<int>dp(t+1);
    int tempt = 1;
    while(tempt <= t) {
        if(m >= 10) {
            dp[tempt] = max(dp[tempt], dp[tempt-1]+60);
            m -= 10;
        } else {
            m += 4;
            dp[tempt] = max(dp[tempt], dp[tempt-1]);
        }
        tempt++;
    }
    for(int i = 1;i <= t;i++) {
        dp[i] = max(dp[i], dp[i-1] + 17);
    }
    int ans = 0;
    for(int i = 1;i <= t;i++) {
        if(dp[i] >= s) {
            ans = i;
            break;
        }
    }
    if(ans) {
        cout << "Yes" << endl << ans;
    } else {
        cout << "No" << endl << dp[t];
    }
}