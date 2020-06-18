#include <iostream>
#include <string>
#include <vector>

static std::string str;
static std::vector<char> stack;

bool is_valid() {
  stack.clear();

  for (char c : str) {
    if (c == '(' || c == '[') {
      stack.push_back(c);
      continue;
    }

    char match;
    if (c == ')')
      match = '(';
    else if (c == ']')
      match = '[';
    else
      continue;

    if (stack.empty())
      return false;

    if (stack.back() != match)
      return false;

    stack.pop_back();
  }

  return stack.empty();
}

int main() {
  str.reserve(128);
  stack.reserve(128);

  int case_count;
  std::cin >> case_count;
  std::getline(std::cin, str);
  while (case_count--) {
    std::getline(std::cin, str);
    std::cout << (is_valid() ? "Yes" : "No") << "\n";
  }
}
