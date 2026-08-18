#include<bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int>price(n+2, 0);
    for(int i = 1;i <= n;i++) cin >> price[i];
    //dp[i]表示以i结束的最长下降子序列的长度
    vector<int>dp(n+2);
    //cnt[i]表示以i结尾且长度为dp[i]的序列的种类数目
    vector<int>cnt(n+2);
    //题目中说股票价格都是大于0的，所以可以在最后添加一个0,
    //这样在统计结果的时候输出dp[n+1], cnt[n+1]就可以了
    for(int i = 1;i <= n+1;i++) dp[i] = 1;
    //外层要是从小到大遍历，保证在遍历到i的时候i之前的dp以及cnt已经算好了
    for(int i = 1;i <= n+1;i++) {
        //最长下降子序列
        for(int j = 1;j < i;j++) {
            if(price[j] > price[i]) {
                dp[i] = max(dp[i], dp[j]+1);
            }
        }

        //统计数目
        set<int>used;
        //如果dp[i]=1,那么cnt[i] = 1
        if(dp[i] == 1) {
            cnt[i] = 1;
            continue;
        }
        //倒序遍历，出现6 4(1) 4(2) 3这样的时候
        //只统计6 4(2) 3这一种，防止重复统计
        for(int j = i-1;j >= 1;j--) {
            if(price[j] > price[i] 
                && dp[j]+1 == dp[i] //保证dp[i]是由dp[j]所更新而来的，即统计的该序列是一个最长序列
                && !used.count(price[j])) {
                    cnt[i] += cnt[j];
                    used.insert(price[j]);
                }
        }
    }
    //长度需要减去添加的虚拟0
    cout << dp[n+1]-1 << ' ' << cnt[n+1];
    return 0;
}