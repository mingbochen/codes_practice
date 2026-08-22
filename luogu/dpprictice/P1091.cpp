// #include<bits/stdc++.h>
// using namespace std;

// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     int n;
//     cin >> n;
//     vector<int>height(n);
//     for(int i = 0;i < n;i++) cin >> height[i];
//     //dp1负责记录每个位置作为末尾的最长上升子序列长度(注意这里是子序列而不是子串, 子序列是可以中间跳过元素的)
//     vector<int>dp1(n+1, 1);
//     //dp2负责记录以每个位置作为开始的最长下降子序列的长度
//     vector<int>dp2(n+1, 1);
//     for(int i = 0;i < n;i++) {
//         for(int j = 0;j < i;j++) {
//             if(height[j] < height[i]) {
//                 dp1[i] = max(dp1[i], dp1[j] + 1);//表示从j之前的子序列再拼上i
//             }
//         }
//     }
//     //这里i要从大到小进行遍历因为dp2[i]的更新依赖于比它大的dp元素
//     for(int i = n-1;i >= 0;i--) {
//         for(int j = n-1;j > i;j--) {
//             if(height[j] < height[i]) {
//                 dp2[i] = max(dp2[i], dp2[j] + 1);
//             }
//         }
//     }
//     //依次遍历以i为峰值的合唱队形
//     int ans = 0;
//     for(int i = 0;i < n;i++) {
//         //这里要减1因为i在dp1和dp2中都被算了一遍
//         ans = max(ans, dp1[i] + dp2[i] - 1);
//     }
//     cout << n-ans;
//     return 0;
// }


// #include<bits/stdc++.h>
// using namespace std;

// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     int n;
//     cin >> n;
//     vector<int>height(n);
//     for(int i = 0;i < n;i++) cin >> height[i];
//     //dp1[i]表示以i结尾的最长递增子序列长度，dp2[i]表示以i开头的最长递减子序列长度
//     vector<int>dp1(n, 1), dp2(n, 1);
//     for(int i = 0;i < n;i++) {
//         for(int j = i+1;j < n;j++) {
//             if(height[j] > height[i]) dp1[j] = max(dp1[j], dp1[i]+1);
//         }
//     }
//     for(int i = n-1;i >= 0;i--) {
//         for(int j = i-1;j >= 0;j--) {
//             if(height[j] > height[i]) dp2[j] = max(dp2[j], dp2[i]+1);
//         }
//     }
//     int ans = 0;
//     for(int i = 0;i < n;i++) ans = max(ans, dp1[i]+dp2[i]-1);
//     cout << n-ans;
//     return 0;
// }

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int>height(n);
    for(int i = 0;i < n;i++) cin >> height[i];
    vector<int>
}