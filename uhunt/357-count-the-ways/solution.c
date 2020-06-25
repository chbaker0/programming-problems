#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

static uint64_t ways[5][30001];
static uint64_t denominations[] = {1, 5, 10, 25, 50};

int main() {
  int i;
  for (i = 0; i < 5; ++i)
    ways[i][0] = 1;

  for (i = 0; i <= 30000; ++i)
    ways[0][i] = 1;

  for (i = 1; i <= 30000; ++i) {
    int j;
    for (j = 1; j < 5; ++j) {
      ways[j][i] = ways[j-1][i];

      uint64_t denom = denominations[j];
      if (denom <= i) {
        ways[j][i] += ways[j][i-denom];
      }
    }
  }

  uint64_t x;
  while (scanf("%"SCNu64, &x) == 1) {
    if (ways[4][x] > 1)
      printf("There are %"PRIu64" ways to produce %"PRIu64" cents change.\n", ways[4][x], x);
    else
      printf("There is only 1 way to produce %"PRIu64" cents change.\n", x);
  }

  return 0;
}
