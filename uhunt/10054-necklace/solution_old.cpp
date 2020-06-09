#include <algorithm>
#include <list>
#include <map>
#include <utility>
#include <iostream>
#include <vector>

#undef NDEBUG
#include <cassert>

/*
static std::multimap<int, int> edge_map;

std::list<std::pair<int, int>> eulerify(int start_color = -1) {
    // assumes |edge_map| is connected and every vertex has even degree
    std::list<std::pair<int, int>> path;

    // the graph must be non-empty, and there must be at least 2 edges (since every vertex has even degree).
    assert(edge_map.size() >= 4);

    std::multimap<int, int>::iterator it;
    if (start_color == -1) {
        it = edge_map.begin();
    } else {
        it = edge_map.find(start_color);
        assert(it != edge_map.end());
    }

    int first_color = it->first;

    int src_color, dst_color;
    do {
        src_color = it->first;
        dst_color = it->second;

        // take first edge with start color
        path.emplace_back(src_color, dst_color);

        // remove edge entries (both src -> dst and dst -> src)
        edge_map.erase(it);
        bool removed_opposite = false;
        auto range = edge_map.equal_range(dst_color);
        for (auto it = range.first; it != range.second; ++it) {
            if (it->second == src_color) {
                edge_map.erase(it);
                removed_opposite = true;
                break;
            }
        }
        assert(removed_opposite);

        // continue at any edge starting from the second color
        it = edge_map.find(dst_color);
    } while (dst_color != first_color);

    // sanity check the path
    assert(path.size() >= 2);
    assert(path.front().first == first_color);
    assert(path.back().second == first_color);

    // return path if there's no edges left. it should be the eulerian path
    if (edge_map.size() == 0) {
        return path;
    }

    // the leftover graph should have at least 2 edges
    assert(edge_map.size() >= 4);

    // pick color in |path| with leftover edge
    auto intersection = path.begin();
    for (; intersection != path.end(); ++intersection) {
        auto it = edge_map.find(intersection->first);
        if (it != edge_map.end()) {
            break;
        }
    }

    assert(intersection != path.end());
    int color = intersection->first;

    // construct another loop using remaining edges
    std::list<std::pair<int, int>> detour = eulerify(color);

    assert(detour.front().first == intersection->first);
    assert(detour.back().second == intersection->first);

    // merge loops
    auto merge_point = intersection;
    ++merge_point;
    path.splice(merge_point, std::move(detour));

    return path;
}

*/

static const int MAX_COLOR = 50;
static int adjacency[MAX_COLOR+1][MAX_COLOR+1] = {0};

int first_adjacent(int src) {
  for (int i = 1; i <= MAX_COLOR; ++i) {
    if (adjacency[src][i] > 0)
      return i;
  }

  return -1;
}

void remove_edge(int a, int b) {
  assert(adjacency[a][b] == adjacency[b][a]);
  assert(adjacency[a][b] > 0);
  adjacency[a][b] -= 1;
  adjacency[b][a] -= 1;
}

std::vector<int> eulerify() {
  std::vector<int> path_colors;
  std::vector<int> color_stack;

  for (int i = 1; i <= MAX_COLOR; ++i) {
    if (first_adjacent(i) != -1) {
      color_stack.push_back(i);
      break;
    }
  }
  assert(color_stack.size() == 1);

  while(color_stack.size() > 0) {
    int dst = first_adjacent(color_stack.back());
    if (dst == -1) {
      path_colors.push_back(color_stack.back());
      color_stack.pop_back();
    } else {
      remove_edge(color_stack.back(), dst);
      color_stack.push_back(dst);
    }
  }

  for (int i = 1; i <= MAX_COLOR; ++i) {
    for (int j = 1; j <= MAX_COLOR; ++j) {
      if (adjacency[i][j] > 0) {
        path_colors.clear();
      }
    }
  }

  return path_colors;
}

bool connected() {
  bool exists[MAX_COLOR+1] = {0};
  for (int i = 1; i <= MAX_COLOR; ++i) {
    for (int j = 1; j <= MAX_COLOR; ++j) {
      exists[i] = true;
      exists[j] = true;
    }
  }

  bool seen[MAX_COLOR+1] = {0};
  std::vector<int> stack;

  if (int i = 1; i <= MAX_COLOR; ++i) {
    if (first_adjacent(i) != -1) {
      stack.push_back(i);
      break;
    }
  }

  while (!stack.empty()) {
    int color = stack.back();
    seen[color] = true;
  }
}

int main() {
  int case_count;
  std::cin >> case_count;
  for (int c = 1; c <= case_count; ++c) {
    if (c > 1)
      std::cout << "\n";

    int num_beads;
    std::cin >> num_beads;

    std::vector<std::pair<int, int>> beads;

    for (int bead = 0; bead < num_beads; ++bead) {
      int a, b;
      std::cin >> a >> b;
      beads.emplace_back(a, b);
      adjacency[a][b] += 1;
      adjacency[b][a] += 1;
    }

    std::sort(beads.begin(), beads.end());

    bool possible = true;
    for (int i = 1; i <= MAX_COLOR; ++i) {
      int edge_count = 0;
      for (int j = 1; j <= MAX_COLOR; ++j)
        edge_count += adjacency[i][j];
      if (edge_count % 2 != 0)
        possible = false;
    }

    std::vector<int> vertices;
    if (possible) {
      vertices = eulerify();
      if (vertices.size() == 0)
        possible = false;
    }

    std::cout << "Case #" << c << "\n";

    if (possible) {
      assert(vertices.size()-1 == num_beads);
      assert(vertices.front() == vertices.back());
      for (int i = 1; i < vertices.size(); ++i) {
        std::cout << vertices[i-1] << " " << vertices[i] << "\n";
      }
    } else {
      std::cout << "some beads may be lost\n";
    }
  }
}
