#include <stdio.h>
#include <string.h>

static int str_len;
static char str[1000];

int is_valid() {
  char stack[1000];
  int stack_sz = 0;

  int i;
  for (i = 0; i < str_len; ++i) {
    char match = 0;
    if (str[i] == '(' || str[i] == '[') {
      stack[stack_sz++] = str[i];
      continue;
    } else if (str[i] == ')') {
      match = '(';
    } else if (str[i] == ']') {
      match = '[';
    } else if (str[i] == ' ') {
      continue;
    } else {
      return 0;
    }

    if (stack_sz == 0)
      return 0;

    if (stack[stack_sz-1] != match)
      return 0;

    --stack_sz;
  }

  return stack_sz == 0;
}

int main() {
  int case_count;
  scanf("%d", &case_count);
  getchar();
  while (case_count--) {
    fgets(str, 1000, stdin);
    str_len = strlen(str);
    if (str[str_len-1] == '\n')
      --str_len;
    printf("%s\n", is_valid() ? "Yes" : "No");
  }

  return 0;
}
