#include <algorithm>
#include <iostream>
#include <cstring>

// 46341 = ceil(sqrt(INT32_MAX))
static constexpr unsigned int max_init = 46341;

static unsigned int num_init_primes = 0;
static unsigned int init_primes[10000];

void init_sieve() {
  static bool marks[max_init+1];
  std::memset(marks, 0, max_init+1);

  marks[0] = true;
  marks[1] = true;

  for (unsigned int p = 2; p <= max_init; ++p) {
    // check if composite
    if (marks[p])
      continue;

    init_primes[num_init_primes++] = p;
    for (unsigned int m = p*p; m <= max_init; m += p)
      marks[m] = true;
  }
}

// 1 MiB limit
static constexpr unsigned int segment_limit = 1024 * 1024;

void sieve_segment(unsigned int min, unsigned int max, bool* marks) {
  std::memset(marks, 0, max - min + 1);

  for (unsigned int i = 0; i < num_init_primes; ++i) {
    unsigned int p = init_primes[i];
    if (p*p > max)
      return;

    unsigned int start = std::max(p*p, p*(min/p));
    for (unsigned int m = start; m <= max; m += p) {
      if (m < min)
        continue;
      marks[m-min] = true;
    }
  }
}

int main() {
  init_sieve();

  static bool marks[segment_limit];

  unsigned int min, max;
  while (std::cin >> min >> max) {
    min = std::max(min, 2u);
    if (max <= min) {
      std::cout << "There are no adjacent primes.\n";
      continue;
    }

    unsigned int c1 = 0, c2 = 0, d1 = 0, d2 = 0;
    unsigned int p_prev = 0;
    unsigned int cur_bound = min;
    while (cur_bound < max) {
      unsigned int seg_max = std::min(cur_bound+segment_limit-1, max);
      sieve_segment(cur_bound, seg_max, marks);

      for (unsigned int n = cur_bound; n <= seg_max; ++n) {
        if (marks[n-cur_bound])
          continue;
        if (p_prev == 0) {
          p_prev = n;
          continue;
        }

        if (c1 == 0 || (n-p_prev) < (c2-c1)) {
          c2 = n;
          c1 = p_prev;
        }

        if (d1 == 0 || (n-p_prev) > (d2-d1)) {
          d2 = n;
          d1 = p_prev;
        }

        p_prev = n;
      }

      cur_bound = seg_max + 1;
    }

    if (c1 != 0)
      std::cout << c1 << "," << c2 << " are closest, " << d1 << "," << d2 << " are most distant.\n";
    else
      std::cout << "There are no adjacent primes.\n";
  }
}
