#include <cstdio>
#include <unordered_map>

static unsigned int a, b;
static unsigned int mod;

static std::unordered_map<unsigned int, unsigned int> memo;

unsigned int compute(unsigned int n) {
  if (n == 0)
    return a;
  else if (n == 1)
    return b;
  else if (n == 2)
    return a+b;

  auto it = memo.find(n);
  if (it != memo.end())
    return it->second;

  unsigned int result;
  if (n % 2) {
    unsigned int x = (n+1)/2;
    unsigned int prev_1 = compute(x);
    unsigned int prev_2 = compute(x-1);
    result = (prev_1*prev_1 + prev_2*prev_2) % mod;
  } else {
    unsigned int x = n/2;
    unsigned int prev_1 = compute(x);
    unsigned int prev_2 = compute(x-1);
    result = (prev_1 * (prev_1 + 2*prev_2)) % mod;
  }

  memo[n] = result;
  return result;
}

int main() {
  unsigned int garbage;
  std::scanf("%u", &garbage);

  unsigned int n, m;
  while (std::scanf(" %u %u %u %u", &a, &b, &n, &m) == 4) {
    if (m == 1)
      mod = 10;
    else if (m == 2)
      mod = 100;
    else if (m == 3)
      mod = 1000;
    else
      mod = 10000;

    memo.clear();
    std::printf("%u\n", compute(n));
  }
}
