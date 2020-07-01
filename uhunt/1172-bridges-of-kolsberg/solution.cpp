#include <iostream>
#include <string>
#include <map>

struct city {
  unsigned int os;
  unsigned int tv;
};

static city north_cities[1000];
static city south_cities[1000];
static unsigned int num_north_cities;
static unsigned int num_south_cities;

struct sol {
  int val;
  unsigned int bridges;
};

static sol opt[1000][1000];

bool sol_less(const sol& lhs, const sol& rhs) {
  if (lhs.val < rhs.val)
    return true;
  else if (lhs.val > rhs.val)
    return false;
  else
    return lhs.bridges > rhs.bridges;
}

int main() {
  unsigned int num_cases;
  std::cin >> num_cases;

  std::string os_name;
  std::string city_name;
  while (num_cases--) {
    unsigned int next_os = 1;
    std::map<std::string, unsigned int> os_map;

    std::cin >> num_north_cities;
    for (unsigned int i = 0; i < num_north_cities; ++i) {
      std::cin >> city_name >> os_name >> north_cities[i].tv;
      unsigned int& os = os_map[os_name];
      if (os == 0)
        os = next_os++;
      north_cities[i].os = os;
    }

    std::cin >> num_south_cities;
    for (unsigned int i = 0; i < num_south_cities; ++i) {
      std::cin >> city_name >> os_name >> south_cities[i].tv;
      unsigned int& os = os_map[os_name];
      if (os == 0)
        os = next_os++;
      south_cities[i].os = os;
    }

    if (num_north_cities == 0 || num_south_cities == 0) {
      std::cout << "0 0\n";
      continue;
    }

    if (north_cities[0].os == south_cities[0].os) {
      opt[0][0].val = north_cities[0].tv + south_cities[0].tv;
      opt[0][0].bridges = 1;
    } else {
      opt[0][0].val = 0;
      opt[0][0].bridges = 0;
    }

    for (unsigned int i = 0; i < num_north_cities; ++i) {
      for (unsigned int j = 0; j < num_south_cities; ++j) {
        if (i == 0 && j == 0)
          continue;

        opt[i][j] = {};
        if (north_cities[i].os == south_cities[j].os) {
          if (i > 0 && j > 0)
            opt[i][j] = opt[i-1][j-1];

          opt[i][j].val += north_cities[i].tv + south_cities[j].tv;
          opt[i][j].bridges += 1;
        }

        if (i > 0 && sol_less(opt[i][j], opt[i-1][j]))
          opt[i][j] = opt[i-1][j];

        if (j > 0 && sol_less(opt[i][j], opt[i][j-1]))
          opt[i][j] = opt[i][j-1];
      }
    }

    sol& fnl = opt[num_north_cities-1][num_south_cities-1];
    std::cout << fnl.val << ' ' << fnl.bridges << '\n';
  }
}
