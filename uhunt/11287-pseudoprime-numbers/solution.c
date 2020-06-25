#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

static uint64_t p;

uint64_t exponentiate(uint64_t a, uint64_t e, uint64_t accum) {
  if (e == 1)
    return (a*accum) % p;

  uint64_t a_sq = (a*a) % p;
  if (e % 2)
    return exponentiate(a_sq, e/2, (a*accum)%p);
  else
    return exponentiate(a_sq, e/2, accum);
}

#define MAX_PRIME 31623

static unsigned int primes[4096];
static unsigned int num_primes;

void sieve() {
  static unsigned char sieve[MAX_PRIME+1] = {0};

  num_primes = 0;

  unsigned int p;
  for (p = 2; p <= MAX_PRIME; ++p) {
    if (sieve[p])
      continue;

    primes[num_primes++] = p;

    unsigned int m;
    for (m = p*p; m <= MAX_PRIME; m += p) {
      sieve[m] = 1;
    }
  }
}

int is_prime(uint64_t a) {
  unsigned int i;
  for (i = 0; i < num_primes; ++i) {
    unsigned int n = primes[i];
    if (n >= a)
      break;
    if (a % n == 0)
      return 0;
  }

  return 1;
}

int main() {
  sieve();

  uint64_t a;
  while (scanf(" %"SCNu64" %"SCNu64, &p, &a) && p && a) {
    const char* ans;
    if (is_prime(p))
      ans = "no";
    else if (a == exponentiate(a, p, 1))
      ans = "yes";
    else
      ans = "no";
    puts(ans);
  }

  return 0;
}
