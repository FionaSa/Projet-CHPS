#pragma once 
#define MAX_GENES  1024

typedef struct gene_map_s {

    //
    unsigned long long genes_counter;

    //Gene start position (AUG)
    unsigned long long* gene_start;

    //Gene stop position (UAA, UAG, UGA)
    unsigned long long* gene_end;

}gene_map_t;

typedef struct codon {
    char* codon;
    char* short_name;
    char* full_name;
    char symbol;
}codon;

typedef struct mutation_map {
    unsigned long long *size;
    unsigned long long *start_mut;
    unsigned long long *end_mut;
}mutation_map;

//extern struct gene_map_s gene_map;
unsigned short* convert_to_binary(char* dna_seq, unsigned size);
char* binary_to_codon(unsigned short* bin_dna_seq, unsigned size);
char* generating_mRNA(const unsigned short gene_seq [], const unsigned int seq_size);
void detecting_genes(const unsigned short gene [], const unsigned int gene_size, gene_map_t* gene_map);
char* generating_amino_acid_chain(const unsigned short gene_seq [], const unsigned int seq_size);
void detecting_mutations(const unsigned short gene_seq [], const unsigned long long size_sequence, mutation_map mut_m);
float calculating_matching_score(const unsigned short seq1 [], const int sequence_size1, const unsigned short seq2 [], const int sequence_size2);
int binary_size_count(int b);
int hamming(int seq1, int seq2);