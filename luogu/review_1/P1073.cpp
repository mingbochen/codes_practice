#include<bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;
vector<vector<int>>edges;
vector<int>dfn, low, belong, instack;
vector<int>mx, mn, price;//每个连通分量中的最小买入值和最大卖出值
stack<int>st;
int tot = 0, scc_cnt = 0;

void tarjan(int u) {
    dfn[u] = low[u] = ++tot;
    st.push(u);
    instack[u] = 1;
    for(auto v : edges[u]) {
        if(!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if(instack[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if(low[u] == dfn[u]) {
        scc_cnt++;
        int v;
        do {
            v = st.top();
            st.pop();
            instack[v] = 0;
            mn[scc_cnt] = min(mn[scc_cnt], price[v]);
            mx[scc_cnt] = max(mx[scc_cnt], price[v]);
            belong[v] = scc_cnt;
        } while(u != v);
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    edges.resize(n+1), dfn.resize(n+1), low.resize(n+1);
    belong.resize(n+1), instack.resize(n+1), mx.resize(n+1, INT_MIN);
    mn.resize(n+1, INF), price.resize(n+1);
    for(int i = 1;i <= n;i++) cin >> price[i];
    for(int i = 0;i < m;i++) {
        int x, y, z;
        cin >> x >> y >> z;
        edges[x].push_back(y);
        if(z == 2) edges[y].push_back(x);
    }
    for(int i = 1;i <= n;i++) {
        if(!dfn[i]) tarjan(i);
    }
    vector<vector<int>>dag(scc_cnt+1);
    //反向dag
    vector<vector<int>>redag(scc_cnt+1);
    vector<int>lowest(scc_cnt+1, INF), hightest(scc_cnt+1, -1);
    vector<int>indeg(scc_cnt+1), outdeg(scc_cnt+1);
    for(int u = 1;u <= n;u++) {
        for(auto v : edges[u]) {
            if(belong[u] != belong[v]) {
                dag[belong[u]].push_back(belong[v]);
                redag[belong[v]].push_back(belong[u]);
                indeg[belong[v]]++;
                outdeg[belong[u]]++;
            }
        }
    }
    //正向dag用于求从1->i的最小买入值
    //反向dag用于求从n->i的最大卖出值
    queue<int>q1, q2;
    for(int i = 1;i <= scc_cnt;i++) {
        if(indeg[i] == 0) q1.push(i);
        if(outdeg[i] == 0) q2.push(i);
    }
    int s_sccid = belong[1], e_sccid = belong[n];
    //正向dp必须从1号节点开始
    lowest[s_sccid] = mn[s_sccid];
    //反向dp必须从n号节点开始
    hightest[e_sccid] = mx[e_sccid];
    while(!q1.empty()) {
        int u = q1.front();
        q1.pop();
        for(auto v : dag[u]) {
            if(indeg[v]) {
                if(lowest[u] != INF) lowest[v] = min({lowest[v], lowest[u], mn[v]});
                indeg[v]--;
                if(indeg[v] == 0) q1.push(v);
            }
        }
    }
    while(!q2.empty()) {
        int u = q2.front();
        q2.pop();
        for(auto v : redag[u]) {
            if(outdeg[v]) {
                if(hightest[u] != -1) hightest[v] = max({hightest[v], hightest[u], mx[v]});
                outdeg[v]--;
                if(outdeg[v] == 0) q2.push(v);
            }
        }
    }
    int ans = 0;
    for(int i = 1;i <= scc_cnt;i++) {
        ans = max(ans, hightest[i]-lowest[i]);
    }
    if(ans <= 0) {
        cout << 0;
    } else {
        cout << ans;
    }
    return 0;
}