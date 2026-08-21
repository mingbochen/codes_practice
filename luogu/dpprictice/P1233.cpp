// #include<bits/stdc++.h>
// using namespace std;

// const int INF = 0x3f3f3f3f;
// struct stick{
//     int l;
//     int w;
// };
// int n;
// int ans = INF;
// vector<stick>s;
// vector<bool>used;

// //num记录已经使用过的木棍的数量
// //last记录上一个处理木棍的下标
// //cost记录目前为止的准备时间
// void dfs(int index, int num, int last, int cost) {
//     if(index > n && num < n) return;
//     if(num >= n) {
//         ans = min(ans, cost);
//         return;
//     }
//     //找没有使用过的
//     int ready = 0;
//     for(int i = index;i <= n;i++) {
//         if(!used[i]) {
//             ready = i;
//             int chosecost = 0;
//             //last==-1表示第一根处理的木棍
//             if(last == -1) {
//                 chosecost = 1;
//             } else if(s[last].l >= s[ready].l && s[last].w >= s[ready].w) {
//                 chosecost = 0;
//             } else {
//                 chosecost = 1;
//             }
//             //选择这跟木棍
//             used[ready] = 1;
//             dfs(i+1, num+1, ready, cost+chosecost);
//             //回溯
//             used[ready] = 0;
//         } else {
//             //不选择这跟木棍
//             dfs(i+1, num, last, cost);
//         }
//     }
    
// }
// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     cin >> n;
//     s.resize(n+1), used.resize(n+1, 0);
//     for(int i = 1;i <= n;i++) {
//         cin >> s[i].l >> s[i].w;
//     }
//     dfs(1, 0, -1, 0);
//     cout << ans;
//     return 0;
// }

#include<bits/stdc++.h>
using namespace std;

struct stick{
    int l;
    int w;
};

//按照长度进行降序排序,对于长度相同的宽度进行降序排序
bool comp(const stick& a ,const stick& b) {
    if(a.l != b.l) {
        return a.l > b.l;
    }
    return a.w > b.w;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<stick>s(n);
    for(int i = 0;i < n;i++) cin >> s[i].l >> s[i].w;
    sort(s.begin(), s.end(), comp);
    //排过序之后长度就满足了条件,现在就是求在这个序列可以最少划分为多少个递减子序列
    //注意这里是递减子序列
    //如果几根木棍想被放在同一次准备中连续加工，那么它们的宽度必须满足：
    //前一个宽度 >= 后一个宽度
    //一个序列最少划分成多少个非递增子序列 = 它的最长严格递增子序列 LIS 的长度。
    vector<int>dp(n);//dp[i]表示以i结尾的最长严格递增子序列长度
    for(int i = 0;i < n;i++) dp[i] = 1;
    for(int i = 0;i < n;i++) {
        for(int j = i+1;j < n;j++) {
            if(s[j].w > s[i].w) dp[j] = max(dp[j], dp[i]+1);
        }
    }
    int ans = 0;
    for(int i = 0;i < n;i++) {
        ans = max(ans, dp[i]);
    }
    cout << ans;
    return 0;
}