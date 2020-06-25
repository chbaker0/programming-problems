#include <stdio.h>
#include <stdint.h>

#define NUM_PLACES 24;

struct bigint {
  uint64_t places[NUM_PLACES];
};

void add(struct bigint* target, const struct bigint* summand) {
  int i = 0;
  int carry = 0;
  do {
    if (carry) {
      target->places[i] += 1;
      if (target->places[i] == 0)
    }
    uint64_t sum = target->places[i] + summand->places[i];
    i += 1;
  } while (carry > 0);
}

int main() {
  
}
