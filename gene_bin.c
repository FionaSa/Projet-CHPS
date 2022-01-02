#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "gene_bin.h"


/***************************************/
/********** BINARIES FUNCTION **********/
/***************************************/


/**
 * in : seq_bin : "binary array"
 * in : pos : position of the wanted bit (0 <= pos < size_seq * 2)
 * out : int : the wanted bit
 */
int get_binary_value(const long int *seq_bin, const int pos){
    int new_pos = pos > int_SIZE ? pos / int_SIZE : 0;
    return seq_bin[new_pos] & (1 << (pos - new_pos)) ? 1 : 0;
}

/**
 * in : seq_bin : "binary array"
 * in : pos : position of the bit to be replaced (0 <= pos < size_seq * 2)
 * in : value : the bit to replace
 * out : seq_bin : "binary array" modified
 */
long int* change_binary_value(long int *seq_bin, const int pos, const int value){
    // value = 1 or 0
    // ~(1000) = (0001)
    int new_pos = pos > int_SIZE ? pos / int_SIZE : 0;

    if (value)
        seq_bin[new_pos] |= (1 << (pos - new_pos));
    else
        seq_bin[new_pos] &= ~(1 << (pos - new_pos));
    return seq_bin;
}

/**
 * in : seq_char : the DNA seq in it's char* mode
 * in : seq_size : size of the array 'seq_char' = number of nucleotides
 * out : seq_bin : "binary array" filled
 */
long int* set_binary_array(const char *seq_char, const unsigned seq_size){
    int seq_bin_size = 2 * seq_size;
    int nb = seq_bin_size / int_SIZE;

    if(seq_bin_size % int_SIZE != 0)
        nb++;
    long int* seq_bin = NULL;
    seq_bin = calloc(nb, sizeof(long int));

    int pos = 0;
    for (long int i = 0; i < seq_size; ++i)
    {
        switch(seq_char[i]){
        case 'A':
            // A = 00
            break;
        case 'T':
            // T = 11
            change_binary_value(seq_bin, pos, 1);
            change_binary_value(seq_bin, pos + 1, 1);
            break;
        case 'G':
            // G = 01
            change_binary_value(seq_bin, pos + 1, 1);
            break;
        case 'C':
            // C = 10
            change_binary_value(seq_bin, pos, 1);
            break;
        case 'N':
            // N = A = 00
            break;
        case 'R':
            // R = A = 00
            break;
        case 'Y':
            // Y = C = 10
            change_binary_value(seq_bin, pos, 1);
            break;
        case 'K':
            // K = G = 01
            change_binary_value(seq_bin, pos + 1, 1);
            break;
        case 'M':
            // M = A = 00
            break;
        case 'S':
            // S = C = 10
            change_binary_value(seq_bin, pos, 1);
            break;
        case 'W':
            // W = A = 00
            break;
        case 'B':
            // B = C = 10
            change_binary_value(seq_bin, pos, 1);
            break;
        case 'D':
            // D = A = 00
            break;
        case 'H':
            // H = G = 01
            change_binary_value(seq_bin, pos + 1, 1);
            break;
        case 'V':
            // V = A = 00
            break;
        }
        pos += 2;
    }
    return seq_bin;
}

/**
 * in : seq_bin1 : first sequence to xor: "binary array"
 * in : seq_size1 : number total of used bits in the sequence seq_bin1
 * in : seq_bin2 : second sequence to xor: "binary array"
 * in : seq_size2 : number total of used bits in the sequence seq_bin2
 * out : xor : "binary array" which is the result of the xor operation beteween seq1 and seq2
 */
long int* xor_binary_array(const long int *seq_bin1, const unsigned seq_size1,
                                const long int *seq_bin2, const unsigned seq_size2){

    // "nb" = number of 'int' in the arrays 'seq1' and 'seq2' 
    //      = size of the 'long int*' arrays
    int nb_seq1 = seq_size1 / int_SIZE;
    if(seq_size1 % int_SIZE != 0)   nb_seq1++;
    int nb_seq2 = seq_size2 / int_SIZE;
    if(seq_size2 % int_SIZE != 0)   nb_seq2++;

    long int max_nb = nb_seq1 >= nb_seq2 ? nb_seq1 : nb_seq2;

    long int max_size = seq_size1 >= seq_size2 ? seq_size1 : seq_size2;
    long int min_size = seq_size1 >= seq_size2 ? seq_size2 : seq_size1;
    long int diff_size = max_size - min_size;

    long int *xor = NULL;
    xor = calloc(max_nb, sizeof(*xor));


    // If the sequences don't have the same size, do (with x = 1 or 0):

    //  xxxxxxxxx
    // ^
    //  000xxxxxx
    // -----------
    //  xxxxxxxxx

    // And, 0 ^ x = x

    int bit = 0;
    if(max_size == seq_size1){
        for (long int i = 0; i < diff_size; ++i){
           bit = get_binary_value(seq_bin1, i);
           xor = change_binary_value(xor, i, bit);
        }
        for (long int i = diff_size; i < max_size; ++i){
           bit = get_binary_value(seq_bin1, i) ^ get_binary_value(seq_bin2, i - diff_size);
           xor = change_binary_value(xor, i, bit);
        }
    }
    else{
        for (long int i = 0; i < diff_size; ++i){
           bit = get_binary_value(seq_bin2, i);
           xor = change_binary_value(xor, i, bit);
        }
        for (long int i = diff_size; i < max_size; ++i){
           bit = get_binary_value(seq_bin1, i - diff_size) ^ get_binary_value(seq_bin2, i);
           xor = change_binary_value(xor, i, bit);
        }
    }
    return xor;
}

/**
 * in : seq_bin : "binary array"
 * in : seq_size : number total of used bits in the sequence
 * out : s : popcount of the seq : number of '1'
 */
int popcount_binary_array(const long int *seq_bin, const long int seq_size){
    int s = 0;

    int nb = seq_size / int_SIZE;
    if(seq_size % int_SIZE != 0)    nb++;

    for (int i = 0; i < nb; ++i)
        s += __builtin_popcount(seq_bin[i]);

    return s;
}

long int mask_binary_array(const long int seq_bin, const long int pos_start, const long int size) {
    // printf("seq_bin : %d, start : %d, size : %d\n", seq_bin, pos_start, size);
    long int res;

    res = seq_bin << ((int_SIZE+1) - size - pos_start);
    res = res & 0b11111111111111111111111111111111;
    res = res >> ((int_SIZE+1) - size);
    // res = res << pos_start;

    // printf("return %d\n", res);
    return res;
}

long int* get_piece_binary_array(const long int* seq_bin, const long int seq_size, const long int pos_start, const long int size){
    long int *res;

    long int intsize = int_SIZE + 1;

    long int seq_start = seq_size - 1 - pos_start/(intsize);
    long int seq_stop = seq_size - 1 - (pos_start+size)/(intsize);

    long int array_size = (size) / intsize + (size % intsize != 0);
    // printf("array_size : %ld\n", array_size);

    res = calloc(array_size, sizeof(*seq_bin));

    long int relative_start;
    long int relative_size;

    long int it = 0;
    long int i = seq_start;
    long int val = 0;
    long int res_p = 0;
    long int relative_space_left = 0;
    long int writen_so_far = 0;

    // printf("seq_size : %ld, pos_start : %ld, size : %ld\n", seq_size, pos_start, size);
    // printf("seq_start : %ld, seq_stop : %ld\n", seq_start, seq_stop);

    while(i != seq_stop-1){
        // printf("FOR : %ld, %ld, %ld\n", i, seq_start, seq_stop);
        relative_start = i == seq_start ? pos_start % (intsize) : 0;
        // relative_size = size - it * (intsize) + relative_start % (intsize) + pos_start % (intsize);
        relative_size = size - writen_so_far;
        relative_size = relative_size > (intsize) ? (intsize) - relative_start : relative_size;
        val = mask_binary_array(*(seq_bin + i), relative_start, relative_size);
        // printf("i : %ld, it : %ld, *(seq_bin + i) : %ld, r_start : %ld, r_size : %ld, val : %ld\n", i, it, *(seq_bin + i), relative_start, relative_size, val);

        res_p = array_size - it - 1;
        // printf("res_p : %ld\n", res_p);
        if (i == seq_start){
            *(res + res_p) = val; // Première itération
            // printf("première it : res+res_p = %ld (%ld)\n", *(res + res_p), val);
            writen_so_far += relative_size;
            // printf("writen_so_far / relative_size : %ld\n", writen_so_far);
        }
        else{
            // printf("relative_space_left : %ld", relative_space_left);
            relative_space_left = intsize - (writen_so_far % intsize == 0 ? intsize : writen_so_far % intsize);
            if (relative_space_left) {
                // *(res + res_p+1) = *(res + res_p+1) | ((mask_binary_array(val, 0, relative_space_left) << intsize - relative_space_left));
                *(res + res_p + 1) = *(res + res_p + 1) | (mask_binary_array(val, 0, relative_space_left) << (intsize-relative_space_left));
                // printf("val : %ld, mask : %ld, << %ld\n", val, mask_binary_array(val, 0, relative_space_left), writen_so_far % intsize);
                // printf("mask << : %ld, res+%ld : %ld\n", mask_binary_array(val, 0, relative_space_left) << (intsize - relative_space_left), res_p+1, *(res + res_p + 1));
                writen_so_far += relative_space_left;
                // printf("writen_so_far / relative_size : %ld\n", writen_so_far);
            }
            *(res + res_p) = val >> relative_space_left;
            // printf("*(res + res_p(%ld)) : %ld\n", res_p, *(res + res_p));
            // relative_space_left = intsize - relative_size;
            writen_so_far += relative_size - relative_space_left;
        }
        it++;
        i--;
    }
    return res;
}




/***************************************/
/******** DNA & GENES FUNCTION *********/
/***************************************/

//////////////// Convert to binary
/**
 * in : dna_seq : array of char
 * in : size : size of dna_seq = number of nucleotides (= number of letter)
 * out : seq : array of int
 * Convert a char DNA sequence to its binary sequence
 */
long int* convert_to_binary(const char* dna_seq, const unsigned size){
    return set_binary_array(dna_seq, size);
}

//////////////// Convert binary aa to codon
/**
 * in : bin_dna_seq : long int array
 * in : size : number total of used bits in bin_dna_seq
 * out : dna_seq : array of binary
 * Convert a binary sequence to its DNA bases
 */
char* binary_to_dna(long int* bin_dna_seq, const unsigned size){
    if (size % 2 != 0) {
        printf("Error: binary_to_aa : wrong binary size (%d). Must be odd.\nExit.\n",size);
        return NULL;
    }

    char* dna_seq = calloc((size / 2) + 1, sizeof(*dna_seq));

    int j = 0;
    for (unsigned i = 0; i < size; i += 2){
        // nucleotides = A, T/U, G, C
        int nucl1 = get_binary_value(bin_dna_seq, i);
        int nucl2 = get_binary_value(bin_dna_seq, i + 1);

        if (nucl1 == 0 && nucl2 == 0)
            // 00 = A/N
            dna_seq[j] = 'A';
        else if (nucl1 == 1 && nucl2 == 1)
            // 11 = T
            dna_seq[j] = 'T';
        else if (nucl1 == 1 && nucl2 == 0)
            // 10 = C
            dna_seq[j] = 'C';
        else if (nucl1 == 0 && nucl2 == 1)
            // 01 = G
            dna_seq[j] = 'G';
        j++;
    }
    return dna_seq;
}

//////////////// Generating mRNA
/**
 * in : gene_seq : long int array : "binary array"
 * in : seq_size : size of gene_seq : number of used bits in gene_seq
 * out : rna_seq : array of char
 * Convert a binary DNA sequence to a string mRNA sequence
 */
char* generating_mRNA(const long int* gene_seq, const long int seq_size) {
    // Check the input argument
    if (!gene_seq)
        return printf("ERROR: generating_mRNA: undefined sequence\n"), NULL;

    // Create and check the output
    char* rna_seq = NULL;
    rna_seq = malloc(sizeof(*rna_seq) * (seq_size / 2) + 1);
    if (!rna_seq)
        return printf("ERROR: generating_mRNA: cannot allocate memory\n"), NULL;

    int j = 0;
    // Parse the binary DNA sequence two by two
    for (long int i = 0; i < seq_size; i += 2) {

        // nucleotides = A, T/U, G, C
        int nucl1 = get_binary_value(gene_seq, i);
        int nucl2 = get_binary_value(gene_seq, i + 1);

        if (nucl1 == 0 && nucl2 == 0)
            // 00 = A
            rna_seq[j] = 'A';
        else if (nucl1 == 1 && nucl2 == 1)
            // 11 = U
            rna_seq[j] = 'U';
        else if (nucl1 == 1 && nucl2 == 0)
            // 10 = C
            rna_seq[j] = 'C';
        else if (nucl1 == 0 && nucl2 == 1)
            // 01 = G
            rna_seq[j] = 'G';
        else
            return printf("ERROR: generating_mRNA: invalid value in DNA sequence\n"), NULL;
        j++;
    }
    rna_seq[j] = '\0';
    return rna_seq;
}

//////////////// Detecting genes 
/**
* in : gene : long int array : "binary array"
* in : gene_size : size of gene : number of used bits in gene
* in : gene_map : struct to map the genes
* out : void
* Detect if a gene exists in the sequence and insert it in the structure
*/
void detecting_genes(const long int *gene, const long int gene_size, gene_map_t* gene_map) {
    //struct gene_map_s gene_map;
    gene_map->genes_counter = 0;

    // Check if memory ever have been allocated, do it if not
    if(!gene_map->gene_start || !gene_map->gene_end){
        gene_map->gene_start = malloc(sizeof(*gene_map->gene_start) * MAX_GENES);
        gene_map->gene_end = malloc(sizeof(*gene_map->gene_end) * MAX_GENES);

        if (!gene_map->gene_start || !gene_map->gene_end){
            printf("ERROR: detecting_genes: cannot allocate memory\n");
            return;
        }
    }


    int start_pos = -1;

    long int i = 0;

    while ((i + 6) <= gene_size) {
        // nucleotides = A, T/U, G, C
        int nucl1 = get_binary_value(gene, i);
        int nucl2 = get_binary_value(gene, i + 1);
        int nucl3 = get_binary_value(gene, i + 2);
        int nucl4 = get_binary_value(gene, i + 3);
        int nucl5 = get_binary_value(gene, i + 4);
        int nucl6 = get_binary_value(gene, i + 5);

        //If a start pos and a stop pos doesn't exist, search for AUG
        // if (!(gene[i%32] & ( 1 << (i%32) ))
        if (nucl1 == 0 && nucl2 == 0 && nucl3 == 1 
            && nucl4 == 1 && nucl5 == 0 && nucl6 == 1) {
        //if atc, it's the start of a gene
            start_pos = i;
            i += 6;
        }
        else{

            if (start_pos != -1 ) {
                //if a start pos exists , search for UAA / UAG / UGA
                if ((nucl1 == 1 && nucl2 == 1 && nucl3 == 0) 
                    && ((nucl4 == 0 && nucl5 == 0 && nucl6 == 0)
                        || (nucl4 == 0 && nucl5 == 0 && nucl6 == 1)
                        || (nucl4 == 1 && nucl5 == 0 && nucl6 == 0))) {
                   //It's the end of a gene          
                   //If a start pos and an stop pos has been found, a gene exists so we save it in the struc
                    gene_map->gene_start[gene_map->genes_counter] = start_pos;
                    gene_map->gene_end[gene_map->genes_counter] = i+5;

                    gene_map->genes_counter++;

                    start_pos = -1;
                    i += 6;
                }
                else
                    i += 2;
            }
            else
                i += 2;
        }
    }

}

/**
 * in : gene_seq : long int array : "binary array"
 * in : seq_size : size of gene_seq : number of used bits in gene_seq
 * out : char* : protein in symbols
 * The program parses the mRNA sequence, verify its length and if the first codon is a START codon.
*/
char* generating_amino_acid_chain(const long int *gene_seq, const long int seq_size) {
    short codon_size = 6;
    // Check the input argument
    if (!gene_seq)
        return printf("ERROR: generating_amino_acid_chain: undefined sequence\n"), NULL;
    if(seq_size % 3 != 0)
        return printf("ERROR: generating_amino_acid_chain: bad size\n"), NULL;

    // Create and check the output
    char* aa_seq = NULL;
    // aa_seq = malloc(sizeof(*aa_seq) * (seq_size / codon_size) + 1);
    aa_seq = calloc((seq_size / codon_size) + 1, sizeof(*aa_seq));
    if (!aa_seq)
        return printf("ERROR: generating_amino_acid_chain: cannot allocate memory\n"), NULL;

    unsigned temp = 0;

    for (long int i = 0; i < seq_size; i += codon_size) {
        // The hash functions, takes the 6 bits, and transform the array into an integer.
        // The integer first char is a 2, for hash generation purposes.
        int hash = 2;
        for(long int k = i; k < i + codon_size; k++){
            hash = 10 * hash + get_binary_value(gene_seq, k);
        }

        // Switch over the hash.
        switch(hash){
        case 2000000 :
            aa_seq[temp] = 'K';
            break;
        case 2000001 :
            aa_seq[temp] = 'K';
            break;
        case 2000010 :
            aa_seq[temp] = 'N';
            break;
        case 2000011 :
            aa_seq[temp] = 'N';
            break;
        case 2000100 :
            aa_seq[temp] = 'R';
            break;
        case 2000101 :
            aa_seq[temp] = 'R';
            break;
        case 2000110 :
            aa_seq[temp] = 'S';
            break;
        case 2000111 :
            aa_seq[temp] = 'S';
            break;
        case 2001000 :
            aa_seq[temp] = 'T';
            break;
        case 2001001 :
            aa_seq[temp] = 'T';
            break;
        case 2001010 :
            aa_seq[temp] = 'T';
            break;
        case 2001011 :
            aa_seq[temp] = 'T';
            break;
        case 2001100 :
            aa_seq[temp] = 'I';
            break;
        case 2001101 :
            aa_seq[temp] = 'M';
            break;
        case 2001110 :
            aa_seq[temp] = 'I';
            break;
        case 2001111 :
            aa_seq[temp] = 'I';
            break;
        case 2010000 :
            aa_seq[temp] = 'E';
            break;
        case 2010001 :
            aa_seq[temp] = 'E';
            break;
        case 2010010 :
            aa_seq[temp] = 'D';
            break;
        case 2010011 :
            aa_seq[temp] = 'D';
            break;
        case 2010100 :
            aa_seq[temp] = 'G';
            break;
        case 2010101 :
            aa_seq[temp] = 'G';
            break;
        case 2010110 :
            aa_seq[temp] = 'G';
            break;
        case 2010111 :
            aa_seq[temp] = 'G';
            break;
        case 2011000 :
            aa_seq[temp] = 'A';
            break;
        case 2011001 :
            aa_seq[temp] = 'A';
            break;
        case 2011010 :
            aa_seq[temp] = 'A';
            break;
        case 2011011 :
            aa_seq[temp] = 'A';
            break;
        case 2011100 :
            aa_seq[temp] = 'V';
            break;
        case 2011101 :
            aa_seq[temp] = 'V';
            break;
        case 2011110 :
            aa_seq[temp] = 'V';
            break;
        case 2011111 :
            aa_seq[temp] = 'V';
            break;
        case 2100000 :
            aa_seq[temp] = 'Q';
            break;
        case 2100001 :
            aa_seq[temp] = 'Q';
            break;
        case 2100010 :
            aa_seq[temp] = 'H';
            break;
        case 2100011 :
            aa_seq[temp] = 'H';
            break;
        case 2100100 :
            aa_seq[temp] = 'R';
            break;
        case 2100101 :
            aa_seq[temp] = 'R';
            break;
        case 2100110 :
            aa_seq[temp] = 'R';
            break;
        case 2100111 :
            aa_seq[temp] = 'R';
            break;
        case 2101000 :
            aa_seq[temp] = 'P';
            break;
        case 2101001 :
            aa_seq[temp] = 'P';
            break;
        case 2101010 :
            aa_seq[temp] = 'P';
            break;
        case 2101011 :
            aa_seq[temp] = 'P';
            break;
        case 2101100 :
            aa_seq[temp] = 'L';
            break;
        case 2101101 :
            aa_seq[temp] = 'L';
            break;
        case 2101110 :
            aa_seq[temp] = 'L';
            break;
        case 2101111 :
            aa_seq[temp] = 'L';
            break;
        case 2110000 :
            aa_seq[temp] = 'O';
            break;
        case 2110001 :
            aa_seq[temp] = 'O';
            break;
        case 2110010 :
            aa_seq[temp] = 'Y';
            break;
        case 2110011 :
            aa_seq[temp] = 'Y';
            break;
        case 2110100 :
            aa_seq[temp] = 'O';
            break;
        case 2110101 :
            aa_seq[temp] = 'W';
            break;
        case 2110110 :
            aa_seq[temp] = 'C';
            break;
        case 2110111 :
            aa_seq[temp] = 'C';
            break;
        case 2111000 :
            aa_seq[temp] = 'S';
            break;
        case 2111001 :
            aa_seq[temp] = 'S';
            break;
        case 2111010 :
            aa_seq[temp] = 'S';
            break;
        case 2111011 :
            aa_seq[temp] = 'S';
            break;
        case 2111100 :
            aa_seq[temp] = 'L';
            break;
        case 2111101 :
            aa_seq[temp] = 'L';
            break;
        case 2111110 :
            aa_seq[temp] = 'F';
            break;
        case 2111111 :
            aa_seq[temp] = 'F';
            break;

        default:
            return printf("ERROR: generating_amino_acid_chain: invalid value (%d) in RNA sequence\n", hash), NULL;
        }
    
        temp++;
    }

    aa_seq[temp] = '\0';
    return aa_seq;
}


/**
* in : gene_seq : sequence of the gene : "binary array"
* in : size_sequence : size of the sequence : number of used bits in gene_seq
* in : mut_m : map of the possible mutation's areas
* out : boolean
* The algorithm runs through a gene sequence and detects if there is a sequence with a high GC frequency
* (at least 1/5th of the gene sequence's size) it returns true, else it returns false.
* Precondition: gene_seq is of size size_sequence.
*/
void detecting_mutations(const long int *gene_seq, const long int size_sequence,
                         mutation_map mut_m) {
    long int detect_mut = 0;  //Counting size of GC sequence
    unsigned short tmp_start_mut = 0;   //stock start mutation
    unsigned cmp = 0;   //counter of all mutation zones

    //Read the sequence
    for (long int i = 0; i < size_sequence; i += 2) {

        // nucleotides = A, T/U, G, C
        int nucl1 = get_binary_value(gene_seq, i);
        int nucl2 = get_binary_value(gene_seq, i + 1);

        //Increment detect_mut if find a C or G nucl
        if (((nucl1 == 0) && (nucl2 == 1)) ||
            ((nucl1 == 1) && (nucl2 == 0))) {
            if(detect_mut == 0){tmp_start_mut = i;}
            detect_mut+=2;
        }
        //Put detect_mut to 0 if find a A or T nucl
        else {
            //Check if previous GC sequence is a probable mutation zone
            if (detect_mut >= (size_sequence / 5)) {
                mut_m.start_mut[cmp] = tmp_start_mut;
                mut_m.end_mut[cmp] = i-1;
                mut_m.size[cmp] = detect_mut-1;
                cmp++;
            }
            detect_mut = 0;
        }
    }
    //Check if ending sequence is a probable mutation zone
    if (detect_mut >= (size_sequence / 5)) {
        mut_m.start_mut[cmp] = tmp_start_mut;
        mut_m.end_mut[cmp] = size_sequence-1;
        mut_m.size[cmp] = detect_mut-1;
    }
}

/**
 * in : seq1 : first sequence in binary
 * in : sequence_size1 : number total of used bits in the sequence seq1
 * in : seq2 : second sequence in binary
 * in : sequence_size2 : number total of used bits in the sequence seq2
 * out : float : matching score in %
 * The algorithms runs the hamming distance between two binary sequences, and return their matching score in %
*/
float calculating_matching_score(const long int *seq1, const int seq_size1,
                                 const long int *seq2, const int seq_size2) {
    // Check the input argument
    if (!seq1 || !seq2)
        return printf("ERROR: calculating_matching_score: undefined sequence\n"), -1.0;

    long int *xor = NULL;
    xor = xor_binary_array(seq1, seq_size1, seq2, seq_size2);

    // xor_size = max size
    int xor_size = seq_size1 >= seq_size2 ? seq_size1 : seq_size2;

    int pop = popcount_binary_array(xor, xor_size);

    float y = ((float)pop * 100.0) / (float)xor_size;
    return 100.0 - y;
}
