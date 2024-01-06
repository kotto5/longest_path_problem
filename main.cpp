#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
#include <string>
#include <cmath>
#include <locale>

using namespace std;
using Graph = vector<vector<int> >;

struct edge {
    int from;   // 辺の始点
    int to;     // 辺の終点
    double leng;   // 辺の長さ
    bool    operator<(edge &other) {
        return ((this->leng < other.leng) || 
            (this->leng == other.leng && this->to < other.to));
    }
    bool    operator>(edge &other) {
        return ((this->leng > other.leng) || 
            (this->leng == other.leng && this->to > other.to));
    }
};


struct comma_is_space : std::ctype<char> {
  comma_is_space() : std::ctype<char>(get_table()) {}
  static mask const* get_table()
  {
    static mask rc[table_size];
    rc[','] = std::ctype_base::space;
    rc[' '] = std::ctype_base::space;
    rc['\n'] = std::ctype_base::space;
    rc['\r'] = std::ctype_base::space;
    return &rc[0];
  }
};

double dfs(vector<vector<edge> > &G, int v, vector<bool> &used, vector<double> &dist, vector<int> &next, int parent = -1) {
    used[v] = true;
    double ret = 1.0 / 0.0;
    for (auto nv: G[v]) {
        if (nv.to == parent)
            continue;
        if (used[nv.to])
        {
            // cout << "test 2 next: " << next[v] << endl;
            if (ret > nv.leng) {
                ret = nv.leng;
                next[v] = nv.to;
            }
            continue;
        }
        int tmp = dfs(G, nv.to, used, dist, next, v);
        cout << "root" << v << " next: " << nv.to << " tmp: " << tmp << " nv leng: " << nv.leng << " tmp + nv.leng: " << tmp + nv.leng << endl;
        if (ret > tmp + nv.leng) {
            ret = tmp + nv.leng;
            next[v] = nv.to;
        }
    }
    if (ret == 1.0 / 0.0)
        ret = 0.0;
    return ret;
}

// 最長路問題
// the longest path problem
// path contain cycle
// 無向グラフの最長路問題
// 最大の経路のパスを出力する
int main() {
    vector<edge> E;
    int         N = 0;
    cin.imbue(locale(cin.getloc(), new comma_is_space));
    while (1) {
        int a, b;
        double c;
        cin >> a >> b >> c;
        cout << a << " " << b << " " << c << endl;
        E.push_back({a, b, c});
        if (N < a)
            N = a;
        if (N < b)
            N = b;
        if (cin.eof())
            break;
    }
    for (auto v: E) {
        cout << v.from << " " << v.to << " " << v.leng << endl;
    }
    cout << N << endl;
    vector<vector<edge> > G(N + 1);
    for (auto v: E) {
        G[v.from].push_back(v);
        G[v.to].push_back({v.to, v.from, v.leng});
    }
    cout << "--------- G is ! --------" << endl;
    for (int i = 0; i < N + 1; ++i) {
        for (auto v: G[i]) {
            cout << v.from << " " << v.to << " " << v.leng << endl;
        }
    }

    // main algorithm
    {
        vector<bool> used(N + 1, false);
        vector<double> dist(N + 1, 1.0 / 0.0);
        dist[1] = 0;
        vector<int> next(N + 1, -1);
        cout << "-----------------" << endl;
        cout << dfs(G, 1, used, dist, next) << endl;
        cout << 1 << endl;
        int v = next[1];
        while (v != -1 && v != 1) {
            cout << v << endl;
            v = next[v];
        }
        if (v == 1)
            cout << 1 << endl;
    }
    return 0;
}
