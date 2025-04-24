# dna-hash2: A lightweight, header-only C library for hashing DNA sequences

## Overview
`dna-hash2` is a header-only C library for fast hashing of DNA sequences using a 2-bit encoding. At its core, it provides the
functionality to store short DNA sequences as integers in a tiny, portable library with a convenient API.

It has functions that perform various features:
- 2-bit encoding short DNA sequences and hashing to fixed-width integers
- Hashing k-mers and computing minimizers
- De-coding the hashed sequence

### Quick Start
1. Clone this repo
2. Include dna_hash2.h
3. `DNA_HASH2_INIT()` in your implementation


## API Reference
### Types
For clarity, dna-hash2 uses two integer types:


`typedef uint32_t dna32_t`
and
`typedef uint64_t dna64_t`


### Functions
|Function|Description|
|----|----|
|`dna32_t hash_dna32_t(const char* seq, int seqlen)`|Return a unsigned int from a DNA sequence with length <= 16|
|`dna64_t hash_dna64_t(const char* seq, int seqlen)`|Return a unsigned long long from a DNA sequence with length <= 32|
|`dna32_t hash_dna32_t_rc(const char* seq, int seqlen)`|Return a unsigned int from the reverse-complement of a DNA sequence with length <= 16|
|`dna64_t hash_dna64_t_rc(const char* seq, int seqlen)`|Return a unsigned long long from the reverse-complement of a DNA sequence with length <= 32|
|`dna32_t kmer_dna32_t(const char* seq, int seqlen, int k, int kstart)`|Return the hash of a k-mer at position kstart|
|`dna64_t kmer_dna64_t(const char* seq, int seqlen, int k, int kstart)`|Return the hash of a k-mer at position kstart|
|`dna32_t minimizer_dna32_t(const char* seq, int seqlen, int kstart, int k, int m)`|Return the hash of the m-length minimizer of k-mer at position kstart|
|`dna64_t minimizer_dna64_t(const char* seq, int seqlen, int kstart, int k, int m)`|Return the hash of the m-length minimizer of k-mer at position kstart|
|`void decode_dna32_t(dna32_t hash, int len, char* seq)`|Decode DNA hash from unsigned int to its original sequence|
|`void decode_dna64_t(dna32_t hash, int len, char* seq)`|Decode DNA hash from unsigned long long to its original sequence|


## Examples

How to include:
```C
#include "dna_hash2.h"
DNA_HASH_INIT()
```

Example for a short sequence to a 32-bit integer:
```C
const char* seq = "ATGCATGCATGCATGC";
int slength = 16;

dna32_t hash = hash_dna32_t(seq, slength);
```

Example computing the hashes of all k-mers in a short sequence:
```C
const char* seq = "ATGC...";
int seqlen = 100;
int klen   = 16;

for (int i = 0; i < seqlen - klen; i++) {
  dna32_t kmer = kmer_dna32_t(seq, seqlen, klen, i);
}
```

Example computing the minimizer for each k-mer in a short sequence:
```C
const char* seq = "ATGC...";
int seqlen = 100;
int klen   = 16;
int mlen   = 11;

for (int i = 0; i < seqlen - klen; i++) {
  dna32_t mmer = minimizer_dna32_t(seq, seqlen, i, klen, mlen);
}
```
## Citation
If you do choose to use dna-hash2 in your work, please cite:


> Bierstedt, J. *dna-hash2: A lightweight, header-only C library for hashing DNA sequences*, 2025.
> Available at: https://github.com/jacobbierstedt/dna-hash2



