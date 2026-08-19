#include<bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<vector<int>>dist(n+1, vector<int>(n+1, INF));
    for(int i = 0;i < n-1;i++) {
        int a, b;
        cin >> a >> b;
        dist[a][b] = 1;
    }
    for(int i = 1;i <= n;i++) dist[i][i] = 0;
    for(int k = 1;k <= n;k++) {
        for(int i = 1;i <= n;i++) {
            for(int j = 1;j <= n;j++) {
                if(dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
    int ans = -1;
    for(int i = 1;i <= n;i++) {
        bool flag = true;
        for(int j = 1;j <= n;j++) {
            if(dist[j][i] == INF) {
                flag = false;
                break;
            }
        }
        if(flag) {
            ans = i;
            break;
        }
    }
    cout << ans;
    return 0;
}