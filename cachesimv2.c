//CacheSim v2 - Nathan Loucks
//THIS VERSION IS INCOMPLETE. Do not attempt to compile/use this version. It certainly will not work.

//Libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <getopt.h>
#include <ctype.h>
#include <assert.h>

typedef unsigned long long Address; //64 bit address object

struct set_line{
    long long *tag; //tag value
    long long data;
    short *v_flag; //valid flag
    int use_c; //use counter
    struct set_line *next;
    struct set_line *prev;
};
struct Set{
    struct set_line *lines;
};
struct LRUCache{
    int capacity;
    struct Set *sets;
    int hit_c;
    int miss_c;

    int n_lines;
    int n_sets;
    int t_size;
    int m;
    int s;
    int e;
    int b;

};
struct LRUCache build(int s, int e, int b){
    struct LRUCache newCache;
    struct Set set;
    struct set_line line;
    newCache.n_sets = pow(2,s);
    newCache.n_lines = pow(2,e);
    newCache.t_size = 64 - (s + b);

    newCache.b = b;
    newCache.s = s;
    newCache.e = e;

    //allocate mem for n sets in cache
    newCache.sets = (struct Set*) malloc (sizeof(struct Set) * n_sets);
    
    for(int i = 0; i < n_sets; i++){
        //allocate mem for n lines in set
        set.lines = (struct set_line*) malloc (sizeof(struct set_line) * n_lines);
        
        for(int j = 0; j < n_lines; j++){
            //initialize line values for set[i]
            line.v_flag = 0;
            line.tag = 0;
            line.use_c = 0;
            set.lines[j] = line;
        }
        newCache.sets[i] = set; //add set to cache structure
    }
    return newCache;
}


void put(Address address, struct LRUCache cache){
    Address tag = address >> (cache.b + cache.s);
}
long long get(Address address){
    long long thisData;
    //SEE IF ITS THERE
    return thisData;
}