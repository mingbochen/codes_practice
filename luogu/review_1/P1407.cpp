#include<bits/stdc++.h>
using namespace std;

vector<vector<int>>edges;
//用于string->int的映射
unordered_map<string, int>id;
vector<int>dfn, low, instack;
vector<int>belong;
stack<int>st;
int tot = 0, scc_cnt = 0;
int idx = 0;
int getid(const string& a) {
    if(id.find(a) == id.end()) {
        id[a] = ++idx;
    }
    return id[a];
}

void tajan(int u) {
    dfn[u] = low[u] = ++tot;
    st.push(u);
    instack[u] = 1;
    for(auto v : edges[u]) {
        if(!dfn[v]) {
            tajan(v);
            low[u] = min(low[u], low[v]);
        } else if(instack[v]){
            low[u] = min(low[u], dfn[v]);
        }
    }
    if(dfn[u] == low[u]) {
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
    int n, m;
    cin >> n;
    edges.resize(2*n+1);
    dfn.resize(2*n+1), low.resize(2*n+1), instack.resize(2*n+1);
    belong.resize(2*n+1);
    vector<pair<int, int>>couple(n);
    for(int i = 0;i < n;i++) {
        string g, b;
        cin >> g >> b;
        int gid = getid(g);
        int bid = getid(b);
        edges[gid].push_back(bid);
        couple[i] = {gid, bid};
    }
    cin >> m;
    for(int i = 0;i < m;i++) {
        string g, b;
        cin >> g >> b;
        int gid = getid(g);
        int bid = getid(b);
        edges[bid].push_back(gid);
    }
    for(int i = 1;i <= idx;i++) {
        if(!dfn[i]) {
            tajan(i);
        }
    }
    for(auto[g, b] : couple) {
        if(belong[g] == belong[b]) {
            cout << "Unsafe";
        } else {
            cout << "Safe";
        }
        cout << '\n';
    }
}