#include "wsp_hash_256.h"

void wsp_hash_256(unsigned long input_count, const uint8_t *input,
                  struct wsp_hash_256_s *s) {
  unsigned long i = 0;

  s->state[0] = 1111111111;

  while (
    i != 7 &&
    i != input_count
  ) {
    i++;
    s->state[i] = input[i - 1] + s->state[i - 1];
    s->state[i] += (s->state[i] + 111111111) << 9;
  }

  while (i != 7) {
    i++;
    s->state[i] = s->state[i - 1] + 111111111;
    s->state[i] += (s->state[i] + 111111111) << 9;
  }

  s->_state[0] = s->state[0];
  s->_state[1] = s->state[1];
  s->_state[2] = s->state[2];
  s->_state[3] = s->state[3];
  s->_state[4] = s->state[4];
  s->_state[5] = s->state[5];
  s->_state[6] = s->state[6];
  s->_state[7] = s->state[7];
  i = 0;

  while (i != input_count) {
    s->state[i & 7] += (
      input[i] + s->state[(i + 1) & 7] + s->state[(i - 1) & 7]
      + 111111111
    ) << 8;
    s->_state[i & 7] ^= ((
      ((input[i] << 24) | (s->state[i - 1 & 7] >> 8))
      + s->state[i & 7]
    ) >> 2) + s->state[i & 7] + input[i] + 11;
    i++;
  }

  while (i < 7) {
    s->state[i] += s->state[i + 1] + 111111111;
    s->state[i] += (s->state[i] + 111111111) << 9;
    i++;
  }

  s->_state[0] += (s->state[0] + s->_state[1]) ^ s->_state[0];
  s->_state[1] += s->state[1] ^ (s->_state[0] + s->_state[2]);
  s->_state[2] += (s->state[2] + s->_state[3]) ^ s->_state[1];
  s->_state[3] += s->state[3] ^ (s->_state[2] + s->_state[4]);
  s->_state[4] += (s->state[4] + s->_state[5]) ^ s->_state[2];
  s->_state[5] += s->state[5] ^ (s->_state[4] + s->_state[6]);
  s->_state[6] += (s->state[6] + s->_state[7]) ^ s->_state[3];
  s->_state[7] += ((
    s->state[1] ^ s->state[2] ^ s->state[3]
  ) << 16) | ((s->state[4] ^ s->state[5] ^ s->state[6]) >> 16) + s->state[7];
  i = 24;

  while (i != 9) {
    s->state[7] += ((
      s->state[(s->state[3] ^ s->_state[7]) & 7]
      + (s->state[4] ^ s->_state[0]) + s->_state[1]
    ) >> i) + (s->state[0] ^ s->_state[2]);
    s->state[6] += ((
      s->state[(s->state[2] ^ s->_state[0]) & 7]
      + (s->state[3] ^ s->_state[1]) + s->_state[2]
    ) << i) + (s->state[7] ^ s->_state[3]);
    s->state[5] += ((
      s->state[(s->state[1] ^ s->_state[1]) & 7]
      + (s->state[2] ^ s->_state[2]) + s->_state[3]
    ) >> i) + (s->state[6] ^ s->_state[4]);
    s->state[4] += ((
      s->state[(s->state[0] ^ s->_state[2]) & 7]
      + (s->state[1] ^ s->_state[3]) + s->_state[4]
    ) << i) + (s->state[5] ^ s->_state[5]);
    s->state[3] += ((
      s->state[(s->state[7] ^ s->_state[3]) & 7]
      + (s->state[0] ^ s->_state[4]) + s->_state[5]
    ) >> i) + (s->state[4] ^ s->_state[6]);
    s->state[2] += ((
      s->state[(s->state[6] ^ s->_state[4]) & 7]
      + (s->state[7] ^ s->_state[5]) + s->_state[6]
    ) << i) + (s->state[3] ^ s->_state[7]);
    s->state[1] += ((
      s->state[(s->state[5] ^ s->_state[5]) & 7]
      + (s->state[6] ^ s->_state[6]) + s->_state[7]
    ) >> i) + (s->state[2] ^ s->_state[0]);
    s->state[0] += ((
      s->state[(s->state[4] ^ s->_state[6]) & 7]
      + (s->state[5] ^ s->_state[7]) + s->_state[0]
    ) << i) + (s->state[1] ^ s->_state[1]);
    i -= 3;
  }
}

void wsp_hash_256_initialize(unsigned long input_count, const uint8_t *input,
                             struct wsp_hash_256_s *s) {
  unsigned char i = 0;

  s->state[0] = 1111111111;

  while (
    i != 7 &&
    i != input_count
  ) {
    i++;
    s->state[i] = input[i - 1] + s->state[i - 1];
    s->state[i] += (s->state[i] + 111111111) << 9;
  }

  while (i != 7) {
    i++;
    s->state[i] = s->state[i - 1] + 111111111;
    s->state[i] += (s->state[i] + 111111111) << 9;
  }

  s->_state[0] = s->state[0];
  s->_state[1] = s->state[1];
  s->_state[2] = s->state[2];
  s->_state[3] = s->state[3];
  s->_state[4] = s->state[4];
  s->_state[5] = s->state[5];
  s->_state[6] = s->state[6];
  s->_state[7] = s->state[7];
}

void wsp_hash_256_transform(unsigned long i, unsigned long input_count,
                            const uint8_t *input,
                            struct wsp_hash_256_s *s) {
  while (i != input_count) {
    s->state[i & 7] += (
      input[i] + s->state[(i + 1) & 7] + s->state[(i - 1) & 7]
      + 111111111
    ) << 8;
    s->_state[i & 7] ^= ((
      ((input[i] << 24) | (s->state[i - 1 & 7] >> 8))
      + s->state[i & 7]
    ) >> 2) + s->state[i & 7] + input[i] + 11;
    i++;
  }

  while (i < 7) {
    s->state[i] += s->state[i + 1] + 111111111;
    s->state[i] += (s->state[i] + 111111111) << 9;
    i++;
  }
}

void wsp_hash_256_finalize(struct wsp_hash_256_s *s) {
  unsigned char i = 24;

  s->_state[0] += (s->state[0] + s->_state[1]) ^ s->_state[0];
  s->_state[1] += s->state[1] ^ (s->_state[0] + s->_state[2]);
  s->_state[2] += (s->state[2] + s->_state[3]) ^ s->_state[1];
  s->_state[3] += s->state[3] ^ (s->_state[2] + s->_state[4]);
  s->_state[4] += (s->state[4] + s->_state[5]) ^ s->_state[2];
  s->_state[5] += s->state[5] ^ (s->_state[4] + s->_state[6]);
  s->_state[6] += (s->state[6] + s->_state[7]) ^ s->_state[3];
  s->_state[7] += ((
    s->state[1] ^ s->state[2] ^ s->state[3]
  ) << 16) | ((s->state[4] ^ s->state[5] ^ s->state[6]) >> 16) + s->state[7];

  while (i != 9) {
    s->state[7] += ((
      s->state[(s->state[3] ^ s->_state[7]) & 7]
      + (s->state[4] ^ s->_state[0]) + s->_state[1]
    ) >> i) + (s->state[0] ^ s->_state[2]);
    s->state[6] += ((
      s->state[(s->state[2] ^ s->_state[0]) & 7]
      + (s->state[3] ^ s->_state[1]) + s->_state[2]
    ) << i) + (s->state[7] ^ s->_state[3]);
    s->state[5] += ((
      s->state[(s->state[1] ^ s->_state[1]) & 7]
      + (s->state[2] ^ s->_state[2]) + s->_state[3]
    ) >> i) + (s->state[6] ^ s->_state[4]);
    s->state[4] += ((
      s->state[(s->state[0] ^ s->_state[2]) & 7]
      + (s->state[1] ^ s->_state[3]) + s->_state[4]
    ) << i) + (s->state[5] ^ s->_state[5]);
    s->state[3] += ((
      s->state[(s->state[7] ^ s->_state[3]) & 7]
      + (s->state[0] ^ s->_state[4]) + s->_state[5]
    ) >> i) + (s->state[4] ^ s->_state[6]);
    s->state[2] += ((
      s->state[(s->state[6] ^ s->_state[4]) & 7]
      + (s->state[7] ^ s->_state[5]) + s->_state[6]
    ) << i) + (s->state[3] ^ s->_state[7]);
    s->state[1] += ((
      s->state[(s->state[5] ^ s->_state[5]) & 7]
      + (s->state[6] ^ s->_state[6]) + s->_state[7]
    ) >> i) + (s->state[2] ^ s->_state[0]);
    s->state[0] += ((
      s->state[(s->state[4] ^ s->_state[6]) & 7]
      + (s->state[5] ^ s->_state[7]) + s->_state[0]
    ) << i) + (s->state[1] ^ s->_state[1]);
    i -= 3;
  }
}
