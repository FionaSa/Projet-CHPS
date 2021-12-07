#include "gene.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int n = 1000;

unsigned int* alea_gen(){
    unsigned int* gene = malloc(n* sizeof(int));

    srand(getpid());


    for (int i = 0; i < n ; i++ )
    {   
        gene[i] = rand()%2; 
       // printf(" %d",gene[i]);

    }
    return gene;
}


 int* test_gen(){
      int* gene= calloc(sizeof(int*),MAX_GENES);
    

    //Example of a gene so the gene map register it 
    gene[0] = 000011011100;


    return gene;  
}

void print_test(gene_map_t *gene_map)
{
    printf("Début print de test\n");
    for( long long i = 0; i < gene_map->genes_counter; i ++)
    {
        printf("Gene \x1b[31m%lld\x1b[0m: \x1b[32m[%lld:%lld]\x1b[0m\n",i,gene_map->gene_start[i],gene_map->gene_end[i]);
    }
}

int main(){

     int* gene= test_gen();
    
    // int* gene= alea_gen();


   gene_map_t gene_map;

    gene_map.genes_counter = 0;

    gene_map.gene_end = calloc(sizeof(int*),MAX_GENES);

    gene_map.gene_start = calloc(sizeof(int*),MAX_GENES);

    detecting_genes(gene,13,&gene_map);

    //Test print 

    print_test(&gene_map);

    return 0;

}