# dna-hash2: A header-only C library for hashing DNA sequences

### Quick Start
1. Clone this repo
2. Include dna_hash2.h

## Overview
`dna-hash2` is a header-only C library for fast hashing of DNA sequences using a 2-bit encoding.

Example for a short sequence to a 32-bit integer:
```C
const char* seq = "ATGCATGCATGCATGC";
int slength = 16;

dna32_t hash = hash32_dna(seq, slength);
```

Example computing the hashes of all k-mers in a short sequence:
```C
const char* seq = "ATGC...";
int seqlen = 100;
int klen   = 16;

for (int i = 0; i < seqlen - klen; i++) {
  dna32_t kmer = kmer32_dna(seq, seqlen, klen, i);
}
```

Example computing the minimizer for each k-mer in a short sequence:
```C
const char* seq = "ATGC...";
int seqlen = 100;
int klen   = 16;
int mlen   = 11;

for (int i = 0; i < seqlen - klen; i++) {
  dna32_t mmer = minimizer32_dna(seq, seqlen, i, klen, mlen);
}
```
