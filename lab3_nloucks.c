//Cache Sim - Nathan Loucks
//CSC322 - Systems Programming Lab 3

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <math.h>
#include <getopt.h>
#include <ctype.h>

typedef struct Line{
    const int b_size; //block size in bits
    unsigned long long block,tag;
    short v; //valid flag bit
    int l_rate; //use rate
}Line;

typedef struct Set{
    Line *lines;
    int s_rate;
}Set;

typedef struct Cache{
    Set *sets;
    int hit_c,miss_c,evic_c;
    int set_b,block_b,line_per_set,s;
}Cache;

//initialize cache with user input 
void cacheInit(Cache *cache){
    printf("Initializing Cache...\n");
    //init counters
    cache->hit_c = 0;
    cache->miss_c = 0;
    cache->evic_c = 0;

    unsigned long long n_sets = pow(2,cache->set_b); // number of sets in cache = 2^s
    cache->sets = (Set *)malloc(sizeof(Set)*n_sets); //allocate mem for sets
    printf("Mem for sets allocated.\n");

    //Allocate mem for cache lines within each set.
    for(unsigned long long i=0;i<n_sets;i++){
        cache->sets[i].s_rate = 0;
        cache->sets[i].lines = (Line *)malloc(sizeof(Line)*cache->line_per_set);
        //printf("Mem allocated for lines within set: %llu\n",i);
        for(unsigned long long k=0;k<cache->line_per_set;k++){
            cache->sets[i].lines[k].v = 0;
        }
    }
    printf("Cache initialization complete.\n");
}

//DEALLOCATION OF MEM
void dealloc(Cache *cache){
    printf("Deallocating mem...\n");
    unsigned long long n_sets = pow(2,cache->set_b); // number of sets in cache = 2^s
    for(unsigned long long i=0;i<n_sets;i++){
        free(cache->sets[i].lines); //free lines within set
        //printf("Lines in set: %llu deallocated.\n",i);
    }
    free(cache->sets); //free sets after the lines
    printf("Mem deallocation completed.\n");
}

//Query cache for an address (HIT: found in cache = 1, MISSES: not found but has free space = -1, not found and no free space = 0)
int queryCache(unsigned long long address, const Cache *cache){
    unsigned long long index = 0;
    unsigned long long tag_b = 64 - ((cache->s) + (cache->block_b));
    unsigned long long tag = address >> (cache->set_b + cache->block_b); //extract tag
    unsigned long long set = (address << (tag_b)) >> (tag_b + cache->set_b);//extract set idx

    printf("Tag: %llX  Set: %llX ",tag,set);

    //search through cache
    for(unsigned long long i = 0; i < cache->line_per_set; i++){
        if(cache->sets[set].lines[i].v && cache->sets[set].lines[i].tag == tag){ //already in cache 'hit'
            cache->sets[set].lines[i].l_rate++;
            return 1;
            break;
        }else if(!cache->sets[set].lines[i].v){ //valid flag unset, so free space is available
            index = i;
            cache->sets[set].lines[index].tag = tag;
            cache->sets[set].lines[index].v = 1;
            cache->sets[set].lines[index].l_rate++;
            return -1;
            break;
        }else{
            return 0;  // no empty spot, not found in cache 'miss'
        }
    }
    //return result;
}

//EVICT SPOT
void evictData(unsigned long long address, Cache *cache){
    unsigned long long index = 0;
    unsigned long long tag_b = 64 - ((cache->s) + (cache->block_b));
    unsigned long long tag = address >> (cache->set_b + cache->block_b); //extract tag
    unsigned long long set = (address << (tag_b)) >> (tag_b + cache->set_b);//extract set idx

    unsigned long long min_r;
    min_r = cache->sets[set].lines[0].l_rate;

    for(unsigned long long i = 0; i < cache->line_per_set; i++){
        unsigned long long this_r = cache->sets->lines[i].l_rate;
        if(min_r > this_r){
            min_r = this_r;
            index = i;
        }
    }
    cache->sets[set].lines[index].tag = tag;
    cache->sets[set].lines[index].l_rate = 0;
}

//CHECK HIT OR MISS USING FUNC. queryCache()
void cacheData(unsigned long long address, Cache *cache){
    //query cache for address
    switch(queryCache(address, cache)){
        case 0:
            printf(" Miss, evict\n");
            evictData(address, cache);
            cache->miss_c++;
            cache->evic_c++;
            break;
        case 1:
            cache->hit_c++;
            printf(" hit\n");
            break;
        case -1:
            cache->miss_c++;
            printf(" Miss, no evict\n");
            break;
        default:
            printf("queryCache returned wrong value\n");
            break;
    }
}

//SIMULATE CACHE WITH INPUT LIST OF ADDRESSES
void simulateCache(char *fileName, Cache *cache){
    FILE *input = fopen(fileName, "r");
    unsigned long long address;

    while(fscanf(input, "%llX", &address) == 1){
        printf("%llX\n", address);
        cacheData(address, cache);
    }
    fclose(input);
}

int main(int argc, char *argv[]){
    int opt,m, s, e, b;
    char *i;
    char *r;

    struct Cache cache0;

    //int n_hits,n_miss;

    //ensure correct num of arguments before parsing
    if(!(argc == 13)){
        printf("Error: Invalid number of arguments. Arg count: %d\n",argc);
        exit(-1);
    }

    while(-1 != (opt = getopt(argc,argv,"m:s:e:b:i:r"))){
        switch(opt){
            case 'm':
                m = atoi(optarg);
                break;
            case 's':
                s = atoi(optarg);
                cache0.s = s;
                break;
            case 'e':
                e = atoi(optarg);
                break;
            case 'b':
                b = atoi(optarg);
                cache0.block_b = pow(2,b);
                break;
            case 'i':
                i = optarg;
                break;
            case 'r':
                r = optarg;
                break;
            default:
                printf("Invalid argument\n");
                break;
        }
    }
    cache0.set_b = pow(2,s);
    cache0.line_per_set = pow(2,e);
    printf("addr size %d, sets: %d, lines: %d, block size: %d\n",m,cache0.set_b,cache0.line_per_set,cache0.block_b);
    //printf("Filename: %c, Mode: %c\n", i, r);

    cacheInit(&cache0);

    simulateCache(i,&cache0);
    float r_miss = (double)cache0.miss_c/(double)(cache0.miss_c+cache0.hit_c); //calculate miss rate
    float r_miss_p = r_miss * 100;
    int total_trans = cache0.hit_c + cache0.miss_c;
    int avg_access_t = 1 + (r_miss * 100); //calulate avg access time in cycles
    int total_run_t = (cache0.miss_c+cache0.hit_c)*avg_access_t;
    
    printf("Hits: %d, Misses: %d, Evictions: %d\n",cache0.hit_c,cache0.miss_c,cache0.evic_c);
    printf("Total transfers: %d\n", total_trans);
    printf("Miss Rate: %0.2f\n",r_miss_p);
    printf("Avg access time: %d clk cycles\n", avg_access_t);
    printf("Total run time: %d clk cycles\n", total_run_t);


    

    dealloc(&cache0);

    return 0;
}