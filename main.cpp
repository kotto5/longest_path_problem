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

double dfs(const vector<vector<edge> > &G, vector<bool> &seen, vector<int> &next, int v, int prev = -1) {
    seen[v] = true;
    vector<bool> seen_longest(seen);
    vector<int> next_longest(next);
    double ans = 1.0 / 0.0;
    for (auto nv: G[v]) {
        if (nv.to == prev)
            continue;
        else if (seen[nv.to])
        {
            if (nv.leng < ans) {
                ans = nv.leng;
                next_longest = next;
                next_longest[v] = nv.to;
            }
            continue;
        }
        vector<int> next_tmp(next);
        vector<bool> seen_tmp(seen);
        double weight = dfs(G, seen_tmp, next_tmp, nv.to, v) + nv.leng;
        cout << "root" << v << " next_copy: " << nv.to << " tmp: " << weight << " nv leng: " << nv.leng << " weight + nv.leng: " << weight + nv.leng << endl;
        if (weight < ans) {
            ans = weight;
            next_longest = next_tmp;
            next_longest[v] = nv.to;
            seen_longest = seen_tmp;
        }
    }
    next = next_longest;
    seen = seen_longest;
    if (ans == 1.0 / 0.0)
        ans = 0.0;
    return ans;
}

int main() {
    vector<vector<edge> > graph; // graph[v]: 頂点vから出る辺の集合
    // input: init graph
    {
        int         graphSize = 0;
        vector<edge> edges;
        cin.imbue(locale(cin.getloc(), new comma_is_space));
        while (1) {
            int a, b;
            double c;
            cin >> a >> b >> c;
            // -1 * c: 最長パスを求めるため
            c = -1.0 * c;
            edges.push_back({a, b, c});
            if (graphSize < a)
                graphSize = a;
            if (graphSize < b)
                graphSize = b;
            if (cin.eof())
                break;
        }
        graphSize += 1;
        graph.resize(graphSize);
        for (auto v: edges) {
            graph[v.from].push_back(v);
            graph[v.to].push_back({v.to, v.from, v.leng});
        }
    }
    int graphSize = graph.size();
    // main algorithm
    {
        double  longestLength = -1.0 / 0.0;
        vector<int> longestPath(graphSize, -1);
        int longestPathStart = -1;
        for (int i = 0; i < graphSize; i++) {
            cout << "============== root: " << i << " ==============" << endl;
            vector<bool> seen(graphSize, false);
            vector<int> next(graphSize, -1);
            double len = dfs(graph, seen, next, i) * -1.0;
            if (longestLength < len) {
                longestLength = len;
                longestPath = next;
                longestPathStart = i;
            }
            cout << endl;
        }
        cout <<  longestLength << endl;
        cout << "======= root: " << longestPathStart << " =======" << endl;
        vector<bool> printed(graphSize, false);
        int v = longestPathStart;
        while (v != -1) {
            cout << v << endl;
            if (printed[v])
                break;
            printed[v] = true;
            v = longestPath[v];
        }
        cout << "-----------------" << endl;
        for (int j = 0; j < graphSize; j++) {
            cout << "longestPath[" << j << "]: " << longestPath[j] << endl;
        }
    }
    return 0;
}
