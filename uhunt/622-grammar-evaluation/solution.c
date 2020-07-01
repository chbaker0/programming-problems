#include <stdio.h>
#include <ctype.h>

static const char* str;

int eval_exp();

int eval_fact() {
  if (*str == '(') {
    int num = eval_exp(++str);
    if (*str != ')')
      return -1;
    ++str;
    return num;
  }

  if (!isdigit(*str))
    return -1;

  int num = 0;
  while (isdigit(*str)) {
    num = 10*num + (*str - '0');
    ++str;
  }

  return num;
}

int eval_comp() {
  int prod = eval_fact(str);
  if (prod == -1)
    return -1;

  while (*str == '*') {
    ++str;
    int res = eval_fact(str);
    if (res == -1)
      return -1;
    prod *= res;
  }
  return prod;
}

int eval_exp() {
  int sum = eval_comp(str);
  if (sum == -1)
    return -1;

  while (*str == '+') {
    ++str;
    int res = eval_comp(str);
    if (res == -1)
      return -1;
    sum += res;
  }

  if (*str != 0 && *str != ')')
    return -1;

  return sum;
}

int main() {
  int garbage;
  scanf("%d", &garbage);

  char exp[2049];
  while (scanf(" %2048s", exp) > 0) {
    str = exp;
    int result = eval_exp(exp);
    if (*str == 0 && result >= 0)
      printf("%d\n", result);
    else
      puts("ERROR");
  }

  return 0;
}
