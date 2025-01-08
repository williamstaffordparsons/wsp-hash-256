#ifndef WSP_HASH_256_H
#define WSP_HASH_256_H

#include <stdint.h>

struct wsp_hash_256_s {
  uint32_t mix[8];
  uint32_t mix_offset[8];
};

void wsp_hash_256(const unsigned long input_count, const uint8_t *input,
                  struct wsp_hash_256_s *s);

void wsp_hash_256_initialize(const unsigned long input_count,
                             const uint8_t *input, struct wsp_hash_256_s *s);

void wsp_hash_256_transform(unsigned long i, const unsigned long input_count,
                            const uint8_t *input, struct wsp_hash_256_s *s);

void wsp_hash_256_finalize(struct wsp_hash_256_s *s);

#endif
