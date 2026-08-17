#include<bits/stdc++.h>
using namespace std;

using ll = long long;
vector<vector<int>>edges;
vector<int>dfn, low, sz; //low表示的是不通过父边能到达的最早遍历的点，注意不能通过父边
vector<char>flag;
vector<ll>ans;
int tot = 0;
int n, m;

void tarjan(int u, int fa) {
    dfn[u] = low[u] = ++tot;
    ans[u] = 1LL * n * (n-1);//如果没有边的时候的所有不连通有序点对
    sz[u] = 1;
    int sum = 0, remain = 0;
    for(auto v : edges[u]) {
        if(v == fa) continue;
        if(!dfn[v]) {
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            sz[u] += sz[v];
            //判断u是否是割点
            if(low[v] >= dfn[u]) {
                sum += sz[v];
                //如果是割点的话, 减去割点里面连通分量中连通的有序对数量
                ans[u] -= 1LL * sz[v] * (sz[v] - 1);
            }
        } else {
            //对于返祖边更新low,父边不能用来更新low
            low[u] = min(low[u], dfn[v]);
        }
    }
    remain = n-sum-1;
    ans[u] -= 1LL * remain * (remain - 1);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    edges.resize(n+1), dfn.resize(n+1), low.resize(n+1);
    sz.resize(n+1), flag.resize(n+1, false), ans.resize(n+1);
    //割点
    for(int i = 0;i < m;i++) {
        int a, b;
        cin >> a >> b;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }
    tarjan(1, 0);
    for(int i = 1;i <= n;i++) {
        cout << ans[i] << '\n';
    }
    return 0;
}