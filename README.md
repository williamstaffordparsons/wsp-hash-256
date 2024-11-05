# WSP-Hash-256
© 2024 William Stafford Parsons

## About
WSP-Hash-256 is a 256-bit cryptographic hashing algorithm as both a substantial improvement to SHA-256 and a test subject for cryptanalysis.

Read more [here](https://williamstaffordparsons.github.io/wsp-hash-256/).

## Example
``` c
#include <stdio.h>
#include "wsp_hash_256.h"

int main(void) {
  struct wsp_hash_256_s s;
  uint8_t input[8] = {'m', 'e', 's', 's', 'a', 'g', 'e', 0};
  unsigned char i = 0;

  while (i != 10) {
    i++;
    wsp_hash_256(8, (const uint8_t *) input, &s);
    printf("All-at-once result %u is ", i);
    printf("0x%08x 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x.\n",
      s.state[0], s.state[1], s.state[2], s.state[3],
      s.state[4], s.state[5], s.state[6], s.state[7]
    );
    input[7]++;
  }

  input[7] = 0;
  i = 0;

  while (i != 10) {
    i++;
    wsp_hash_256_initialize(8, (const uint8_t *) input, &s);
    wsp_hash_256_transform(0, 8, (const uint8_t *) input, &s);
    wsp_hash_256_finalize(&s);
    input[7]++;
    printf("Segmented result %u is ", i);
    printf("0x%08x 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x.\n",
      s.state[0], s.state[1], s.state[2], s.state[3],
      s.state[4], s.state[5], s.state[6], s.state[7]
    );
  }

  return 0;
}
```
