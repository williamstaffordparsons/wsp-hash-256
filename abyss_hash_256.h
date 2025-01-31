#ifndef ABYSS_HASH_256_H
#define ABYSS_HASH_256_H

#include <stdint.h>

struct abyss_hash_256_s {
  uint32_t mix[8];
  uint32_t mix_offset[8];
};

void abyss_hash_256(const unsigned long input_count, const uint8_t *input,
                    struct abyss_hash_256_s *s);

void abyss_hash_256_initialize(const unsigned long input_count,
                               const uint8_t *input,
                               struct abyss_hash_256_s *s);

void abyss_hash_256_transform(unsigned long i, const unsigned long input_count,
                              const uint8_t *input, struct abyss_hash_256_s *s);

void abyss_hash_256_finalize(struct abyss_hash_256_s *s);

#endif
