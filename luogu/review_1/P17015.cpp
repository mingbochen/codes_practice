#include<bits/stdc++.h>
using namespace std;

using ll = long long;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int>a(n+2, 0);
    for(int i = 1;i <= n;i++) cin >> a[i];
    //dp[i][j]表示把从i到j的数字删除所获得的最大分数总和
    vector<vector<ll>>dp(n+1, vector<ll>(n+1));
    for(int i = 1;i <= n;i++) {
        dp[i][i] = a[i-1] + a[i+1];
    }
    for(int len = 2;len <= n;len++) {
        for(int i = 1;i+len-1 <= n;i++) {
            int j = i+len-1;
            //枚举[i,j]范围内最后删除的元素k
            //删除左侧元素是[i,k-1]
            //删除右侧元素是[k+1, j]
            //注意k要从i遍历到j不能遗漏边界情况
            for(int k = i;k <= j;k++) {
                //在len=2时候，遍历最后一个删除的i或者是j,这样是全部的情况都考虑到了
                //然后在len=3的时候使用len=2已经更新好的，遍历最后一个删除的，剩余的len<=2的时已经更新好的最大值
                //所以可以保证结果正确
                ll left_value = (k-1 >= i ? dp[i][k-1] : 0);
                ll right_value = (k+1 <= j ? dp[k+1][j] : 0);
                //删除元素k所得到的价值
                ll value = a[i-1] + a[j+1];
                dp[i][j] = max(dp[i][j], left_value+right_value+value);
            }
        }
    }
    cout << dp[1][n];
    return 0;
}