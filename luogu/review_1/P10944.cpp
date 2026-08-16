#include<bits/stdc++.h>
using namespace std;

vector<vector<int>>edges;
vector<int>dfn, low, instack, belong;
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
    if(dfn[u] == low[u]){
        scc_cnt++;
        int v;
        do {
            v = st.top();
            st.pop();
            instack[v] = 0;
            belong[v] = scc_cnt;
        } while(u != v);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t--) {
        int n, m;
        cin >> n >> m;
        edges.assign(n+1, vector<int>()), dfn.assign(n+1, 0);
        low.assign(n+1, 0), instack.assign(n+1, 0), belong.assign(n+1, 0);
        scc_cnt = 0, tot = 0;
        for(int i = 0;i < m;i++) {
            int u, v;
            cin >> u >> v;
            edges[u].push_back(v);
        }
        for(int i = 1;i <= n;i++) {
            if(!dfn[i]) tarjan(i);
        }
        //也就是构造的dag的拓扑排序只能有一种
        vector<vector<int>>dag(scc_cnt+1);
        vector<int>indeg(scc_cnt+1);
        for(int u = 1;u <= n;u++) {
            for(auto v : edges[u]) {
                if(belong[u] != belong[v]) {
                    dag[belong[u]].push_back(belong[v]);
                    indeg[belong[v]]++;
                }
            }
        }
        queue<int>q;
        for(int i = 1;i <= scc_cnt;i++) {
            if(indeg[i] == 0) q.push(i);
        }
        bool flag = true;
        while(!q.empty()) {
            if(q.size() > 1) {
                flag = false;
                break;
            }
            int u = q.front();
            q.pop();
            for(auto v : dag[u]) {
                if(indeg[v]) {
                    indeg[v]--;
                    if(indeg[v] == 0) q.push(v);
                }
            }
        }
        if(flag) {
            cout << "Yes" << '\n';
        } else {
            cout << "No" << '\n';
        }
    }
    return 0;
}