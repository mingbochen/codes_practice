// #include<bits/stdc++.h>
// using namespace std;

// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     int n;
//     cin >> n;
//     vector<int>price(n+2, 0);
//     for(int i = 1;i <= n;i++) cin >> price[i];
//     //dp[i]表示以i结束的最长下降子序列的长度
//     vector<int>dp(n+2);
//     //cnt[i]表示以i结尾且长度为dp[i]的序列的种类数目
//     vector<int>cnt(n+2);
//     //题目中说股票价格都是大于0的，所以可以在最后添加一个0,
//     //这样在统计结果的时候输出dp[n+1], cnt[n+1]就可以了
//     for(int i = 1;i <= n+1;i++) dp[i] = 1;
//     //外层要是从小到大遍历，保证在遍历到i的时候i之前的dp以及cnt已经算好了
//     for(int i = 1;i <= n+1;i++) {
//         //最长下降子序列
//         for(int j = 1;j < i;j++) {
//             if(price[j] > price[i]) {
//                 dp[i] = max(dp[i], dp[j]+1);
//             }
//         }

//         //统计数目
//         set<int>used;
//         //如果dp[i]=1,那么cnt[i] = 1
//         if(dp[i] == 1) {
//             cnt[i] = 1;
//             continue;
//         }
//         // 对相同 price[j] 的候选状态，只能统计最后出现的那个。
//         // 因为后出现的相同价格能够继承前一个位置的所有方案，
//         // 并且还可能包含中间新产生的方案。
//         // 所以必须倒序枚举 j，再按照 price[j] 去重。
//         for(int j = i-1;j >= 1;j--) {
//             if(price[j] > price[i] 
//                 && dp[j]+1 == dp[i] //保证dp[i]是由dp[j]所更新而来的，即统计的该序列是一个最长序列
//                 && !used.count(price[j])) {
//                     cnt[i] += cnt[j];
//                     used.insert(price[j]);
//                 }
//         }
//     }
//     //长度需要减去添加的虚拟0
//     cout << dp[n+1]-1 << ' ' << cnt[n+1];
//     return 0;
// }

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int>price(n+1, 0);
    for(int i = 0;i < n;i++) {
        cin >> price[i];
    }
    vector<int>dp(n+1, 1);
    vector<int>cnt(n+1, 0);
    for(int i = 0;i <= n;i++) {
        for(int j = 0;j < i;j++) {
            if(price[j] > price[i]) dp[i] = max(dp[i], dp[j]+1);
        }
        set<int>used;
        if(dp[i] == 1) {
            cnt[i] = 1;
            continue;
        }
        for(int j = i-1;j >= 0;j--) {
            if(dp[i] == dp[j]+1
                && !used.count(price[j])
                && price[j] > price[i]) {
                    cnt[i] += cnt[j];
                    used.insert(price[j]);
                }
        }
    }
    cout << dp[n]-1 << ' ' << cnt[n];
    return 0;
}