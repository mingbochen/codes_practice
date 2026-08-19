#include<bits/stdc++.h>
using namespace std;

vector<vector<int>>enm;
vector<int>vis;
vector<int>ans;
int n, m, tot = 0, a = 0;
void dfs(int k) {
    if(k > n) {
        if(tot > a) {
            a = tot;
            for(int i = 1;i <= n;i++) ans[i] = vis[i];
        }
        return;
    }
    //检查第k个人是否能选
    bool flag = true;
    for(int i = 1;i <= n;i++) {
        if(vis[i] && enm[i][k]) {
            //已经选择i，且i和k是仇人
            flag = false;
            break;
        } 
    }
    //第k个人有两种选择，一种是被选，一种是不被选
    //选择第k个人
    if(flag) {
        vis[k] = 1;
        tot++;
        dfs(k+1);
        //回溯
        tot--;
        vis[k] = 0;
    }
    //不选择第k个人
    dfs(k+1);
    return;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    //深搜
    cin >> n >> m;
    vis.resize(n+1, 0), ans.resize(n+1, 0);
    enm.resize(n+1, vector<int>(n+1, 0));
    for(int i = 0;i < m;i++) {
        int u, v;
        cin >> u >> v;
        enm[u][v] = enm[v][u] = 1;
    }
    dfs(1);
    cout << a << endl;
    for(int i = 1;i <= n;i++) cout << ans[i] << ' ';
    return 0; 
}