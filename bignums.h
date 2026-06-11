#ifndef __BIGNUMS_H_
#define __BIGNUMS_H_

#include <stddef.h>

#define BIGNUM_DEFAULT_CAPASITY 128

typedef struct {
  int *limbs; /* each number is between 0 and 1000 */
  size_t count;
  size_t capasity;
  int sign;
} Big_Num;

/* Creates Big_Num from given string (string must contain only digits exept first symbol, it can be `-`) */
Big_Num *bignum_from_string(const char *num);

/* Adds num1 to num2. Result is returned and must be freed after usage */
Big_Num *bignum_add(Big_Num *num1, Big_Num *num2);

/* Returns a string representations of number, you must free it yourself */
char *bignum_to_string(Big_Num *num);

void bignum_free(Big_Num *num);

#endif /* __BIGNUMS_H_ */
