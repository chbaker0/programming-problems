#include <assert.h>
#include <ctype.h>
#include <stdio.h>

static unsigned char x_digits[100];
static unsigned int x_len;
static unsigned char y_digits[100];
static unsigned int y_len;

static unsigned char sum[200];
static unsigned int sum_len;

void add_digit(unsigned int i, int d) {
  while (i >= sum_len)
    sum[sum_len++] = 0;
  sum[i] = d + (int) sum[i];
}

int main() {
  int first = 1;
  while (1) {
    x_len = 0;
    y_len = 0;

    int c = getchar();
    if (c == '\n')
      c = getchar();
    if (c < 0)
      return 0;

    do {
      x_digits[x_len++] = c - '0';
    } while ((c = getchar()) != '\n');

    while ((c = getchar()) != '\n') {
      y_digits[y_len++] = c - '0';
    }

    if (x_len > y_len)
      sum_len = x_len;
    else
      sum_len = y_len;

    unsigned int i;
    for (i = 0; i < sum_len; ++i) {
      unsigned char x = i < x_len ? x_digits[x_len - i - 1] : 0;
      unsigned char y = i < y_len ? y_digits[y_len - i - 1] : 0;
      sum[i] = x + y;
    }

    int done = 0;
    while (!done) {
      done = 1;

      if (sum_len < 1)
        break;

      while (sum[0] >= 2) {
        done = 0;
        add_digit(1, 1);
        add_digit(0, -2);
      }

      if (sum_len < 2)
        continue;

      while (sum[1] >= 1 && sum[0] >= 1) {
        done = 0;
        add_digit(2, 1);
        add_digit(1, -1);
        add_digit(0, -1);
      }

      while (sum[1] >= 2) {
        done = 0;
        add_digit(2, 1);
        add_digit(1, -2);
        add_digit(0, 1);
      }

      for (i = 2; i < sum_len; ++i) {
        while (sum[i] >= 1 && sum[i-1] >= 1) {
          done = 0;
          add_digit(i+1,  1);
          add_digit(i,   -1);
          add_digit(i-1, -1);
        }

        while (sum[i] >= 2) {
          done = 0;
          add_digit(i+1,  1);
          add_digit(i,   -2);
          add_digit(i-2,  1);
        }
      }
    }

    if (!first)
      putchar('\n');
    first = 0;

    for (i = 0; i < sum_len; ++i) {
      unsigned char d = sum[sum_len - i - 1];
      assert(d <= 1);
      putchar(d + '0');
    }

    putchar('\n');
  }
}
