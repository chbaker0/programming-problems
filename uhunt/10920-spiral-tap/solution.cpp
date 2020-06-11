#include <iostream>
#include <cmath>

struct coord {
  long long int x;
  long long int y;
};

coord tap(long long int sz, long long int p) {
  if (p == 1)
    return {(sz+1)/2, (sz+1)/2};

  // what do these names even mean...
  long long int subsquare = std::sqrt((double) (p-1));
  if (subsquare % 2 == 0)
    subsquare -= 1;

  const long long int steps = subsquare+1;
  const long long int p_outer = p - subsquare * subsquare;

  coord result;

  if (p_outer <= steps) {
    result.x = subsquare+2 - p_outer;
    result.y = subsquare+2;
  } else if (p_outer <= steps*2) {
    result.x = 1;
    result.y = subsquare+2 - (p_outer - steps);
  } else if (p_outer <= steps*3) {
    result.x = p_outer - steps*2 + 1;
    result.y = 1;
  } else {
    result.x = subsquare+2;
    result.y = p_outer - steps*3 + 1;
  }

  result.x += (sz - subsquare - 1) / 2;
  result.y += (sz - subsquare - 1) / 2;

  return result;
}

int main() {
  long long int sz, p;
  while ((std::cin >> sz >> p) && sz > 0 && p > 0) {
    coord result = tap(sz, p);
    std::cout << "Line = " << result.y << ", column = " << result.x << ".\n";
  }
}
