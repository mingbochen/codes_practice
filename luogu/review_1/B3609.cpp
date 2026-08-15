#include<bits/stdc++.h>
using namespace std;

vector<vector<int>>edges;
vector<int>dfn, low, instack, belong;
vector<vector<int>>scc;
stack<int>st;
int tot = 0, scc_cnt = 0;

void tarjan(int u) {
    dfn[u] = low[u] = ++tot;
    instack[u] = 1;
    st.push(u);
    for(auto v : edges[u]) {
        if(!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if(instack[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    if(dfn[u] == low[u]) {
        scc_cnt++;
        int v;
        do{
            v = st.top();
            st.pop();
            scc[scc_cnt].push_back(v);
            belong[v] = scc_cnt;
            instack[v] = 0;
        } while(u != v);
        sort(scc[scc_cnt].begin(), scc[scc_cnt].end());
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    edges.resize(n+1), dfn.resize(n+1), low.resize(n+1);
    instack.resize(n+1, false), scc.resize(n+1), belong.resize(n+1);
    for(int i = 0;i < m;i++) {
        int u, v;
        cin >> u >> v;
        edges[u].push_back(v);
    }
    for(int i = 1;i <= n;i++) {
        if(!dfn[i]) tarjan(i);
    }
    cout << scc_cnt << endl;
    vector<int>output(scc_cnt+1, 0);
    for(int i = 1;i <= n;i++) {
        int scc_id = belong[i];
        if(output[scc_id]) continue;
        output[scc_id] = true;
        for(auto v : scc[scc_id]) cout << v << ' ';
        cout << '\n';
    }
    return 0;
}