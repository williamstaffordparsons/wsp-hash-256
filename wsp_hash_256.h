#ifndef WSP_HASH_256_H
#define WSP_HASH_256_H

#include <stdint.h>

struct wsp_hash_256_s {
  uint32_t _state[8];
  uint32_t state[8];
};

void wsp_hash_256(unsigned long input_count, const uint8_t *input,
                  struct wsp_hash_256_s *s);

void wsp_hash_256_initialize(unsigned long input_count, const uint8_t *input,
                             struct wsp_hash_256_s *s);

void wsp_hash_256_transform(unsigned long i, unsigned long input_count,
                            const uint8_t *input,
                            struct wsp_hash_256_s *s);

void wsp_hash_256_finalize(struct wsp_hash_256_s *s);

#endif
