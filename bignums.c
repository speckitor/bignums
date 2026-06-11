#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bignums.h"

static int char_to_num(const char ch)
{
  switch (ch) {
  case '0': return 0;
  case '1': return 1;
  case '2': return 2;
  case '3': return 3;
  case '4': return 4;
  case '5': return 5;
  case '6': return 6;
  case '7': return 7;
  case '8': return 8;
  case '9': return 9;
  };
}

static int limb_length(int limb)
{
  if (limb > 99) return 3;
  if (limb > 9) return 2;
  else return 0;
}

Big_Num *bignum_from_string(const char *num)
{
  Big_Num *bignum = calloc(1, sizeof(*bignum));
  bignum->count = 0;
  bignum->capasity = BIGNUM_DEFAULT_CAPASITY;
  bignum->limbs = calloc(bignum->capasity, sizeof(*bignum->limbs));
  bignum->sign = num[0] == '-' ? 0 : 1;

  int idx = 0;
  int t = 1;
  for (int i = strlen(num) - 1; bignum->sign ? i >= 0 : i > 0; --i) {
    bignum->limbs[idx] += t * char_to_num(num[i]);
    if (t * 10 == 1000) {
      t = 1;
      idx++;
      bignum->count++;
    } else {
      t *= 10;
    }
  }

  return bignum;
}

Big_Num *bignum_add(Big_Num *num1, Big_Num *num2)
{
  Big_Num *bignum = calloc(1, sizeof(*bignum));
  bignum->count = 0;
  bignum->capasity = BIGNUM_DEFAULT_CAPASITY;
  bignum->limbs = calloc(bignum->capasity, sizeof(*bignum->limbs));
  bignum->sign = 1;

  int carry = 0;
  int i = 0;
  while (i < num1->count || i < num2->count) {
    if (i < num1->count)
      carry += num1->limbs[i];
    if (i < num2->count)
      carry += num1->limbs[i];

    bignum->limbs[i] = carry % 1000;
    carry /= 1000;

    bignum->count++;
    i++;
  }

  if (carry)
    bignum->limbs[bignum->count++] = carry;

  return bignum;
}

char *bignum_to_string(Big_Num *bignum)
{
  char *num = calloc(bignum->count * 4, sizeof(char));

  int last = bignum->count - 1;
  snprintf(num, 4, "%d", bignum->limbs[last]);
  int off = strlen(num);
  for (int i = last - 1; i >= 0; --i) {
    snprintf(num + off, 4, "%03d", bignum->limbs[i]);
    off += 3;
  }

  return num;
}

void bignum_free(Big_Num *bignum)
{
  free(bignum->limbs);
  free(bignum);
}
