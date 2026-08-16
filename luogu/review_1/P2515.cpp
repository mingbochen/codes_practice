#include<bits/stdc++.h>
using namespace std;

vector<vector<int>>edges;
vector<int>dfn, low, belong, scc_weight, scc_value, instack;
vector<int>weight, value, d;

stack<int>st;
int tot = 0, scc_cnt = 0;
int n, m;

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
    if(low[u] == dfn[u]){
        scc_cnt++;
        int v;
        do {
            v = st.top();
            st.pop();
            instack[v] = 0;
            scc_weight[scc_cnt] += weight[v];
            scc_value[scc_cnt] += value[v];
            belong[v] = scc_cnt;
        } while(u != v);
    }
}

vector<vector<int>>dp; //dp[u][j]表示已经选择u的情况下，在u的子树中最多使用j空间的最大价值
vector<vector<int>>dag;

void dfs(int u) {
    if(u != 0) {
        for(int j = scc_weight[u];j <= m;j++) dp[u][j] = scc_value[u];
    } else {
        for(int j = 0;j <= m;j++) dp[u][j] = 0;
    }
    //对于u的子树更新u的dp值
    for(auto v : dag[u]) {
        dfs(v);
        //倒序枚举当前已经分配给u的容量
        //因为每个子节点只能使用一次，dp[u][i+j]要用dp[u][i]来更新
        //所以要确保dp[u][i]是来自以其他子树而非当前子树
        for(int i = m;i >= 0;i--) {
            if(dp[u][i] == -1) continue;
            //枚举分配给子树v的容量
            for(int j = 0;j + i <= m;j++) {
                if(dp[v][j] == -1) continue;
                dp[u][i+j] = max(dp[u][i+j], dp[u][i] + dp[v][j]);
            }
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> m;
    edges.resize(n+1), dfn.resize(n+1), low.resize(n+1), belong.resize(n+1);
    scc_weight.resize(n+1), scc_value.resize(n+1), instack.resize(n+1);
    weight.resize(n+1), value.resize(n+1), d.resize(n+1);
    for(int i = 1;i <= n;i++) cin >> weight[i];
    for(int i = 1;i <= n;i++) cin >> value[i];
    for(int i = 1;i <= n;i++) {
        cin >> d[i];
        if(d[i] != 0) edges[d[i]].push_back(i);
    }
    for(int i = 1;i <= n;i++) {
        if(!dfn[i]) tarjan(i);
    }
    dag.resize(scc_cnt+1);
    vector<int>indeg(scc_cnt+1);
    for(int u = 1;u <= n;u++) {
        for(auto v : edges[u]) {
            if(belong[u] != belong[v]) {
                dag[belong[u]].push_back(belong[v]);
                indeg[belong[v]]++;
            }
        }
    }
    //添加虚拟源节点
    scc_weight[0] = 0, scc_value[0] = 0;
    for(int i = 1;i <= scc_cnt;i++) {
        if(indeg[i]==0) dag[0].push_back(i);
    }
    dp.resize(scc_cnt+1, vector<int>(m+1, -1));
    dfs(0);
    cout << dp[0][m];
    return 0;
}