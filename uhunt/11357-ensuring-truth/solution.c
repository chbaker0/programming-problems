#include <ctype.h>
#include <stdio.h>
#include <string.h>

#if defined(ONLINE_JUDGE)
#define NDEBUG
#endif

#include <assert.h>

static char formula_str[251];

int satisfiable() {
  unsigned int i = 0;
  while (1) {
    int clause_sat = 1;
    int values[26] = {0};

    assert(formula_str[i] == '(');
    i += 1;

    while (1) {
      int not = 0;
      if (formula_str[i] == '~') {
        i += 1;
        not = 1;
      }

      char var = formula_str[i];
      i += 1;
      assert(isalpha(var) && islower(var));

      if (values[var - 'a'] == 0)
        values[var - 'a'] = 1 + not;
      else if (values[var - 'a'] != 1 + not)
        clause_sat = 0;

      if (formula_str[i] == '&') {
        i += 1;
      } else {
        assert(formula_str[i] == ')');
        i += 1;
        break;
      }
    }

    if (clause_sat)
      return 1;

    if (formula_str[i] == '|') {
      i += 1;
    } else {
      assert(formula_str[i] == 0);
      break;
    }
  }

  return 0;
}

int main() {
  unsigned int garbage;
  scanf("%u", &garbage);

  while (scanf(" %250s", formula_str) > 0)
    puts(satisfiable() ? "YES" : "NO");

  return 0;
}
