#pragma once 

#define MAX_GENES  1024
// Number of bits in an integer
#define int_SIZE 31

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


/********** BINARIES FUNCTION **********/

int get_binary_value(const unsigned int *seq_bin, const int pos);
unsigned int* change_binary_value(unsigned int *seq_bin, const int pos, const int value);
unsigned int* set_binary_array(const char *array, const unsigned size);
unsigned int* xor_binary_array(const unsigned int *seq1, const unsigned array_size1,
                                const unsigned int *seq2, const unsigned array_size2);
int popcount_binary_array(const unsigned int *seq, const unsigned int size);


/******** DNA & GENES FUNCTION *********/

unsigned int* convert_to_binary(const char* dna_seq, const unsigned size);
char* binary_to_dna(unsigned int* bin_dna_seq, const unsigned size);
char* generating_mRNA(const unsigned int* gene_seq, const unsigned int seq_size);
void detecting_genes(const unsigned int *gene, const unsigned int gene_size,
                     gene_map_t* gene_map);
char* generating_amino_acid_chain(const unsigned int *gene_seq, const unsigned int seq_size);
void detecting_mutations(const unsigned int *gene_seq, const unsigned int size_sequence,
                         mutation_map mut_m);
float calculating_matching_score(const unsigned int *seq1, const int sequence_size1,
                                 const unsigned int *seq2, const int sequence_size2);


