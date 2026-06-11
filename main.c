#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bignums.h"

int
main(void)
{
  const char *num = "123456789";

  Big_Num *bignum1 = bignum_from_string(num);
  Big_Num *bignum2 = bignum_from_string(num);

  Big_Num *bignum3 = bignum_add(bignum1, bignum2);
  char *num3 = bignum_to_string(bignum3);

  assert(strcmp(num3, "246913578") == 0);
  puts("PASSED");

  bignum_free(bignum1);
  bignum_free(bignum2);
  bignum_free(bignum3);
  free(num3);
  return 0;
}
