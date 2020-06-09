#include <algorithm>
#include <deque>
#include <list>
#include <map>
#include <string>
#include <utility>
#include <iostream>
#include <iterator>
#include <vector>

#undef NDEBUG
#include <cassert>

static const int MAX_COLOR = 50;
static int adjacency[MAX_COLOR+1][MAX_COLOR+1];

static int first_adjacent[MAX_COLOR+1];

void add_edge(int a, int b) {
  assert(adjacency[a][b] == adjacency[b][a]);
  adjacency[a][b] += 1;
  adjacency[b][a] += 1;
  assert(adjacency[a][b] > 0);

  if (first_adjacent[a] == -1 || b < first_adjacent[a])
    first_adjacent[a] = b;

  if (first_adjacent[b] == -1 || a < first_adjacent[b])
    first_adjacent[b] = a;
}

void update_first_adjacent(int src, int old_dst) {
  if (first_adjacent[src] < old_dst)
    return;
  assert(first_adjacent[src] == old_dst);

  first_adjacent[src] = -1;
  for (int i = old_dst+1; i <= MAX_COLOR; ++i) {
    if (adjacency[src][i] > 0) {
      first_adjacent[src] = i;
      return;
    }
  }
}

void remove_edge(int a, int b) {
  assert(adjacency[a][b] == adjacency[b][a]);
  adjacency[a][b] -= 1;
  adjacency[b][a] -= 1;
  assert(adjacency[a][b] >= 0);

  assert(first_adjacent[a] != -1);
  assert(first_adjacent[b] != -1);

  if (adjacency[a][b] == 0) {
    update_first_adjacent(a, b);
    update_first_adjacent(b, a);
  }
}

void build_cycle(std::deque<int>& path, int start_color) {
  int cur_color = start_color;
  do {
    int next_color = first_adjacent[cur_color];
    assert(next_color != -1);
    path.push_back(next_color);
    remove_edge(cur_color, next_color);
    cur_color = next_color;
  } while (cur_color != start_color);
}

std::deque<int> eulerify() {
  std::deque<int> path;

  // use any color present in graph as start color.
  for (int i = 1; i <= MAX_COLOR; ++i) {
    if (first_adjacent[i] != -1) {
      path.push_back(i);
      break;
    }
  }

  assert(path.size() == 1);

  int rotations = 0;
  while (true) {
    build_cycle(path, path.back());
    assert(path.size() >= 2);

    // rotate the path until a vertex with remaining edges is at the end. if
    // there are none, we are done.
    while (rotations < path.size() && first_adjacent[path.back()] == -1) {
      path.push_front(path.back());
      path.pop_back();
      ++rotations;
    }

    if (rotations == path.size()) {
      return path;
    }
  }
}

int main() {
  // ignore case count
  std::string trash;
  getline(std::cin, trash);

  int test_case = 0;
  int bead_count;
  while (std::cin >> bead_count) {
    ++test_case;

    for (int i = 0; i <= MAX_COLOR; ++i)
      for (int j = 0; j <= MAX_COLOR; ++j)
        adjacency[i][j] = 0;

    for (int i = 0; i <= MAX_COLOR; ++i)
      first_adjacent[i] = -1;

    for (int bead = 0; bead < bead_count; ++bead) {
      int a = 0, b = 0;
      std::cin >> a >> b;
      add_edge(a, b);
    }

    bool possible = true;

    // check all vertices have even degree
    for (int color = 1; color <= MAX_COLOR; ++color) {
      int incident_edges = 0;
      for (int dest = 1; dest <= MAX_COLOR; ++dest)
        incident_edges += adjacency[color][dest];

      if ((incident_edges % 2) != 0) {
        possible = false;
        break;
      }
    }

    std::deque<int> cycle;

    if (possible) {
      cycle = eulerify();

      // check if there are any leftover edges. if so, the graph wasn't connected.
      for (int color = 1; color <= MAX_COLOR; ++color) {
        if (first_adjacent[color] != -1)
          possible = false;
      }
    }

    if (test_case > 1)
      std::cout << "\n";

    std::cout << "Case #" << test_case << "\n";

    if (possible) {
      assert(cycle.size() == bead_count+1);
      for (int i = 1; i < cycle.size(); ++i) {
        std::cout << cycle[i-1] << " " << cycle[i] << "\n";
      }
    } else {
      std::cout << "some beads may be lost\n";
    }
  }
}
