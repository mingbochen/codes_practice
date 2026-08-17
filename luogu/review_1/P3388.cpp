#include<bits/stdc++.h>
using namespace std;

vector<vector<int>>edges;
vector<int>dfn, low;
vector<char>is_cut;
int tot = 0, cnt = 0;

void tarjan(int u, int fa) {
    dfn[u] = low[u] = ++tot;
    int child = 0;
    for(auto v : edges[u]) {
        if(v == fa) continue;
        if(!dfn[v]) {
            //没有访问过才加child数量，防止多加
            child++;
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            //非根节点，这里不能进行计数
            //因为可能对于u的多个子节点v都满足该条件
            //is_cut可以重复复制为true,但是cnt不能重复计数
            //优化为tarjan只负责标记，tarjan全部做完之后再计数
            //或者这里要加一个判断!is_cut[u]才对cnt进行加1
            if(fa != 0 && low[v] >= dfn[u]) {
                is_cut[u] = true;
            }
        } else {
            low[u] = min(low[u], dfn[v]);
        }
    }
    //对于根节点，子节点数大于1才是割点
    if(fa == 0 && child >= 2) {
        is_cut[u] = true;
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    edges.resize(n+1), dfn.resize(n+1), low.resize(n+1), is_cut.resize(n+1, 0);
    for(int i = 0;i < m;i++) {
        int u, v;
        cin >> u >> v;
        edges[u].push_back(v);
        edges[v].push_back(u);
    }
    for(int i = 1;i <= n;i++) {
        if(!dfn[i]) tarjan(i, 0);
    }
    for(int i = 1;i <= n;i++) {
        if(is_cut[i]) cnt++;
    }
    cout << cnt << endl;
    for(int i = 1;i <= n;i++) {
        if(is_cut[i]) cout << i << ' ';
    }
    return 0;
}