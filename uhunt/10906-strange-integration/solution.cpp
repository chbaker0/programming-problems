#include <unordered_map>
#include <memory>
#include <string>
#include <cstdio>
#include <cstring>
#include <cctype>

struct expression {
  char op;
  char left[11];
  char right[11];
};

static char names[50][11];
static std::unordered_map<std::string, expression> vars;

std::string gen_exp(const char* name, char prev_op = 0, bool is_right = false) {
  std::string result;

  expression exp = vars[name];

  bool need_paren = false;

  if (prev_op == '*' && exp.op == '+') {
    //      *
    //     / \
    //   ...  + <-
    // OR
    //      *
    //     / \
    // -> +  ...
    need_paren = true;
  } else if (prev_op == exp.op && is_right) {
    //      op
    //     /  \
    //   ...  op <-
    need_paren = true;
  }

  if (need_paren)
    result += '(';

  if (std::isalpha(exp.left[0]))
    result += gen_exp(exp.left, exp.op, false);
  else
    result += exp.left;

  result += exp.op;

  if (std::isalpha(exp.right[0]))
    result += gen_exp(exp.right, exp.op, true);
  else
    result += exp.right;

  if (need_paren)
    result += ')';

  return result;
}

int main() {
  unsigned int garbage;
  std::scanf(" %u", &garbage);

  unsigned int T = 1;
  unsigned int N;
  while (std::scanf(" %u", &N) > 0) {
    vars.clear();
    for (unsigned int i = 0; i < N; ++i) {
      expression exp = {};
      std::scanf(" %10s = %10s %1c %10s", names[i], exp.left, &exp.op, exp.right);
      vars[names[i]] = exp;
    }
    std::printf("Expression #%u: %s\n", T++, gen_exp(names[N-1]).c_str());
  }
}
