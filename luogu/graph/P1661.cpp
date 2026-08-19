#include<bits/stdc++.h>
using namespace std;

using ll = long long;
struct position {
    ll x;
    ll y;
};
vector<int>fa;
vector<int>weight;
int n;

int findfa(int u) {
    if(fa[u] == u) return fa[u];
    return fa[u] = findfa(fa[u]);
}
void merge(int u, int v) {
    int fau = findfa(u), fav = findfa(v);
    if(fau == fav) return ;
    if(weight[fau] > weight[fav]) {
        fa[fav] = fau;
    } else {
        if(weight[fau] == weight[fav]) weight[fav]++;
        fa[fau] = fav;
    }
}

bool check() {
    int fas = findfa(0);
    for(int i = 1;i < n;i++) {
        if(findfa(i) != fas) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    fa.resize(n), weight.resize(n);
    for(int i = 0;i < n;i++) fa[i] = i, weight[i] = 1;
    vector<position>nodes(n);
    for(int i = 0;i < n;i++) {
        cin >> nodes[i].x >> nodes[i].y;
    }
    //相当于求两个点之间的曼哈顿距离（就是沿着方格线走的距离），因为每个点每个时刻只能向四个方向走一步
    //此时两个点都走那时间就是（曼哈顿距离+1）/2,覆盖奇数距离的情况
    vector<vector<ll>>timec(n, vector<ll>(n));
    ll maxt = 0;
    set<ll>timeq;
    for(int i = 0;i < n;i++) {
        for(int j = i+1;j < n;j++) {
            ll t = (abs(nodes[i].x - nodes[j].x) + abs(nodes[i].y - nodes[j].y) + 1LL) / 2;
            timec[i][j] = timec[j][i] = t;
            timeq.insert(t);
            maxt = max(maxt, t);
        }
    }
    ll ans = 0;
    for(auto t : timeq) {
        for(int i = 0;i < n;i++) {
            for(int j = i+1;j < n;j++) {
                if(timec[i][j]==t) {
                    merge(i, j);
                }
            }
        }
        ans = t;
        if(check()) break;
    }
    cout << ans;
    return 0;
}