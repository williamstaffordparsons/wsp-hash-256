#include "wsp_hash_256.h"

void wsp_hash_256(const unsigned long input_count, const uint8_t *input,
                  struct wsp_hash_256_s *s) {
  unsigned long i = 0;

  s->mix[0] = 1111111111;

  while (
    i != 7 &&
    i != input_count
  ) {
    i++;
    s->mix[i] = input[i - 1] + s->mix[i - 1];
    s->mix[i] += (s->mix[i] + 111111111) << 9;
  }

  while (i != 7) {
    i++;
    s->mix[i] = s->mix[i - 1] + 111111111;
    s->mix[i] += (s->mix[i] + 111111111) << 9;
  }

  s->mix_offset[0] = s->mix[0];
  s->mix_offset[1] = s->mix[1];
  s->mix_offset[2] = s->mix[2];
  s->mix_offset[3] = s->mix[3];
  s->mix_offset[4] = s->mix[4];
  s->mix_offset[5] = s->mix[5];
  s->mix_offset[6] = s->mix[6];
  s->mix_offset[7] = s->mix[7];
  i = 0;

  while (i != input_count) {
    s->mix[i & 7] += (
      input[i] + s->mix[(i + 1) & 7] + s->mix[(i - 1) & 7] + 111111111
    ) << 8;
    s->mix_offset[i & 7] ^= ((
      ((input[i] << 24) | (s->mix[i - 1 & 7] >> 8)) + s->mix[i & 7]
    ) >> 2) + s->mix[i & 7] + input[i] + 11;
    i++;
  }

  while (i < 7) {
    s->mix[i] += s->mix[i + 1] + 111111111;
    s->mix[i] += (s->mix[i] + 111111111) << 9;
    i++;
  }

  s->mix_offset[0] += (s->mix[0] + s->mix_offset[1]) ^ s->mix_offset[0];
  s->mix_offset[1] += s->mix[1] ^ (s->mix_offset[0] + s->mix_offset[2]);
  s->mix_offset[2] += (s->mix[2] + s->mix_offset[3]) ^ s->mix_offset[1];
  s->mix_offset[3] += s->mix[3] ^ (s->mix_offset[2] + s->mix_offset[4]);
  s->mix_offset[4] += (s->mix[4] + s->mix_offset[5]) ^ s->mix_offset[2];
  s->mix_offset[5] += s->mix[5] ^ (s->mix_offset[4] + s->mix_offset[6]);
  s->mix_offset[6] += (s->mix[6] + s->mix_offset[7]) ^ s->mix_offset[3];
  s->mix_offset[7] += ((
    s->mix[1] ^ s->mix[2] ^ s->mix[3]
  ) << 16) | ((s->mix[4] ^ s->mix[5] ^ s->mix[6]) >> 16) + s->mix[7];
  i = 24;

  while (i != 9) {
    s->mix[7] += ((
      s->mix[(s->mix[3] ^ s->mix_offset[7]) & 7]
        + (s->mix[4] ^ s->mix_offset[0]) + s->mix_offset[1]
    ) >> i) + (s->mix[0] ^ s->mix_offset[2]);
    s->mix[6] += ((
      s->mix[(s->mix[2] ^ s->mix_offset[0]) & 7]
        + (s->mix[3] ^ s->mix_offset[1]) + s->mix_offset[2]
    ) << i) + (s->mix[7] ^ s->mix_offset[3]);
    s->mix[5] += ((
      s->mix[(s->mix[1] ^ s->mix_offset[1]) & 7]
        + (s->mix[2] ^ s->mix_offset[2]) + s->mix_offset[3]
    ) >> i) + (s->mix[6] ^ s->mix_offset[4]);
    s->mix[4] += ((
      s->mix[(s->mix[0] ^ s->mix_offset[2]) & 7]
        + (s->mix[1] ^ s->mix_offset[3]) + s->mix_offset[4]
    ) << i) + (s->mix[5] ^ s->mix_offset[5]);
    s->mix[3] += ((
      s->mix[(s->mix[7] ^ s->mix_offset[3]) & 7]
        + (s->mix[0] ^ s->mix_offset[4]) + s->mix_offset[5]
    ) >> i) + (s->mix[4] ^ s->mix_offset[6]);
    s->mix[2] += ((
      s->mix[(s->mix[6] ^ s->mix_offset[4]) & 7]
        + (s->mix[7] ^ s->mix_offset[5]) + s->mix_offset[6]
    ) << i) + (s->mix[3] ^ s->mix_offset[7]);
    s->mix[1] += ((
      s->mix[(s->mix[5] ^ s->mix_offset[5]) & 7]
        + (s->mix[6] ^ s->mix_offset[6]) + s->mix_offset[7]
    ) >> i) + (s->mix[2] ^ s->mix_offset[0]);
    s->mix[0] += ((
      s->mix[(s->mix[4] ^ s->mix_offset[6]) & 7]
        + (s->mix[5] ^ s->mix_offset[7]) + s->mix_offset[0]
    ) << i) + (s->mix[1] ^ s->mix_offset[1]);
    i -= 3;
  }
}

void wsp_hash_256_initialize(const unsigned long input_count,
                             const uint8_t *input, struct wsp_hash_256_s *s) {
  unsigned char i = 0;

  s->mix[0] = 1111111111;

  while (
    i != 7 &&
    i != input_count
  ) {
    i++;
    s->mix[i] = input[i - 1] + s->mix[i - 1];
    s->mix[i] += (s->mix[i] + 111111111) << 9;
  }

  while (i != 7) {
    i++;
    s->mix[i] = s->mix[i - 1] + 111111111;
    s->mix[i] += (s->mix[i] + 111111111) << 9;
  }

  s->mix_offset[0] = s->mix[0];
  s->mix_offset[1] = s->mix[1];
  s->mix_offset[2] = s->mix[2];
  s->mix_offset[3] = s->mix[3];
  s->mix_offset[4] = s->mix[4];
  s->mix_offset[5] = s->mix[5];
  s->mix_offset[6] = s->mix[6];
  s->mix_offset[7] = s->mix[7];
}

void wsp_hash_256_transform(unsigned long i, const unsigned long input_count,
                            const uint8_t *input, struct wsp_hash_256_s *s) {
  while (i != input_count) {
    s->mix[i & 7] += (
      input[i] + s->mix[(i + 1) & 7] + s->mix[(i - 1) & 7] + 111111111
    ) << 8;
    s->mix_offset[i & 7] ^= ((
      ((input[i] << 24) | (s->mix[i - 1 & 7] >> 8)) + s->mix[i & 7]
    ) >> 2) + s->mix[i & 7] + input[i] + 11;
    i++;
  }

  while (i < 7) {
    s->mix[i] += s->mix[i + 1] + 111111111;
    s->mix[i] += (s->mix[i] + 111111111) << 9;
    i++;
  }
}

void wsp_hash_256_finalize(struct wsp_hash_256_s *s) {
  unsigned char i = 24;

  s->mix_offset[0] += (s->mix[0] + s->mix_offset[1]) ^ s->mix_offset[0];
  s->mix_offset[1] += s->mix[1] ^ (s->mix_offset[0] + s->mix_offset[2]);
  s->mix_offset[2] += (s->mix[2] + s->mix_offset[3]) ^ s->mix_offset[1];
  s->mix_offset[3] += s->mix[3] ^ (s->mix_offset[2] + s->mix_offset[4]);
  s->mix_offset[4] += (s->mix[4] + s->mix_offset[5]) ^ s->mix_offset[2];
  s->mix_offset[5] += s->mix[5] ^ (s->mix_offset[4] + s->mix_offset[6]);
  s->mix_offset[6] += (s->mix[6] + s->mix_offset[7]) ^ s->mix_offset[3];
  s->mix_offset[7] += ((
    s->mix[1] ^ s->mix[2] ^ s->mix[3]
  ) << 16) | ((s->mix[4] ^ s->mix[5] ^ s->mix[6]) >> 16) + s->mix[7];

  while (i != 9) {
    s->mix[7] += ((
      s->mix[(s->mix[3] ^ s->mix_offset[7]) & 7]
      + (s->mix[4] ^ s->mix_offset[0]) + s->mix_offset[1]
    ) >> i) + (s->mix[0] ^ s->mix_offset[2]);
    s->mix[6] += ((
      s->mix[(s->mix[2] ^ s->mix_offset[0]) & 7]
      + (s->mix[3] ^ s->mix_offset[1]) + s->mix_offset[2]
    ) << i) + (s->mix[7] ^ s->mix_offset[3]);
    s->mix[5] += ((
      s->mix[(s->mix[1] ^ s->mix_offset[1]) & 7]
      + (s->mix[2] ^ s->mix_offset[2]) + s->mix_offset[3]
    ) >> i) + (s->mix[6] ^ s->mix_offset[4]);
    s->mix[4] += ((
      s->mix[(s->mix[0] ^ s->mix_offset[2]) & 7]
      + (s->mix[1] ^ s->mix_offset[3]) + s->mix_offset[4]
    ) << i) + (s->mix[5] ^ s->mix_offset[5]);
    s->mix[3] += ((
      s->mix[(s->mix[7] ^ s->mix_offset[3]) & 7]
      + (s->mix[0] ^ s->mix_offset[4]) + s->mix_offset[5]
    ) >> i) + (s->mix[4] ^ s->mix_offset[6]);
    s->mix[2] += ((
      s->mix[(s->mix[6] ^ s->mix_offset[4]) & 7]
      + (s->mix[7] ^ s->mix_offset[5]) + s->mix_offset[6]
    ) << i) + (s->mix[3] ^ s->mix_offset[7]);
    s->mix[1] += ((
      s->mix[(s->mix[5] ^ s->mix_offset[5]) & 7]
      + (s->mix[6] ^ s->mix_offset[6]) + s->mix_offset[7]
    ) >> i) + (s->mix[2] ^ s->mix_offset[0]);
    s->mix[0] += ((
      s->mix[(s->mix[4] ^ s->mix_offset[6]) & 7]
      + (s->mix[5] ^ s->mix_offset[7]) + s->mix_offset[0]
    ) << i) + (s->mix[1] ^ s->mix_offset[1]);
    i -= 3;
  }
}
