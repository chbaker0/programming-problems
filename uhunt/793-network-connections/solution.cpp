#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <cassert>
#include <cstdio>

#define NDEBUG

struct SetElem {
  int parent;
  int rank;
};

static std::vector<SetElem> union_find;

void init_union_find(int sz) {
  union_find.resize(sz);

  for (int i = 0; i < sz; ++i) {
    union_find[i].parent = i;
    union_find[i].rank = 0;
  }
}

int& parent(int i) {
  assert(i >= 0);
  assert(i < union_find.size());
  return union_find[i].parent;
}

int& rank(int i) {
  assert(i >= 0);
  assert(i < union_find.size());
  return union_find[i].rank;
}

int find(int i) {
  while (parent(i) != i) {
    parent(i) = parent(parent(i));
    i = parent(i);
  }
  return i;
}

void combine(int x, int y) {
  int x_root = find(x);
  int y_root = find(y);

  if (x_root == y_root)
    return;

  if (rank(x_root) < rank(y_root))
    std::swap(x_root, y_root);

  parent(y_root) = x_root;
  if (rank(x_root) == rank(y_root))
    rank(x_root) += 1;
}

int main() {
  int case_count;
  std::cin >> case_count;

  std::string line;

  for (int tc = 0; tc < case_count; ++tc) {
    int computer_count;
    std::cin >> computer_count;
    init_union_find(computer_count);

    getline(std::cin, line);

    int succ = 0, fail = 0;

    while (getline(std::cin, line) && !line.empty()) {
      char cmd;
      int ci, cj;
      std::sscanf(line.c_str(), "%c %d %d", &cmd, &ci, &cj);

      ci -= 1;
      cj -= 1;

      if (cmd == 'c') {
        combine(ci, cj);
      } else {
        assert(cmd == 'q');
        if (find(ci) == find(cj))
          succ += 1;
        else
          fail += 1;
      }
    }

    if (tc > 0)
      std::cout << "\n";
    std::cout << succ << "," << fail << "\n";
  }
}
