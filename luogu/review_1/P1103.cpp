#include<bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;
bool comp(const pair<int, int>& a, const pair<int, int>& b) {
    return a.first < b.first;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    vector<pair<int, int>>books(n+1);
    for(int i = 1;i <= n;i++) {
        cin >> books[i].first >> books[i].second;
    }
    sort(books.begin(), books.end(), comp);
    int left = n-k;
    //dp[i][j]表示前i本书中留下j本书,其中第i本必须留下此时前i本书的最小不整齐度
    vector<vector<int>>dp(n+1, vector<int>(left+1, INF));
    for(int i = 1;i <= n;i++) dp[i][1] = 0;
    for(int i = 1;i <= n;i++) {
        //j表示前i本书中保留j本,不用考虑1本,因为保留一本的情况已经进行了考虑,即不整齐度为0
        for(int j = 2;j <= left;j++) {
            for(int h = 1;h < i;h++) {
                if(dp[h][j-1] != INF) {
                    dp[i][j] = min(dp[h][j-1]+abs(books[i].second-books[h].second), dp[i][j]);
                }
            }
        }
    }
    int ans = INF;
    for(int i = 1;i <= n;i++) {
        ans = min(ans, dp[i][left]);
    }
    cout << ans;
    return 0;
}