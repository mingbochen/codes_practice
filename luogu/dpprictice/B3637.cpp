// #include<bits/stdc++.h>
// using namespace std;

// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     int n;
//     cin >> n;
//     vector<int>nums(n+1);
//     for(int i = 1;i <= n;i++) cin >> nums[i];
//     vector<int>dp(n+1);//dp[i]表示以nums[i]结尾的最长上升子序列的长度
//     for(int i = 1;i <= n;i++) {
//         dp[i] = 1;
//         for(int j = 1;j < i;j++) {
//             if(nums[i] > nums[j]) {
//                 dp[i] = max(dp[i], dp[j]+1);
//             }
//         }
//     }
//     int ans = 0;
//     for(int i = 1;i <= n;i++) ans = max(ans, dp[i]);
//     cout << ans;
//     return 0;
// }

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int>tails;
    for(int i = 0;i < n;i++) {
        int num;
        cin >> num;
        auto it = lower_bound(tails.begin(), tails.end(), num);
        if(it == tails.end()) {
            tails.push_back(num);
        } else {
            *it = num;
        }
    }
    cout << tails.size();
    return 0;
}