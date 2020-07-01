#include <stdio.h>
#include <stdlib.h>

#ifdef ONLINE_JUDGE
#define NDEBUG
#endif

#include <assert.h>

#define MAX_LEN 262144

static char expression[MAX_LEN+1];
static unsigned int len;

int get_line() {
  len = 0;
  int c;
  while ((c = getchar()) != '\n') {
    if (c == EOF)
      return 0;
    assert(len < MAX_LEN);

    expression[len++] = c;
  }

  expression[len] = 0;

  assert(len > 0);
  return !(len == 2 && expression[0] == '(' && expression[1] == ')');
}

static unsigned int i;

double read_num() {
  char* end;
  double num = strtod(expression+i, &end);
  i = end - expression;
  return num;
}

double ev() {
  assert(i < len);
  if (expression[i] == '(') {
    ++i;
    double p = read_num();
    assert(expression[i] == ' ');
    ++i;
    double a = ev();
    assert(expression[i] == ' ');
    ++i;
    double b = ev();
    assert(expression[i] == ')');
    ++i;
    return a + b*(2*p-1);
  } else {
    return read_num();
  }
}

int main() {
  while (get_line()) {
    i = 0;
    double result = ev();
    assert(i == len);
    printf("%#.2f\n", result);
  }

  return 0;
}
