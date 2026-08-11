#include<bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<int>height(n);
    for(int i = 0;i < n;i++) {
        cin >> height[i];
    }
    //dp1[i]记录以i为结尾的最长上升子序列长度
    //dp2[i]记录以i为结尾的最长下降子序列长度
    //初始每个元素都为1
    vector<int>dp1(n, 1), dp2(n, 1);
    for(int i = 0;i < n;i++) {
        for(int j = 0;j < i;j++) {
            if(height[j] < height[i]) {
                dp1[i] = max(dp1[i], dp1[j]+1);
            }
        }
    }
    for(int i = n-1;i >= 0;i--) {
        for(int j = n-1;j >i;j--) {
            if(height[j] < height[i]) {
                dp2[i] = max(dp2[i], dp2[j]+1);
            }
        }
    }
    int ans = 0;
    for(int i = 0;i < n;i++) {
        ans = max(ans, dp1[i] + dp2[i]-1);
    }
    cout << n-ans;
    return 0;
}