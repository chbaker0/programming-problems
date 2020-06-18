#include <iostream>
#include <cstdint>

int main() {
  unsigned int dummy;
  std::cin >> dummy;

  unsigned int num_coins;

  while (std::cin >> num_coins) {
    unsigned int coins[1000];
    for (unsigned int i = 0; i < num_coins; ++i) {
      std::cin >> coins[i];
    }

    std::uint64_t sum = 0;
    unsigned int uniques = 0;
    for (unsigned int i = 0; i < num_coins-1; ++i) {
      if (sum + coins[i] < coins[i+1]) {
        uniques += 1;
        sum += coins[i];
      }
    }

    uniques += 1;

    std::cout << uniques << "\n";
  }
}
