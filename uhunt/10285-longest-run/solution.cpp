#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

static int R, C;
static int heightmap[100][100];
static bool visited[100][100];
static int lengths[100][100];

enum direction {
  UP = 0,
  DOWN,
  LEFT,
  RIGHT
};

bool has_edge_from(int r, int c, direction dir) {
  static int r_off[4] = {
    -1, // UP
    1,  // DOWN
    0,  // LEFT
    0   // RIGHT
  };

  static int c_off[4] = {
    0,  // UP
    0,  // DOWN
    -1, // LEFT
    1,  // RIGHT
  };


  int r_adj = r + r_off[dir];
  int c_adj = c + c_off[dir];

  if (r_adj < 0 || r_adj >= R || c_adj < 0 || c_adj >= C)
    return false;

  if (visited[r_adj][c_adj])
    return false;

  return heightmap[r][c] < heightmap[r_adj][c_adj];
}

bool is_source(int r, int c) {
  return !(has_edge_from(r, c, UP) || has_edge_from(r, c, DOWN) || has_edge_from(r, c, LEFT) || has_edge_from(r, c, RIGHT));
}

int main() {
  int N;
  std::cin >> N;

  for (int tc = 1; tc <= N; ++tc) {
    std::string name;
    std::cin >> name >> R >> C;

    for (int i = 0; i < R; ++i) {
      for (int j = 0; j < C; ++j) {
        std::cin >> heightmap[i][j];
      }
    }

    for (int i = 0; i < R; ++i) {
      for (int j = 0; j < C; ++j) {
        visited[i][j] = false;
        lengths[i][j] = 0;
      }
    }

    std::vector<std::pair<int, int>> toposort;
    std::vector<std::pair<int, int>> candidates;

    for (int i = 0; i < R; ++i) {
      for (int j = 0; j < C; ++j) {
        if (is_source(i, j))
          candidates.emplace_back(i, j);
      }
    }

    while (!candidates.empty()) {
      int r = candidates.back().first;
      int c = candidates.back().second;
      candidates.pop_back();

      if (visited[r][c])
        continue;
      visited[r][c] = true;

      toposort.emplace_back(r, c);

      for (int r_adj : {r-1, r+1}) {
        if (r_adj < 0 || r_adj >= R)
          continue;

        if (is_source(r_adj, c) && !visited[r_adj][c])
          candidates.emplace_back(r_adj, c);
      }

      for (int c_adj : {c-1, c+1}) {
        if (c_adj < 0 || c_adj >= C)
          continue;

        if (is_source(r, c_adj) && !visited[r][c_adj])
          candidates.emplace_back(r, c_adj);
      }
    }

    for (int i = 0; i < R; ++i) {
      for (int j = 0; j < C; ++j) {
        assert(visited[i][j]);
      }
    }

    assert(toposort.size() == R*C);

    for (auto coord : toposort) {
      int r = coord.first;
      int c = coord.second;

      for (int r_adj : {r-1, r+1}) {
        if (r_adj < 0 || r_adj >= R)
          continue;
        if (heightmap[r_adj][c] > heightmap[r][c])
          lengths[r][c] = std::max(lengths[r][c], 1+lengths[r_adj][c]);
      }

      for (int c_adj : {c-1, c+1}) {
        if (c_adj < 0 || c_adj >= C)
          continue;
        if (heightmap[r][c_adj] > heightmap[r][c])
          lengths[r][c] = std::max(lengths[r][c], 1+lengths[r][c_adj]);
      }
    }

    int longest = 0;
    for (int i = 0; i < R; ++i) {
      for (int j = 0; j < C; ++j) {
        longest = std::max(longest, lengths[i][j]);
      }
    }

    std::cout << name << ": " << longest+1 << "\n";
  }
}
