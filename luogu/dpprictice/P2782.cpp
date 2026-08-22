#include<bits/stdc++.h>
using namespace std;

bool comp(const pair<int, int>& a, const pair<int, int>& b) {
    return a.first < b.first;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<pair<int, int>>par(n);
    for(int i = 0;i < n;i++) {
        cin >> par[i].first >> par[i].second;
    }
    sort(par.begin(), par.end(), comp);
    //求最长的递增子序列的长度
    vector<int>tails;
    for(int i = 0;i < n;i++) {
        int x = par[i].second;
        auto it = upper_bound(tails.begin(), tails.end(), x);
        if(it == tails.end()) {
            tails.push_back(x);
        } else {
            *it = x;
        }
    }
    cout << tails.size();
}