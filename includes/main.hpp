#ifndef MAIN_HPP
#define MAIN_HPP

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

#endif