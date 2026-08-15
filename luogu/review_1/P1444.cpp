#include<bits/stdc++.h>
using namespace std;

struct position{
    int x;
    int y;
};
vector<position>wormhole;
vector<int>righthole;
vector<int>partner;
int n;
int ans = 0;

bool hascircle() {
    //从第i个虫洞出发
    for(int i = 1;i <= n;i++) {
        int cur = i;
        //一共有n个虫洞,所以最多跳n下,如果跳了n下还没出来,说明出现了循环
        for(int step = 1;step <= n;step++) {
            //跳到配对虫洞,在走到配对虫洞的righthole
            int paired = partner[cur];
            cur = righthole[paired];
            if(cur == 0) break;
        }
        if(cur != 0) {
            return true;
        }
    }
    //要把所有起点遍历过后都没有循环才是没有循环
    return false;
}

void dfs() {
    //寻找第一个没有配对的虫洞
    int first = 0;
    for(int i = 1;i <= n;i++) {
        if(partner[i] == 0) {
            first = i;
            break;
        }
    }
    //如果全部已经配对完成进行检查是否存在循环,检查完之后返回
    if(first == 0) {
        ans += hascircle() ? 1 : 0;
        return;
    }
    //再寻找一个没有配对的虫洞和first进行配对
    for(int i = first+1;i <= n;i++) {
        if(partner[i] != 0) continue;
        partner[i] = first;
        partner[first] = i;
        dfs();
        //回溯
        partner[i] = 0;
        partner[first] = 0;
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    wormhole.resize(n+1);
    for(int i = 1;i <= n;i++) cin >> wormhole[i].x >> wormhole[i].y;
    partner.resize(n+1, 0);
    righthole.resize(n+1);
    //初始化每个虫洞在x方向上最接近的虫洞的下标
    for(int i = 1;i <= n;i++) {
        int bestx = INT_MAX;
        for(int j = 1;j <= n;j++) {
            if(wormhole[j].y == wormhole[i].y &&
                wormhole[j].x > wormhole[i].x &&
                wormhole[j].x < bestx) {
                    bestx = wormhole[j].x;
                    righthole[i] = j;
                }
        }
    }
    dfs();
    cout << ans;
    return 0;
}