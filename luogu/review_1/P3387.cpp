#include<bits/stdc++.h>
using namespace std;

vector<vector<int>>edges;
vector<int>dfn, low, belong, instack;
vector<int>scc_weight;
stack<int>st;
vector<int>a;

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
            scc_weight[scc_cnt] += a[v];
            belong[v] = scc_cnt;
            instack[v] = 0;
        } while(u != v);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    edges.resize(n+1), dfn.resize(n+1), belong.resize(n+1), low.resize(n+1);
    instack.resize(n+1, 0), scc_weight.resize(n+1), a.resize(n+1);
    for(int i = 1;i <= n;i++) cin >> a[i];
    for(int i = 0;i < m;i++) {
        int u, v;
        cin >> u >> v;
        edges[u].push_back(v);
    }
    for(int i = 1;i <= n;i++) {
        if(!dfn[i]) tarjan(i);
    }
    vector<vector<int>>dag(scc_cnt+1);
    vector<int>du(scc_cnt+1);
    vector<int>dp(scc_cnt+1, 0);
    for(int u = 1;u <= n;u++) {
        for(auto v : edges[u]) {
            if(belong[u] != belong[v]) {
                dag[belong[u]].push_back(belong[v]);
                du[belong[v]]++;
            }
        }
    }
    queue<int>q;
    for(int i = 1;i <= scc_cnt;i++) {
        if(du[i] == 0) {
            q.push(i);
            dp[i] = scc_weight[i];
        }
    }
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        for(auto v : dag[u]) {
            if(du[v]) {
                du[v]--;
                dp[v] = max(dp[v], dp[u] + scc_weight[v]);
                if(!du[v]) q.push(v);
            }
        }
    }
    int ans = 0;
    for(int i = 1;i <= scc_cnt;i++) ans = max(ans, dp[i]);
    cout << ans;
    return 0;
}