#include <cassert>
#include <cstdio>

static unsigned int a, b;
static unsigned int mod;

// [ w x ]
// [ y z ]
struct mat {
  unsigned int w, x, y, z;
};

static mat prod(const mat& A, const mat& B) {
  mat result;
  result.w = (A.w*B.w + A.x*B.y) % mod;
  result.x = (A.w*B.x + A.x*B.z) % mod;
  result.y = (A.y*B.w + A.z*B.y) % mod;
  result.z = (A.y*B.x + A.z*B.z) % mod;
  return result;
}

static mat power(const mat& A, unsigned int n) {
  assert(n != 0);
  if (n == 1)
    return A;

  mat B = power(A, n/2);
  B = prod(B, B);
  if (n%2)
    return prod(B, A);
  else
    return B;
}

int main() {
  unsigned int garbage;
  std::scanf("%u", &garbage);

  const mat A = {1, 1, 1, 0};

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

    unsigned int result;
    if (n == 0) {
      result = a % mod;
    } else if (n == 1) {
      result = b % mod;
    } else if (n == 2) {
      result = (b+a) % mod;
    } else {
      const mat B = power(A, n);
      result = (B.y*b + B.z*a) % mod;
    }

    std::printf("%u\n", result);
  }
}
