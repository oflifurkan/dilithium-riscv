#include "../randombytes.h"
#include "../sign.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define MLEN 59
#define NTESTS 1

void store_word(uint32_t *address, uint32_t data);

void store_word(uint32_t *address, uint32_t data) {
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("sw %[data], 0(%[address])"
               :
               : [data] "r"(data), [address] "r"(address));
  asm volatile("nop");
  asm volatile("nop");
  asm volatile("nop");
}

int main(void) {

  // volatile unsigned int *LED_ADDR = (volatile unsigned int *)0x00002010;

  char message_match = 1;
  size_t i, j;
  // int ret;
  size_t mlen, smlen;
  // uint8_t b;
  uint8_t m[MLEN + CRYPTO_BYTES];
  uint8_t m2[MLEN + CRYPTO_BYTES];
  uint8_t sm[MLEN + CRYPTO_BYTES];
  uint8_t pk[CRYPTO_PUBLICKEYBYTES];
  uint8_t sk[CRYPTO_SECRETKEYBYTES];

  for (i = 0; i < NTESTS; ++i) {
    randombytes(m, MLEN);

    crypto_sign_keypair(pk, sk);
    crypto_sign(sm, &smlen, m, MLEN, sk);
    crypto_sign_open(m2, &mlen, sm, smlen, pk);

    for (j = 0; j < MLEN; ++j) {
      if (m2[j] != m[j]) {
        message_match = 0;
        break;
      }
    }
  }

  uint32_t *control_address = (uint32_t *)0x14000;
  uint32_t data;

  if (message_match)
    data = 170;
  else
    data = 255;

  while (1)
    store_word(control_address, data);

  return 0;
}
