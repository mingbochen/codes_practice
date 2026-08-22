#include<bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<double>num(n);
    for(int i = 0;i < n;i++) cin >> num[i];
    // vector<int>dp(n, 1);
    // for(int i = 0;i < n;i++) {
    //     for(int j = i+1;j < n;j++) {
    //         if(num[j] > num[i]) dp[j] = max(dp[j], dp[i]+1);
    //     }
    // }
    // int ans = 0;
    // for(int i = 0;i < n;i++) ans = max(ans, dp[i]);
    //最长严格单调递增子序列的长度
    vector<int>tails;
    for(int i = 0;i < n;i++) {
        auto it = lower_bound(tails.begin(), tails.end(), num[i]);
        if(it == tails.end()) {
            tails.push_back(num[i]);
        } else {
            *it = num[i];
        }
    }
    cout << n - tails.size();
    return 0;
}