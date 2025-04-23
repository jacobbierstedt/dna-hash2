/*
  dna-hash2: A header-only C library for fast hashing of short DNA sequences
*/

#ifndef DNA_HASH2_H
#define DNA_HASH2_H

#include <stdint.h>

#ifndef DNA32_T
#define DNA32_T
typedef uint32_t dna32_t;
#endif

#ifndef DNA64_T
#define DNA64_T
typedef uint64_t dna64_t;
#endif

#define DEFAULT_KMASK 0x07
#define DEFAULT_MAX_64 0xFFFFFFFFFFFFFFFF
#define DEFAULT_MAX_32 0xFFFFFFFF

                                    /*  A     C  T        G*/
static const uint8_t dna_8[8]     = {4, 0, 4, 1, 3, 4, 4, 2};
static const uint8_t rev_dna_8[8] = {4, 3, 4, 2, 0, 4, 4, 1};
#define _DNA_8_MASK 0x07

#define ENCODE(c)    dna_8[c & _DNA_8_MASK]  //; printf("%c %u %u\n",c, c & _DNA_8_MASK, dna_8[c & _DNA_8_MASK] )
#define ENCODE_RC(c) rev_dna_8[c & _DNA_8_MASK] 
#define ENCODE_BASE(mask, base) mask<<=2; mask |= ENCODE(base)
#define ENCODE_REV(mask, base)  mask<<=2; mask |= ENCODE_RC(base)

/*
  Hash DNA sequence as 32-bit integer.
  This function takes a DNA sequence and its length and
  returns a unsigned long long integer that represents
  the sequence. It uses 2-bit encoding and works for 
  sequences up to 16 bp.
*/
static inline dna32_t hash32_dna(const char* seq, int seqlen)
{
  dna32_t mask = DEFAULT_KMASK;
  for (int i = 0; i < seqlen; i++) {
    ENCODE_BASE(mask, seq[i]);
  }
  return mask;
}

static inline dna32_t hash32_dna_rc(const char* seq, int seqlen)
{
  dna32_t mask = DEFAULT_KMASK;
  for (int i = seqlen; i > 0; i--) {
    ENCODE_REV(mask, seq[i-1]);
  }
  return mask;
}
/*
  Hash DNA sequence as 64-bit integer.
  This function takes a DNA sequence and its length and
  returns a unsigned long long integer that represents
  the sequence. It uses 2-bit encoding and works for 
  sequences up to 32 bp.
*/
static inline dna64_t hash64_dna(const char* seq, int seqlen)
{
  dna64_t mask = DEFAULT_KMASK;
  for (int i = 0; i < seqlen; i++) {
    ENCODE_BASE(mask, seq[i]);
  }
  return mask;
}

static inline dna64_t hash64_dna_rc(const char* seq, int seqlen)
{
  dna64_t mask = DEFAULT_KMASK;
  for (int i = seqlen; i > 0; i--) {
    ENCODE_REV(mask, seq[i-1]);
  }
  return mask;
}

/*
  Hash a k-mer of length k to a 32-bit integer at a given position.
*/
static inline dna32_t kmer32_dna(const char* seq, int seqlen, int k, int kstart)
{
  dna32_t kmer = DEFAULT_KMASK;
  for (int i = kstart; i < kstart + k; i++) {
    ENCODE_BASE(kmer, seq[i]);
  }
  return kmer;
}

/*
  Compute the minimizer of length m for a k-mer of length k at a
  given position.
*/
static inline dna32_t minimizer32_dna(const char* seq, int seqlen, int kstart, int k, int m)
{
  dna32_t mini = DEFAULT_MAX_32;
  for (int i = kstart; i < k + k - m + 1; i++) {
    dna32_t mhash = kmer32_dna(seq, seqlen, m, i);
    if (mhash < mini) {
      mini = mhash;
    }
  }
  return mini;
}

#undef ENCODE_BASE
#undef ENCODE_REV

#endif /* DNA_HASH2_H */