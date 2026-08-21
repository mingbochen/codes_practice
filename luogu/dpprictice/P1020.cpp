// #include<bits/stdc++.h>
// using namespace std;

// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     vector<int>input;
//     string line;
//     while(getline(cin, line)) {
//         stringstream ss(line);
//         int num;
//         while(ss >> num) input.push_back(num);
//     }
//     int n = input.size();
//     //复杂度为n^2
//     //dp[i]表示以i结尾的最长下降子序列的长度
//     vector<int>dp(n, 1);
//     //最少分成多少个下降子序列 = 最长严格递增子序列的长度
//     vector<int>dp2(n, 1);
//     for(int i = 0;i < n;i++) {
//         for(int j = i+1;j < n;j++) {
//             if(input[j] <= input[i]) dp[j] = max(dp[j], dp[i]+1);
//             if(input[j] > input[i]) dp2[j] = max(dp2[j], dp2[i]+1);
//         }
//     }
//     int ans1 = 0, ans2 = 0;
//     for(int i = 0;i < n;i++) {
//         ans1 = max(ans1, dp[i]);
//         ans2 = max(ans2, dp2[i]);
//     }

//     cout << ans1 << '\n' << ans2;
//     return 0;
// }

//复杂度为nlogn的写法
#include<bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int num;
    vector<int>input;
    while(cin >> num) input.push_back(num);
    int n = input.size();
    //求一个数组的最少划分下降子序列的个数即求一个数组的最长严格递增子序列长度
    //tails1[i]记录的是长度为i的递增子序列的最小结尾
    //比如 3 5, 2 4这两个下降子序列,那么tails1[2]记录的就是4而不是5
    vector<int>tails1;
    vector<int>tails2;
    for(int i = 0;i < n;i++) {
        //原题目是让求最长下降子序列,通过将数字边负数,从而求最长递增子序列长度
        int x = -input[i];
        //相当于使用了贪心的算法,因为如果想要递增,结尾当然是越小越好,因为结尾越小,后面可以添加的数字的可能就越多
        //lower_bound是求的大于等于,upper_bound求得是大于
        //非严格递增是用的upper_bound,因为当相等的时候也得push进去,相等的时候upper_bound返回的是end(),所以可以push进去
        auto it = upper_bound(tails1.begin(), tails1.end(), x);
        //第二问是在原数组上面求最长严格递增子序列
        auto it2 = lower_bound(tails2.begin(), tails2.end(), input[i]);
        if(it == tails1.end()) {
            //tails中没有比input[i]大的,那么可以把input[i]push进去
            tails1.push_back(x);
        } else {
            *it = x;
        }
        if(it2 == tails2.end()) {
            tails2.push_back(input[i]);
        } else {
            *it2 = input[i];
        }
    }
    cout << tails1.size() << endl << tails2.size();
    return 0;

}