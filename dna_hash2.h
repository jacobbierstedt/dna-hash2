/*
MIT License

Copyright (c) 2025 Jacob Bierstedt

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/


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



/*
  Macros for initializing 32-bit and 64-bit functions
*/
#define DNA_HASH2_INIT_32() \
  __HASH_DNA(dna32_t) \
  __HASH_DNA_RC(dna32_t) \
  __KMER_DNA(dna32_t) \
  __MINIMIZER_DNA(dna32_t) \
  __DECODE_DNA(dna32_t)

#define DNA_HASH2_INIT_64() \
  __HASH_DNA(dna64_t) \
  __HASH_DNA_RC(dna64_t) \
  __KMER_DNA(dna64_t) \
  __MINIMIZER_DNA(dna64_t) \
  __DECODE_DNA(dna64_t)

#define DNA_HASH2_INIT() \
  DNA_HASH2_INIT_64() \
  DNA_HASH2_INIT_32()


#define DEFAULT_KMASK 0x00
#define _DNA_8_MASK 0x07
                                    /*  A     C  T        G*/
static const uint8_t dna_8[8]     = {4, 0, 4, 1, 3, 4, 4, 2};
static const uint8_t rev_dna_8[8] = {4, 3, 4, 2, 0, 4, 4, 1};
static const uint8_t dec_dna_8[8] = {'A', 'C', 'G', 'T', 'N'};

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

#define __HASH_DNA(dna_type_t) \
  static inline dna_type_t hash_##dna_type_t(const char* seq, int seqlen) \
  { \
    dna_type_t mask = DEFAULT_KMASK; \
    for (int i = 0; i < seqlen; i++) { \
      ENCODE_BASE(mask, seq[i]); \
    } \
    return mask; \
  }

#define __HASH_DNA_RC(dna_type_t) \
  static inline dna_type_t hash_##dna_type_t##_rc(const char* seq, int seqlen) \
  { \
    dna_type_t mask = DEFAULT_KMASK; \
    for (int i = seqlen; i > 0; i--) { \
      ENCODE_REV(mask, seq[i-1]); \
    } \
    return mask; \
  }

/*
  Hash a k-mer of length k to a 32-bit integer at a given position.
*/

#define __KMER_DNA(dna_type_t) \
  static inline dna_type_t kmer_##dna_type_t(const char* seq, int seqlen, int k, int kstart) \
  { \
    dna_type_t kmer = DEFAULT_KMASK; \
    for (int i = kstart; i < kstart + k; i++) { \
      ENCODE_BASE(kmer, seq[i]); \
    } \
    return kmer; \
  }

/*
  Compute the 64-bit minimizer of length m for a k-mer of length k at a
  given position. Max minimizer length is 32.
*/
#define __MINIMIZER_DNA(dna_type_t) \
static inline dna_type_t minimizer_##dna_type_t(const char* seq, int seqlen, int kstart, int k, int m) \
{ \
  dna_type_t mini = UINT64_MAX; \
  for (int i = kstart; i < kstart + k - m + 1; i++) { \
    dna_type_t mhash = kmer_##dna_type_t(seq, seqlen, m, i); \
    if (mhash < mini) { \
      mini = mhash; \
    } \
  } \
  return mini; \
}

/*
  Decode a 64- or 32-bit integer back to the original char array
*/
#define __DECODE_DNA(dna_type_t) \
  static inline void decode_##dna_type_t(dna_type_t hash, int len, char* s) \
  { \
    for (int i = len - 1; i >= 0; i--) { \
      s[i] = dec_dna_8[hash & 3]; \
      hash >>= 2; \
    } \
  }

#endif /* DNA_HASH2_H */