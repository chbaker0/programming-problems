#include <iostream>
#include <cstring>

unsigned int reverse(unsigned int x) {
  unsigned int result = 0;
  while (x) {
    result *= 10;
    result += x % 10;
    x /= 10;
  }
  return result;
}

static const unsigned int max_input = 1000000;
static bool marks[max_input+1];

void sieve() {
  std::memset(marks, 0, sizeof(marks));

  marks[0] = true;
  marks[1] = true;
  for (unsigned int p = 2; p <= max_input; ++p) {
    if (marks[p])
      continue;
    for (unsigned int m = p*p; m <= max_input; m += p)
      marks[m] = true;
  }
}

int main() {
  sieve();

  unsigned int n;
  while (std::cin >> n) {
    unsigned int rev = reverse(n);
    if (rev != n && !marks[n] && !marks[reverse(n)])
      std::cout << n << " is emirp.\n";
    else if (!marks[n])
      std::cout << n << " is prime.\n";
    else
      std::cout << n << " is not prime.\n";
  }
}
