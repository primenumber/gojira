#include <cmath>
#include <cstdlib>

#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

constexpr long double PI = std::acos(-1.0);
constexpr long double EPS = 1e-12;
constexpr long double INF = 1e+12;

std::string getexpr(long double v, const std::vector<std::vector<long double>> &ary, int index) {
  if (index == 1) return "π";
  for (int i = 1; i < index; ++i) {
    int j = index - i;
    for (long double lhs : ary[i-1]) {
      for (long double rhs : ary[j-1]) {
        if (std::abs(lhs + rhs - v) < EPS)
          return "(" + getexpr(lhs, ary, i) + "+" + getexpr(rhs, ary, j) + ")";
        if (std::abs(lhs - rhs - v) < EPS)
          return "(" + getexpr(lhs, ary, i) + "-" + getexpr(rhs, ary, j) + ")";
        if (std::abs(lhs * rhs - v) < EPS)
          return "(" + getexpr(lhs, ary, i) + "*" + getexpr(rhs, ary, j) + ")";
        if (std::abs(lhs / rhs - v) < EPS)
          return "(" + getexpr(lhs, ary, i) + "/" + getexpr(rhs, ary, j) + ")";
        if (std::abs(std::pow(lhs, rhs) - v) < EPS)
          return "(" + getexpr(lhs, ary, i) + "^" + getexpr(rhs, ary, j) + ")";
      }
    }
  }
  throw "bad";
}

std::vector<std::vector<long double>> make_ary(int depth) {
  std::vector<std::vector<long double>> nums(depth);
  nums[0].emplace_back(PI);
  for (int i = 2; i <= depth; ++i) {
    for (int j = 1; j < i; ++j) {
      int k = i - j;
      for (long double lhs : nums[j-1]) {
        for (long double rhs : nums[k-1]) {
          nums[i-1].push_back(lhs + rhs);
          nums[i-1].push_back(lhs - rhs);
          nums[i-1].push_back(lhs * rhs);
          nums[i-1].push_back(lhs / rhs);
          nums[i-1].push_back(std::pow(lhs, rhs));
        }
      }
    }
    nums[i-1].erase(std::remove_if(std::begin(nums[i-1]), std::end(nums[i-1]),
        [] (long double val) {
          return std::abs(val) < EPS || std::abs(val) > INF || std::isnan(val);
        }), std::end(nums[i-1]));
  }
  return nums;
}

void solve(int v, const std::vector<std::vector<long double>> &ary) {
  for (int i = 0; i < ary.size(); ++i) {
    for (long double val : ary[i]) {
      if (v == std::floor(val)) {
        std::cout << i+1 << " " << getexpr(val, ary, i+1) << std::endl;
        return;
      }
    }
  }
}

void output(const std::vector<std::vector<long double>> &ary) {
  std::set<int64_t> s;
  for (int i = 0; i < ary.size(); ++i) {
    for (long double val : ary[i]) {
      int64_t fv = std::floor(val);
      if (s.find(fv) == std::end(s)) {
        s.insert(fv);
        std::cout << fv << " " << i+1 << " " << getexpr(val, ary, i+1) << std::endl;
      }
    }
  }
}

int main(int argc, char **argv) {
  int dep = 7;
  auto ary = make_ary(dep);
  if (argc == 1) output(ary);
  else solve(atoi(argv[1]), ary);
  return 0;
}
